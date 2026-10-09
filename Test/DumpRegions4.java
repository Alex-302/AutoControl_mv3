//Dump the region candidates fully.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.*;

public class DumpRegions4 extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        long[] addrs = {0x0042b8d0L, 0x0041ecb0L, 0x0041e3b0L, 0x0041de20L, 0x004187a0L, 0x00413a10L};
        for (long a : addrs) {
            Function f = currentProgram.getFunctionManager().getFunctionAt(toAddr(a));
            if (f == null) { println("no func @" + Long.toHexString(a)); continue; }
            println("=== " + f.getName() + " @ " + f.getEntryPoint() + " ===");
            DecompileResults res = ifc.decompileFunction(f, 180, monitor);
            if (res != null && res.getDecompiledFunction() != null) {
                println(res.getDecompiledFunction().getC());
            } else println("(decompile failed)");
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
