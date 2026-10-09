//Dump xrefs + decompiled code for MSAA / hit-test related imports.
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;

public class DumpMsaa extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] targets = {
            "AccessibleObjectFromPoint", "AccessibleObjectFromWindow",
            "AccessibleObjectFromEvent", "AccessibleChildren",
            "WindowFromPoint", "GetClassNameA", "ChildWindowFromPointEx",
            "GetCursorInfo", "GetWindowRect"
        };
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        SymbolTable st = currentProgram.getSymbolTable();
        ReferenceManager rm = currentProgram.getReferenceManager();
        FunctionManager fm = currentProgram.getFunctionManager();
        java.util.Set<Long> seen = new java.util.HashSet<>();
        for (String t : targets) {
            SymbolIterator it = st.getSymbols(t);
            while (it.hasNext()) {
                Symbol s = it.next();
                ReferenceIterator refs = rm.getReferencesTo(s.getAddress());
                while (refs.hasNext()) {
                    Reference ref = refs.next();
                    Function f = fm.getFunctionContaining(ref.getFromAddress());
                    if (f == null) continue;
                    if (!seen.add(f.getEntryPoint().getOffset())) continue;
                    println("=== " + t + " ref @ " + ref.getFromAddress() + " -> " + f.getName() + " @ " + f.getEntryPoint() + " ===");
                    DecompileResults res = ifc.decompileFunction(f, 120, monitor);
                    if (res != null && res.getDecompiledFunction() != null) {
                        println(res.getDecompiledFunction().getC());
                    } else {
                        println("(decompile failed)");
                    }
                }
            }
        }
        ifc.dispose();
        println("=== DONE, functions: " + seen.size() + " ===");
    }
}
