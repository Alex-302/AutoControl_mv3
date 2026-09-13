// ___acrt_get_qualified_locale_downlevel @ 00473069 size=519 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_get_qualified_locale_downlevel
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_get_qualified_locale_downlevel(int param_1,UINT *param_2,LPWSTR param_3)

{
  short *psVar1;
  __acrt_ptd *p_Var2;
  __acrt_ptd *p_Var3;
  __acrt_ptd *p_Var4;
  uint uVar5;
  UINT _Val;
  BOOL BVar6;
  int iVar7;
  uint local_14;
  LCID local_10;
  LCID local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var2 = FUN_0046aa74();
  p_Var3 = p_Var2 + 0x50;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  p_Var4 = FUN_0046aa74();
  *(uint **)(p_Var4 + 0x34c) = &local_14;
  psVar1 = (short *)(param_1 + 0x80);
  *(int *)p_Var3 = param_1;
  p_Var4 = p_Var2 + 0x54;
  *(short **)p_Var4 = psVar1;
  if ((psVar1 != (short *)0x0) && (*psVar1 != 0)) {
    _TranslateName(0x4878e8,DAT_004879fc + -1,(int *)p_Var4);
  }
  local_14 = 0;
  if ((*(short **)p_Var3 == (short *)0x0) || (**(short **)p_Var3 == 0)) {
    if ((*(short **)p_Var4 == (short *)0x0) || (**(short **)p_Var4 == 0)) {
      local_14 = 0x104;
      local_10 = GetUserDefaultLCID();
      local_c = local_10;
    }
    else {
      _GetLcidFromCountry((byte *)&local_14);
    }
  }
  else {
    if ((*(short **)p_Var4 == (short *)0x0) || (**(short **)p_Var4 == 0)) {
      _GetLcidFromLanguage((byte *)&local_14);
    }
    else {
      _GetLcidFromLangCountry(&local_14);
    }
    if (local_14 != 0) goto LAB_0047319e;
    uVar5 = _TranslateName(0x4875d8,DAT_004878e4 + -1,(int *)p_Var3);
    if ((char)uVar5 != '\0') {
      if ((*(short **)p_Var4 == (short *)0x0) || (**(short **)p_Var4 == 0)) {
        _GetLcidFromLanguage((byte *)&local_14);
      }
      else {
        _GetLcidFromLangCountry(&local_14);
      }
    }
  }
  if (local_14 == 0) {
    return 0;
  }
LAB_0047319e:
  _Val = _ProcessCodePage((wchar_t *)(-(uint)(param_1 != 0) & param_1 + 0x100U),(int)&local_14);
  if ((((_Val == 0) || (_Val == 65000)) || (_Val == 0xfde9)) ||
     ((BVar6 = IsValidCodePage(_Val & 0xffff), BVar6 == 0 ||
      (BVar6 = IsValidLocale(local_10,1), BVar6 == 0)))) {
    return 0;
  }
  if (param_2 != (UINT *)0x0) {
    *param_2 = _Val;
  }
  ___acrt_LCIDToLocaleName_16(local_10,(wchar_t *)(p_Var2 + 0x2a0),0x55,0);
  if (param_3 != (LPWSTR)0x0) {
    ___acrt_LCIDToLocaleName_16(local_10,param_3 + 0x90,0x55,0);
    iVar7 = GetLocaleInfoW(local_10,0x1001,param_3,0x40);
    if (iVar7 == 0) {
      return 0;
    }
    iVar7 = GetLocaleInfoW(local_c,0x1002,param_3 + 0x40,0x40);
    if (iVar7 == 0) {
      return 0;
    }
    __itow_s(_Val,param_3 + 0x80,0x10,10);
  }
  return 1;
}


