// ___crtDownlevelLocaleNameToLCID @ 00459948 size=42 callers=2

/* Library Function - Single Match
    ___crtDownlevelLocaleNameToLCID
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___crtDownlevelLocaleNameToLCID(int param_1)

{
  uint uVar1;
  
  if (param_1 != 0) {
    uVar1 = _GetTableIndexFromLocaleName(param_1);
    if ((-1 < (int)uVar1) && (uVar1 < 0xe4)) {
      return *(undefined4 *)(&DAT_004817f8 + uVar1 * 8);
    }
  }
  return 0;
}


