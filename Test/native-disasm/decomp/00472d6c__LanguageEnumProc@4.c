// _LanguageEnumProc@4 @ 00472d6c size=216 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    _LanguageEnumProc@4
   
   Library: Visual Studio 2015 Release */

uint _LanguageEnumProc_4(ushort *param_1)

{
  uint *puVar1;
  __acrt_ptd *p_Var2;
  __acrt_ptd *p_Var3;
  LCID Locale;
  int iVar4;
  WCHAR local_f8 [120];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var2 = FUN_0046aa74();
  p_Var3 = FUN_0046aa74();
  puVar1 = *(uint **)(p_Var3 + 0x34c);
  Locale = _LcidFromHexString(param_1);
  iVar4 = GetLocaleInfoW(Locale,(-(uint)(*(int *)(p_Var2 + 0x60) != 0) & 0xfffff002) + 0x1001,
                         local_f8,0x78);
  if (iVar4 == 0) {
    *puVar1 = 0;
    return 1;
  }
  iVar4 = __wcsicmp(*(wchar_t **)(p_Var2 + 0x50),local_f8);
  if (iVar4 == 0) {
    if (*(int *)(p_Var2 + 0x60) == 0) {
      iVar4 = 1;
      goto LAB_00472e11;
    }
  }
  else {
    if (((*(int *)(p_Var2 + 0x60) != 0) || (*(int *)(p_Var2 + 0x5c) == 0)) ||
       (iVar4 = __wcsicmp(*(wchar_t **)(p_Var2 + 0x50),local_f8), iVar4 != 0)) goto LAB_00472e27;
    iVar4 = 0;
LAB_00472e11:
    iVar4 = _TestDefaultLanguage(Locale,iVar4);
    if (iVar4 == 0) goto LAB_00472e27;
  }
  *puVar1 = *puVar1 | 4;
  puVar1[1] = Locale;
  puVar1[2] = Locale;
LAB_00472e27:
  return ~(*puVar1 >> 2) & 1;
}


