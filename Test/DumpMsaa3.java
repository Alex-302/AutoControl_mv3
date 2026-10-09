//Dump the window-class classifiers + their callers.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;

public class DumpMsaa3 extends GhidraScript {
    private void dump(DecompInterface ifc, long addr) {
        Function f = currentProgram.getFunctionManager().getFunctionAt(toAddr(addr));
        if (f == null) { println("no func @" + Long.toHexString(addr)); return; }
        println("=== " + f.getName() + " @ " + f.getEntryPoint() + " ===");
        DecompileResults res = ifc.decompileFunction(f, 120, monitor);
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
        long[] targets = {0x004096c0L, 0x0040daf0L, 0x0040d060L, 0x00416270L, 0x0042f430L};
        for (long a : targets) dump(ifc, a);
        // callers of the classifiers
        long[] cl = {0x004096c0L, 0x0040daf0L, 0x0040d060L};
        for (long a : cl) {
            ReferenceIterator refs = rm.getReferencesTo(toAddr(a));
            java.util.Set<Long> seen = new java.util.HashSet<>();
            while (refs.hasNext()) {
                Reference ref = refs.next();
                Function f = fm.getFunctionContaining(ref.getFromAddress());
                if (f == null) continue;
                if (!seen.add(f.getEntryPoint().getOffset())) continue;
                println("=== CALLER of " + Long.toHexString(a) + ": " + f.getName() + " @ " + f.getEntryPoint() + " ===");
                DecompileResults res = ifc.decompileFunction(f, 120, monitor);
                if (res != null && res.getDecompiledFunction() != null) {
                    println(res.getDecompiledFunction().getC());
                }
            }
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
