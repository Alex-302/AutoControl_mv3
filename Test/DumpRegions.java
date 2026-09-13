//Find functions combining WindowFromPoint/ChildWindowFromPointEx with GetClassName/GetCursorInfo.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.AddressSet;

public class DumpRegions extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        String[] pointFns = {"WindowFromPoint", "ChildWindowFromPointEx", "GetCursorInfo", "GetCursorPos"};
        String[] classFns = {"GetClassNameA", "GetClassNameW", "GetWindowRect", "FindWindowExA", "GetAncestor"};
        // map: function entry -> set of called import names
        java.util.Map<Long, java.util.Set<String>> usage = new java.util.HashMap<>();
        for (String t : pointFns) {
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
        for (String t : classFns) {
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
        for (java.util.Map.Entry<Long, java.util.Set<String>> e : usage.entrySet()) {
            if (e.getValue().size() < 2) continue;
            Function f = fm.getFunctionAt(currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(e.getKey()));
            if (f == null) continue;
            println("=== " + f.getName() + " @ " + f.getEntryPoint() + " uses: " + e.getValue() + " ===");
            DecompileResults res = ifc.decompileFunction(f, 180, monitor);
            if (res != null && res.getDecompiledFunction() != null) {
                println(res.getDecompiledFunction().getC());
            }
        }
        ifc.dispose();
        println("=== DONE ===");
    }
}
