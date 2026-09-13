// FUN_00472731 @ 00472731 size=462 callers=1

undefined4 __cdecl FUN_00472731(int param_1,UINT *param_2,LPWSTR param_3)

{
  __acrt_ptd *p_Var1;
  __acrt_ptd *p_Var2;
  wchar_t *pwVar3;
  LPWSTR pWVar4;
  wchar_t wVar5;
  bool bVar6;
  __acrt_ptd *p_Var7;
  undefined3 extraout_var;
  UINT _Val;
  BOOL BVar8;
  int iVar9;
  ushort *puVar10;
  __acrt_ptd *p_Var11;
  
  p_Var7 = FUN_0046aa74();
  p_Var11 = p_Var7 + 0x50;
  p_Var2 = p_Var7 + 0x2a0;
  *(undefined4 *)(p_Var7 + 0x58) = 0;
  *(wchar_t *)p_Var2 = L'\0';
  p_Var1 = p_Var7 + 0x54;
  *(int *)p_Var11 = param_1;
  *(short **)p_Var1 = (short *)(param_1 + 0x80);
  if (*(short *)(param_1 + 0x80) != 0) {
    _TranslateName(0x4878e8,0x16,(int *)p_Var1);
  }
  if (**(short **)p_Var11 == 0) {
    FUN_00472033((int)p_Var11);
  }
  else {
    if (**(short **)p_Var1 == 0) {
      _GetLocaleNameFromLanguage((undefined4 *)p_Var11);
    }
    else {
      _GetLocaleNameFromLangCountry((undefined4 *)p_Var11);
    }
    if ((*(int *)(p_Var7 + 0x58) == 0) &&
       (bVar6 = _TranslateName(0x4875d8,0x40,(int *)p_Var11), CONCAT31(extraout_var,bVar6) != 0)) {
      if (**(short **)p_Var1 == 0) {
        _GetLocaleNameFromLanguage((undefined4 *)p_Var11);
      }
      else {
        _GetLocaleNameFromLangCountry((undefined4 *)p_Var11);
      }
    }
  }
  if ((((*(int *)(p_Var7 + 0x58) != 0) &&
       (_Val = _ProcessCodePage((wchar_t *)(param_1 + 0x100),(int)p_Var11), _Val != 0)) &&
      (_Val != 65000)) && ((_Val != 0xfde9 && (BVar8 = IsValidCodePage(_Val & 0xffff), BVar8 != 0)))
     ) {
    if (param_2 != (UINT *)0x0) {
      *param_2 = _Val;
    }
    if (param_3 == (LPWSTR)0x0) {
      return 1;
    }
    pwVar3 = param_3 + 0x90;
    *pwVar3 = L'\0';
    p_Var11 = p_Var2;
    do {
      wVar5 = *(wchar_t *)p_Var11;
      p_Var11 = p_Var11 + 2;
    } while (wVar5 != L'\0');
    iVar9 = FUN_0047002f(pwVar3,0x55,(wchar_t *)p_Var2,
                         ((int)p_Var11 - (int)(p_Var7 + 0x2a2) >> 1) + 1);
    if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    iVar9 = ___acrt_GetLocaleInfoEx_16(pwVar3,0x1001,param_3,0x40);
    if (iVar9 != 0) {
      pWVar4 = param_3 + 0x40;
      iVar9 = ___acrt_GetLocaleInfoEx_16(param_3 + 0x90,0x1002,pWVar4,0x40);
      if ((iVar9 != 0) &&
         (((puVar10 = FUN_00477a87((ushort *)pWVar4,0x5f), puVar10 == (ushort *)0x0 &&
           (puVar10 = FUN_00477a87((ushort *)pWVar4,0x2e), puVar10 == (ushort *)0x0)) ||
          (iVar9 = ___acrt_GetLocaleInfoEx_16(param_3 + 0x90,7,pWVar4,0x40), iVar9 != 0)))) {
        __itow_s(_Val,param_3 + 0x80,0x10,10);
        return 1;
      }
    }
  }
  return 0;
}


