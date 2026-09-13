//Full dump of FUN_00415240, FUN_0040e030 and their callers.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;

public class DumpRegions2 extends GhidraScript {
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
        dump(ifc, 0x00415240L, "FULL");
        dump(ifc, 0x0040e030L, "FULL");
        // callers of both
        long[] a2 = {0x00415240L, 0x0040e030L};
        for (long a : a2) {
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
