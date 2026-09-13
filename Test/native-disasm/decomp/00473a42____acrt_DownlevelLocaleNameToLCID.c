// ___acrt_DownlevelLocaleNameToLCID @ 00473a42 size=44 callers=1

/* Library Function - Single Match
    ___acrt_DownlevelLocaleNameToLCID
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_DownlevelLocaleNameToLCID(wchar_t *param_1)

{
  uint uVar1;
  
  if (param_1 != (wchar_t *)0x0) {
    uVar1 = GetTableIndexFromLocaleName(param_1);
    if ((-1 < (int)uVar1) && (uVar1 < 0xe4)) {
      return *(undefined4 *)(&DAT_00487a28 + uVar1 * 8);
    }
  }
  return 0;
}


