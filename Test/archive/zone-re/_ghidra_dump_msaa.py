#@category Analysis
# Dump xrefs + decompiled code for the MSAA / hit-test related imports.
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

prog = getCurrentProgram()
ifc = DecompInterface()
ifc.openProgram(prog)
monitor = ConsoleTaskMonitor()

targets = ['AccessibleObjectFromPoint', 'AccessibleObjectFromWindow',
           'AccessibleObjectFromEvent', 'AccessibleChildren',
           'WindowFromPoint', 'GetClassNameA', 'ChildWindowFromPointEx',
           'GetCursorInfo', 'GetWindowRect']

seen = set()
for t in targets:
    try:
        syms = getSymbols(t)
    except Exception:
        syms = []
    for s in syms:
        try:
            refs = getReferencesTo(s.getAddress())
        except Exception:
            refs = []
        for ref in refs:
            f = getFunctionContaining(ref.getFromAddress())
            if f is None:
                continue
            key = f.getEntryPoint()
            if key in seen:
                continue
            seen.add(key)
            print("=== %s ref @ %s -> %s @ %s ===" % (t, ref.getFromAddress(), f.getName(), f.getEntryPoint()))
            res = ifc.decompile(f, monitor)
            if res and res.getDecompiledFunction():
                print(res.getDecompiledFunction().getC())
            else:
                print("(decompile failed)")
ifc.dispose()
print("=== DONE, %d functions ===" % len(seen))
