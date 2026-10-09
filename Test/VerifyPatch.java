//Verify the accName patch: decompile FUN_0040b610 from the PATCHED binary.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.*;

public class VerifyPatch extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        long[] addrs = {0x0040b610L, 0x0040bdf0L};
        for (long a : addrs) {
            Function f = fm.getFunctionAt(toAddr(a));
            if (f == null) { println("no func @" + Long.toHexString(a)); continue; }
            println("=== " + f.getName() + " @ " + f.getEntryPoint() + " ===");
            DecompileResults res = ifc.decompileFunction(f, 120, monitor);
            if (res != null && res.getDecompiledFunction() != null) {
                println(res.getDecompiledFunction().getC());
            } else println("(decompile failed)");
        }
        // dump the cave instructions
        println("=== cave @0x409570 ===");
        Instruction insn = currentProgram.getListing().getInstructionAt(toAddr(0x409570L));
        int n = 0;
        while (insn != null && n < 15) {
            println(insn.getAddress() + "  " + insn);
            insn = insn.getNext();
            n++;
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
