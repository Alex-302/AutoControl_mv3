//Dump callers of the AccessibleObjectFromPoint wrapper + Chrome strings.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;

public class DumpMsaa2 extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        SymbolTable st = currentProgram.getSymbolTable();
        ReferenceManager rm = currentProgram.getReferenceManager();
        FunctionManager fm = currentProgram.getFunctionManager();

        // 1) callers of FUN_0040b610 (the AccessibleObjectFromPoint wrapper)
        Address wrap = toAddr(0x0040b610);
        ReferenceIterator refs = rm.getReferencesTo(wrap);
        java.util.Set<Long> seen = new java.util.HashSet<>();
        while (refs.hasNext()) {
            Reference ref = refs.next();
            Function f = fm.getFunctionContaining(ref.getFromAddress());
            if (f == null) continue;
            if (!seen.add(f.getEntryPoint().getOffset())) continue;
            println("=== CALLER of point-wrapper: " + f.getName() + " @ " + f.getEntryPoint() + " ===");
            DecompileResults res = ifc.decompileFunction(f, 120, monitor);
            if (res != null && res.getDecompiledFunction() != null) {
                println(res.getDecompiledFunction().getC());
            }
        }

        // 2) the "Chrome" string + all strings containing Chrome
        println("=== STRINGS with 'Chrome' ===");
        DataIterator dit = currentProgram.getListing().getDefinedData(true);
        while (dit.hasNext()) {
            ghidra.program.model.listing.Data d = dit.next();
            Object v = d.getValue();
            if (v instanceof String) {
                String s = (String) v;
                if (s.toLowerCase().contains("chrome") || s.toLowerCase().contains("render")) {
                    ReferenceIterator r2 = rm.getReferencesTo(d.getAddress());
                    String callers = "";
                    while (r2.hasNext()) {
                        Reference ref = r2.next();
                        Function f = fm.getFunctionContaining(ref.getFromAddress());
                        if (f != null) callers += f.getName() + "@" + f.getEntryPoint() + " ";
                    }
                    println("str @" + d.getAddress() + ": '" + s + "' refs: " + callers);
                }
            }
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
