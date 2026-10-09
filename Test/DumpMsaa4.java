//Dump callers of the class classifier + full FUN_00426a50/FUN_0042f430.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;

public class DumpMsaa4 extends GhidraScript {
    private void dump(DecompInterface ifc, long addr, String label) {
        Function f = currentProgram.getFunctionManager().getFunctionAt(toAddr(addr));
        if (f == null) { println("no func @" + Long.toHexString(addr)); return; }
        println("=== " + label + " " + f.getName() + " @ " + f.getEntryPoint() + " ===");
        DecompileResults res = ifc.decompileFunction(f, 180, monitor);
        if (res != null && res.getDecompiledFunction() != null) {
            println(res.getDecompiledFunction().getC());
        } else println("(decompile failed)");
    }
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        // full bodies of the point-wrapper callers
        dump(ifc, 0x00426a50L, "CALLER#4(point-wrapper)");
        dump(ifc, 0x0042f430L, "CALLER#3(point-wrapper)");
        // callers of the classifiers
        long[] cl = {0x004096c0L, 0x0040daf0L};
        for (long a : cl) {
            ReferenceIterator refs = rm.getReferencesTo(toAddr(a));
            java.util.Set<Long> seen = new java.util.HashSet<>();
            while (refs.hasNext()) {
                Reference ref = refs.next();
                Function f = fm.getFunctionContaining(ref.getFromAddress());
                if (f == null) continue;
                if (!seen.add(f.getEntryPoint().getOffset())) continue;
                println("=== CALLER of " + Long.toHexString(a) + ": " + f.getName() + " @ " + f.getEntryPoint() + " ===");
                DecompileResults res = ifc.decompileFunction(f, 180, monitor);
                if (res != null && res.getDecompiledFunction() != null) {
                    println(res.getDecompiledFunction().getC());
                }
            }
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
