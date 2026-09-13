//Full native dump: sections, imports, strings+xrefs, function list,
//decompiled bodies (one file per function).
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import java.io.*;
import java.util.*;

public class FullDump extends GhidraScript {
    // Output INSIDE the repo (per user policy: no external paths).
    private static final String OUT = "C:/Work/AdGuard/Repos/Other/Alex-302/AutoControl_mv3/Test/native-disasm";
    private PrintWriter out(String name) throws Exception {
        File d = new File(OUT); d.mkdirs();
        return new PrintWriter(new FileWriter(new File(d, name)));
    }
    @Override
    public void run() throws Exception {
        File d = new File(OUT); d.mkdirs();
        File dd = new File(OUT + "/decomp"); dd.mkdirs();
        Program prog = currentProgram;
        Listing listing = prog.getListing();
        FunctionManager fm = prog.getFunctionManager();
        ReferenceManager rm = prog.getReferenceManager();
        SymbolTable st = prog.getSymbolTable();

        // 1) PE sections
        PrintWriter w = out("sections.txt");
        for (MemoryBlock b : prog.getMemory().getBlocks()) {
            w.println(b.getName() + "\tstart=" + b.getStart() + "\tsize=0x" + Long.toHexString(b.getSize()) +
                       "\tperm=" + (b.isRead()?"r":"-") + (b.isWrite()?"w":"-") + (b.isExecute()?"x":"-") +
                       "\tinitialized=" + b.isInitialized());
        }
        w.close();

        // 2) imports (external symbols grouped by library)
        w = out("imports.txt");
        Map<String, List<String>> libs = new TreeMap<>();
        SymbolIterator si = st.getAllSymbols(true);
        while (si.hasNext()) {
            Symbol s = si.next();
            if (!s.isExternal()) continue;
            Namespace ns = s.getParentNamespace();
            String lib = ns == null ? "?" : ns.getName();
            libs.computeIfAbsent(lib, k -> new ArrayList<>()).add(s.getName() + " @ " + s.getAddress());
        }
        for (Map.Entry<String, List<String>> e : libs.entrySet()) {
            w.println("=== " + e.getKey() + " (" + e.getValue().size() + ") ===");
            Collections.sort(e.getValue());
            for (String f : e.getValue()) w.println("  " + f);
        }
        w.close();

        // 3) strings + xrefs
        w = out("strings.txt");
        int strCount = 0;
        for (Data data : listing.getDefinedData(true)) {
            Object v = data.getValue();
            if (!(v instanceof String)) continue;
            String s = (String) v;
            strCount++;
            StringBuilder x = new StringBuilder();
            ReferenceIterator refs = rm.getReferencesTo(data.getAddress());
            int n = 0;
            while (refs.hasNext()) {
                Reference r = refs.next();
                Function f = fm.getFunctionContaining(r.getFromAddress());
                x.append(" ").append(f == null ? r.getFromAddress() : (f.getName() + "@" + f.getEntryPoint()));
                if (++n > 6) { x.append(" ..."); break; }
            }
            String clean = s.replaceAll("[\\x00-\\x1f\\x7f]", "?").replace("\t", " ");
            w.println(data.getAddress() + "\tlen=" + s.length() + "\t'" + clean + "'\trefs:" + x);
        }
        w.println("=== total strings: " + strCount + " ===");
        w.close();

        // 4) function list + per-function decompilation
        w = out("functions.csv");
        w.println("addr;name;size;callers");
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(prog);
        int done = 0, failed = 0;
        for (Function f : fm.getFunctions(true)) {
            long size = f.getBody().getNumAddresses();
            // callers
            int callers = 0;
            ReferenceIterator refs = rm.getReferencesTo(f.getEntryPoint());
            while (refs.hasNext()) { refs.next(); callers++; }
            w.println(f.getEntryPoint() + ";" + f.getName() + ";" + size + ";" + callers);
            // decompile (skip runtime/import thunks: size==0; skip tiny wrappers
            // <40 instr — not needed for the overview; keeps the run short)
            if (size < 40) continue;
            DecompileResults res = ifc.decompileFunction(f, 60, monitor);
            // sanitize: demangled names may contain <>:"/\|?* — invalid in
            // Windows filenames
            String base = f.getEntryPoint().toString().replace(":", "_") + "_" + f.getName();
            String safe = base.replaceAll("[<>:\"/\\\\|?*\\x00-\\x1f]", "_");
            if (safe.length() > 150) safe = safe.substring(0, 150);
            String fn = safe + ".c";
            try (PrintWriter dw = new PrintWriter(new FileWriter(new File(dd, fn)))) {
                if (res != null && res.getDecompiledFunction() != null) {
                    dw.println("// " + f.getName() + " @ " + f.getEntryPoint() + " size=" + size + " callers=" + callers);
                    dw.println(res.getDecompiledFunction().getC());
                    done++;
                } else {
                    dw.println("// DECOMPILE FAILED " + f.getName() + " @ " + f.getEntryPoint());
                    failed++;
                }
            }
            if ((done + failed) % 500 == 0) println("progress: " + (done + failed) + "/" + fm.getFunctionCount());
        }
        w.println("=== total functions: " + fm.getFunctionCount() + " decompiled=" + done + " failed=" + failed + " ===");
        w.close();
        ifc.dispose();
        println("=== DUMP DONE: functions=" + fm.getFunctionCount() + " decompiled=" + done + " failed=" + failed + " strings=" + strCount + " -> " + OUT + " ===");
    }
}
