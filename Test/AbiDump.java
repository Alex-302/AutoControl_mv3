// AbiDump.java - dump the instruction-level ABI evidence the v19 trampoline
// relies on (see AutoControl_native/patches/README.md, "Why this injected code
// is legal"): the prologue of the patched region matcher FUN_004156f0 (which
// register carries the region) and the call site in its only caller
// FUN_00415b40 (which argument is pushed, what happens right after the call).
//
// Ghidra prints `MOV ESI,EDX` where the decompiler only shows `param_2` - that
// pair is what proves EDX = the region. The "no other reference to 0x4156F0"
// half of the evidence is printed by `node Test/engine_abi_dump.js`.
//
// Usage (headless, no auto-analysis needed; JAVA_HOME must point at JDK 21+):
//   analyzeHeadless <proj-dir> <proj-name> \
//     -import AutoControl_native\original\AutoCtrl_2025.4.22.0.exe -noanalysis \
//     -scriptPath <repo>\Test -postScript AbiDump.java -deleteProject
//
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;

public class AbiDump extends GhidraScript {

    private static final long MATCHER = 0x4156F0L;   // FUN_004156f0, the patched function
    private static final long CALLER  = 0x415BB0L;   // FUN_00415b40, around its call site

    private String hexBytes(byte[] b) {
        StringBuilder s = new StringBuilder();
        for (byte x : b) s.append(String.format("%02x ", x));
        return s.toString().trim();
    }

    /** Disassemble [va, va+len) and print every instruction. */
    private void dump(String title, long va, int len) throws Exception {
        Listing listing = currentProgram.getListing();
        println("");
        println("=== " + title + " (VA 0x" + Long.toHexString(va) + ") ===");
        long cur = va, end = va + len;
        while (cur < end) {
            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(cur);
            Instruction ins = listing.getInstructionAt(a);
            if (ins == null) { disassemble(a); ins = listing.getInstructionAt(a); }
            if (ins == null) { println(String.format("%08x  <no instruction>", cur)); return; }
            println(String.format("%08x  %-26s %s",
                    ins.getAddress().getOffset(), hexBytes(ins.getBytes()), ins.toString()));
            cur += Math.max(1, ins.getLength());
        }
    }

    @Override
    public void run() throws Exception {
        println("ABI AUDIT - " + currentProgram.getName()
                + "  (compiler spec: " + currentProgram.getCompilerSpec().getCompilerSpecID() + ")");
        // The prologue is the part the patch replaces: the 5 bytes at MATCHER,
        // then MOV ESI,EDX (region) / MOV EBX,ECX (POINT*) and the region
        // switch table.
        dump("FUN_004156f0 prologue + region switch", MATCHER, 0x80);
        // The only caller: PUSH arg3; MOV EDX,<region>; MOV ECX,<point>;
        // CALL; ADD ESP,4; POPs (callee-saved); RET (EAX returned unchanged).
        dump("FUN_00415b40 around the call site", CALLER, 0x40);
    }
}
