// _LangCountryEnumProc@4 @ 00472b1c size=592 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    _LangCountryEnumProc@4
   
   Library: Visual Studio 2015 Release */

uint _LangCountryEnumProc_4(ushort *param_1)

{
  short *psVar1;
  short sVar2;
  uint *puVar3;
  uint uVar4;
  __acrt_ptd *p_Var5;
  __acrt_ptd *p_Var6;
  LCID Locale;
  int iVar7;
  short *psVar8;
  uint extraout_EDX;
  WCHAR local_f8 [120];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var5 = FUN_0046aa74();
  p_Var6 = FUN_0046aa74();
  puVar3 = *(uint **)(p_Var6 + 0x34c);
  Locale = _LcidFromHexString(param_1);
  iVar7 = GetLocaleInfoW(Locale,(-(uint)(*(int *)(p_Var5 + 100) != 0) & 0xfffff005) + 0x1002,
                         local_f8,0x78);
  if (iVar7 == 0) {
LAB_00472b7a:
    *puVar3 = 0;
    return 1;
  }
  iVar7 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x54),local_f8);
  if (iVar7 == 0) {
    iVar7 = GetLocaleInfoW(Locale,(-(uint)(*(int *)(p_Var5 + 0x60) != 0) & 0xfffff002) + 0x1001,
                           local_f8,0x78);
    if (iVar7 == 0) goto LAB_00472b7a;
    iVar7 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x50),local_f8);
    if (iVar7 == 0) {
      *puVar3 = *puVar3 | 0x304;
      puVar3[1] = Locale;
LAB_00472c4f:
      puVar3[2] = Locale;
    }
    else if ((*puVar3 & 2) == 0) {
      if ((*(int *)(p_Var5 + 0x5c) == 0) ||
         (iVar7 = __wcsnicmp(*(wchar_t **)(p_Var5 + 0x50),local_f8,*(size_t *)(p_Var5 + 0x5c)),
         iVar7 != 0)) {
        if (((*puVar3 & 1) == 0) && (iVar7 = _TestDefaultCountry((short)Locale), iVar7 != 0)) {
          *puVar3 = extraout_EDX | 1;
          goto LAB_00472c4f;
        }
      }
      else {
        *puVar3 = *puVar3 | 2;
        puVar3[2] = Locale;
        psVar8 = *(short **)(p_Var5 + 0x50);
        psVar1 = psVar8 + 1;
        do {
          sVar2 = *psVar8;
          psVar8 = psVar8 + 1;
        } while (sVar2 != 0);
        if ((int)psVar8 - (int)psVar1 >> 1 == *(int *)(p_Var5 + 0x5c)) {
          puVar3[1] = Locale;
        }
      }
    }
  }
  if ((*puVar3 & 0x300) == 0x300) goto LAB_00472d4f;
  iVar7 = GetLocaleInfoW(Locale,(-(uint)(*(int *)(p_Var5 + 0x60) != 0) & 0xfffff002) + 0x1001,
                         local_f8,0x78);
  if (iVar7 == 0) {
    *puVar3 = 0;
    return 1;
  }
  iVar7 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x50),local_f8);
  if (iVar7 == 0) {
    *puVar3 = *puVar3 | 0x200;
    if ((*(int *)(p_Var5 + 0x60) == 0) && (*(int *)(p_Var5 + 0x5c) != 0)) {
      psVar8 = *(short **)(p_Var5 + 0x50);
      psVar1 = psVar8 + 1;
      do {
        sVar2 = *psVar8;
        psVar8 = psVar8 + 1;
      } while (sVar2 != 0);
      if ((int)psVar8 - (int)psVar1 >> 1 != *(int *)(p_Var5 + 0x5c)) goto LAB_00472cb4;
      iVar7 = _TestDefaultLanguage(Locale,1);
      if (iVar7 == 0) goto LAB_00472d4f;
      *puVar3 = *puVar3 | 0x100;
    }
    else {
LAB_00472cb4:
      *puVar3 = *puVar3 | 0x100;
    }
    uVar4 = puVar3[1];
  }
  else {
    if ((((*(int *)(p_Var5 + 0x60) != 0) || (*(int *)(p_Var5 + 0x5c) == 0)) ||
        (iVar7 = __wcsicmp(*(wchar_t **)(p_Var5 + 0x50),local_f8), iVar7 != 0)) ||
       (iVar7 = _TestDefaultLanguage(Locale,0), iVar7 == 0)) goto LAB_00472d4f;
    *puVar3 = *puVar3 | 0x100;
    uVar4 = puVar3[1];
  }
  if (uVar4 == 0) {
    puVar3[1] = Locale;
  }
LAB_00472d4f:
  return ~(*puVar3 >> 2) & 1;
}


