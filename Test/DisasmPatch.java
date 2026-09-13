// Disassemble the bytes injected by the v19 engine patch (entry jump + code cave)
// and print them as an annotated listing.
//
// The file ships the "helper-absent" fallback variant; the zone helper rewrites
// cave bytes 0x00..0x1B in the process at runtime. This script disassembles the
// FILE variant and then patches the cave bytes in memory with the RUNTIME
// variant (using the same absolute addresses the helper computes) and
// disassembles that too - so both listings come from a real disassembler.
//
// Usage (headless, no auto-analysis needed):
//   analyzeHeadless <proj> <name> -import <patched exe> -noanalysis \
//     -postScript DisasmPatch.java
//
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;

public class DisasmPatch extends GhidraScript {

    private static final long ENTRY    = 0x4156F0L;   // FUN_004156f0 (region matcher)
    private static final long CAVE     = 0x47F7A3L;   // code cave in the .text tail
    private static final int  ENTRY_LEN = 5;
    private static final int  ORIG_BLOCK = 0x1C;      // size of the injected prefix
    private static final int  CAVE_LEN  = ORIG_BLOCK + 5 + 5;   // prefix + displaced bytes + jmp back

    // absolute addresses the helper writes (values observed live 2026-09-13;
    // any address works for the LISTING - they are computed at runtime from the
    // module base, so ASLR is irrelevant for the file format)
    private static final long ALIVE = 0x005D0000L;
    private static final long TABLE = 0x005D0010L;

    private Address addr(long va) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(va);
    }

    private String hexBytes(byte[] b) {
        StringBuilder s = new StringBuilder();
        for (byte x : b) s.append(String.format("%02x ", x));
        return s.toString().trim();
    }

    /** Disassemble [va, va+len) and print every instruction. */
    private void dump(String title, long va, int len) throws Exception {
        Listing listing = currentProgram.getListing();
        long cur = va, end = va + len;
        println("");
        println("=== " + title + " (VA 0x" + Long.toHexString(va) + ", " + len + " bytes) ===");
        while (cur < end) {
            Address a = addr(cur);
            Instruction ins = listing.getInstructionAt(a);
            if (ins == null) { disassemble(a); ins = listing.getInstructionAt(a); }
            if (ins == null) { println(String.format("%08x  <no instruction>", cur)); return; }
            println(String.format("%08x  %-26s %s",
                    ins.getAddress().getOffset(), hexBytes(ins.getBytes()), ins.toString()));
            if (ins.getLength() <= 0) return;
            cur += ins.getLength();
        }
    }

    /** Build the runtime (table) variant of the cave prefix. */
    private byte[] runtimePrefix() {
        byte[] b = new byte[0x1C];
        b[0] = (byte) 0x83; b[1] = (byte) 0xFA; b[2] = (byte) 0x28;   // cmp edx,28h
        b[3] = 0x73; b[4] = 0x17;                                     // jae ORIG (+0x1C)
        b[5] = (byte) 0x80; b[6] = 0x3D;                              // cmp byte [ALIVE],0
        b[7] = (byte) (ALIVE & 0xFF);
        b[8] = (byte) ((ALIVE >> 8) & 0xFF);
        b[9] = (byte) ((ALIVE >> 16) & 0xFF);
        b[10] = (byte) ((ALIVE >> 24) & 0xFF);
        b[11] = 0x00;
        b[12] = 0x74; b[13] = 0x08;                                   // je NOTALIVE (+0x16)
        b[14] = (byte) 0x8B; b[15] = 0x04; b[16] = (byte) 0x95;       // mov eax,[edx*4+TABLE]
        b[17] = (byte) (TABLE & 0xFF);
        b[18] = (byte) ((TABLE >> 8) & 0xFF);
        b[19] = (byte) ((TABLE >> 16) & 0xFF);
        b[20] = (byte) ((TABLE >> 24) & 0xFF);
        b[21] = (byte) 0xC3;                                          // ret
        b[22] = (byte) 0xB8; b[23] = 0x01; b[24] = 0x00;              // NOTALIVE: mov eax,1
        b[25] = 0x00; b[26] = 0x00;
        b[27] = (byte) 0xC3;                                          // ret
        return b;
    }

    @Override
    public void run() throws Exception {
        println("patch disassembly - " + currentProgram.getName());
        println("  ALIVE/TABLE shown as 0x" + Long.toHexString(ALIVE) + " / 0x" + Long.toHexString(TABLE)
                + " (the helper computes its own page at runtime)");

        dump("PATCH 1 - entry jump (file)", ENTRY, ENTRY_LEN);
        dump("PATCH 2 - code cave, FILE variant (helper absent)", CAVE, CAVE_LEN);

        // rewrite the cave prefix with the runtime variant and disassemble again
        int tx = currentProgram.startTransaction("cave -> runtime variant");
        try {
            // the bytes are already decoded as instructions, so the listing must
            // be cleared BEFORE writing (otherwise: "Memory change conflicts
            // with instruction at 0047f7a3")
            clearListing(addr(CAVE), addr(CAVE + ORIG_BLOCK - 1));
            currentProgram.getMemory().setBytes(addr(CAVE), runtimePrefix());
        } finally {
            currentProgram.endTransaction(tx, true);
        }
        dump("PATCH 2 - code cave, RUNTIME variant (helper writes this)", CAVE, ORIG_BLOCK);
    }
}
