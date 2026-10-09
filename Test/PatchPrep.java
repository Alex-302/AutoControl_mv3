//Disassemble FUN_0040b610 (bytes) + list candidate code caves near it.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;

public class PatchPrep extends GhidraScript {
    @Override
    public void run() throws Exception {
        Listing listing = currentProgram.getListing();
        Memory mem = currentProgram.getMemory();
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();

        // 1) disassemble FUN_0040b610 with bytes
        Function f = fm.getFunctionAt(toAddr(0x0040b610L));
        println("=== FUN_0040b610 @ " + f.getEntryPoint() + " size=" + f.getBody().getNumAddresses() + " ===");
        Instruction insn = listing.getInstructionAt(f.getEntryPoint());
        int n = 0;
        while (insn != null && n < 20) {
            byte[] b = new byte[insn.getLength()];
            mem.getBytes(insn.getAddress(), b);
            StringBuilder sb = new StringBuilder();
            for (byte x : b) sb.append(String.format("%02X ", x & 0xff));
            println(insn.getAddress() + "  " + sb + "  " + insn);
            insn = insn.getNext();
            n++;
        }

        // 2) code caves: gaps between functions in .text, sorted by proximity to 0x40b610
        java.util.List<long[]> funcs = new java.util.ArrayList<>();
        for (Function g : fm.getFunctions(true)) {
            long s = g.getEntryPoint().getOffset();
            if (s >= 0x401000 && s < 0x47E800) funcs.add(new long[]{s, g.getBody().getNumAddresses()});
        }
        funcs.sort((a, b) -> Long.compare(a[0], b[0]));
        java.util.List<long[]> caves = new java.util.ArrayList<>();
        for (int i = 0; i < funcs.size() - 1; i++) {
            long end = funcs.get(i)[0] + funcs.get(i)[1];
            long next = funcs.get(i + 1)[0];
            if (next > end + 48) caves.add(new long[]{end, next - end, next});
        }
        long target = 0x0040b610L;
        caves.sort((a, b) -> Long.compare(Math.abs(a[0] - target), Math.abs(b[0] - target)));
        println("=== nearest caves >=48B ===");
        for (int i = 0; i < Math.min(6, caves.size()); i++) {
            long[] c = caves.get(i);
            println("cave 0x" + Long.toHexString(c[0]) + " size=" + c[1] + " before func 0x" + Long.toHexString(c[2]));
        }

        // 3) INSPECT the original cave 0x409570 (patch target): bytes + refs
        println("=== cave 0x409570 original bytes (0x40) ===");
        byte[] cb = new byte[0x40];
        mem.getBytes(toAddr(0x00409570L), cb);
        StringBuilder s2 = new StringBuilder();
        for (int i = 0; i < cb.length; i++) {
            if (i % 16 == 0) s2.append("\n").append(Long.toHexString(0x409570 + i)).append(": ");
            s2.append(String.format("%02X ", cb[i] & 0xff));
        }
        println(s2.toString());
        int refsToCave = 0;
        ReferenceIterator ri = rm.getReferencesTo(toAddr(0x00409570L));
        while (ri.hasNext()) { ri.next(); refsToCave++; }
        println("refs TO 0x409570: " + refsToCave);
        println("=== DONE ===");
    }
}
