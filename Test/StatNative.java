//Stat the binary: function count, string count, biggest functions.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.util.*;

public class StatNative extends GhidraScript {
    @Override
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        int fcount = 0;
        List<Function> big = new ArrayList<>();
        for (Function f : fm.getFunctions(true)) {
            fcount++;
            if (f.getBody().getNumAddresses() > 200) big.add(f);
        }
        big.sort((a, b) -> Long.compare(b.getBody().getNumAddresses(), a.getBody().getNumAddresses()));
        int scount = 0;
        for (Data d : listing.getDefinedData(true)) {
            if (d.getValue() instanceof String) scount++;
        }
        println("functions: " + fcount);
        println("strings: " + scount);
        println("functions >200 instr: " + big.size());
        println("--- top 25 by size ---");
        for (int i = 0; i < Math.min(25, big.size()); i++) {
            Function f = big.get(i);
            println(f.getEntryPoint() + " " + f.getName() + " ~" + f.getBody().getNumAddresses() + " instr");
        }
        // find the message-dispatch table: search for a table of pointers into functions near a switch on small constants
        println("--- DONE ---");
    }
}
