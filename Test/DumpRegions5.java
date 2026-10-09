//Dump the IAccessible helper wrappers (role/name/etc) + the point wrapper.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.*;

public class DumpRegions5 extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        long[] addrs = {0x0040b610L, 0x0040bdf0L, 0x0040b930L, 0x0040ba70L, 0x0040b9e0L, 0x0040bcc0L};
        for (long a : addrs) {
            Function f = currentProgram.getFunctionManager().getFunctionAt(toAddr(a));
            if (f == null) { println("no func @" + Long.toHexString(a)); continue; }
            println("=== " + f.getName() + " @ " + f.getEntryPoint() + " ===");
            DecompileResults res = ifc.decompileFunction(f, 120, monitor);
            if (res != null && res.getDecompiledFunction() != null) {
                println(res.getDecompiledFunction().getC());
            } else println("(decompile failed)");
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
