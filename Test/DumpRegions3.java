//List callers of cursor/point APIs + the window-from-point helper.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;

public class DumpRegions3 extends GhidraScript {
    @Override
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        String[] apis = {"GetCursorInfo", "GetCursorPos", "GetMessagePos", "WindowFromPoint",
                         "ChildWindowFromPointEx", "GetForegroundWindow", "GetWindowThreadProcessId"};
        java.util.Map<Long, java.util.Set<String>> usage = new java.util.HashMap<>();
        for (String t : apis) {
            SymbolIterator it = currentProgram.getSymbolTable().getSymbols(t);
            while (it.hasNext()) {
                Symbol s = it.next();
                ReferenceIterator refs = rm.getReferencesTo(s.getAddress());
                while (refs.hasNext()) {
                    Reference ref = refs.next();
                    Function f = fm.getFunctionContaining(ref.getFromAddress());
                    if (f == null) continue;
                    usage.computeIfAbsent(f.getEntryPoint().getOffset(), k -> new java.util.HashSet<>()).add(t);
                }
            }
        }
        // the window-from-point helper FUN_00404e30
        ReferenceIterator refs = rm.getReferencesTo(toAddr(0x00404e30L));
        java.util.Set<Long> hp = new java.util.HashSet<>();
        while (refs.hasNext()) {
            Reference ref = refs.next();
            Function f = fm.getFunctionContaining(ref.getFromAddress());
            if (f == null) continue;
            hp.add(f.getEntryPoint().getOffset());
            usage.computeIfAbsent(f.getEntryPoint().getOffset(), k -> new java.util.HashSet<>()).add("FUN_00404e30");
        }
        for (java.util.Map.Entry<Long, java.util.Set<String>> e : usage.entrySet()) {
            Function f = fm.getFunctionAt(currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(e.getKey()));
            if (f == null) continue;
            println(f.getName() + " @ " + f.getEntryPoint() + " : " + e.getValue());
        }
        println("=== DONE ===");
    }
}
