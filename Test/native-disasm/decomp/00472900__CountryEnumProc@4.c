// _CountryEnumProc@4 @ 00472900 size=169 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    _CountryEnumProc@4
   
   Library: Visual Studio 2015 Release */

uint _CountryEnumProc_4(ushort *param_1)

{
  uint *puVar1;
  __acrt_ptd *p_Var2;
  __acrt_ptd *p_Var3;
  LCID Locale;
  int iVar4;
  uint uVar5;
  WCHAR local_f8 [120];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var2 = FUN_0046aa74();
  p_Var3 = FUN_0046aa74();
  puVar1 = *(uint **)(p_Var3 + 0x34c);
  Locale = _LcidFromHexString(param_1);
  iVar4 = GetLocaleInfoW(Locale,(-(uint)(*(int *)(p_Var2 + 100) != 0) & 0xfffff005) + 0x1002,
                         local_f8,0x78);
  if (iVar4 == 0) {
    *puVar1 = 0;
    uVar5 = 1;
  }
  else {
    iVar4 = __wcsicmp(*(wchar_t **)(p_Var2 + 0x54),local_f8);
    if (iVar4 == 0) {
      iVar4 = _TestDefaultCountry((short)Locale);
      if (iVar4 != 0) {
        *puVar1 = *puVar1 | 4;
        puVar1[2] = Locale;
        puVar1[1] = Locale;
      }
    }
    uVar5 = ~(*puVar1 >> 2) & 1;
  }
  return uVar5;
}


