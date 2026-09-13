// FUN_0046815b @ 0046815b size=886 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

__acrt_ptd * __cdecl
FUN_0046815b(wchar_t *param_1,__acrt_ptd *param_2,rsize_t param_3,__acrt_ptd *param_4,uint param_5,
            undefined4 *param_6)

{
  wchar_t wVar1;
  short sVar2;
  __acrt_ptd *p_Var3;
  int iVar4;
  errno_t eVar5;
  uint uVar6;
  wchar_t *pwVar7;
  __acrt_ptd *p_Var8;
  uint uVar9;
  bool bVar10;
  uint local_1e8;
  __acrt_ptd *local_1e4;
  __acrt_ptd *local_1e0;
  __acrt_ptd *local_1dc;
  __acrt_ptd *local_1d8;
  wchar_t local_1d4 [144];
  wchar_t local_b4;
  undefined1 local_b2 [170];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_1e0 = param_4;
  if (param_1 == (wchar_t *)0x0) {
    return (__acrt_ptd *)0x0;
  }
  p_Var3 = FUN_0046aa74();
  local_1dc = p_Var3 + 0x68;
  local_1e4 = p_Var3 + 0x6c;
  local_1d8 = p_Var3 + 0x172;
  p_Var3 = p_Var3 + 0x2a0;
  local_1e8 = 0;
  iVar4 = FUN_0047002f((wchar_t *)param_4,param_5,(wchar_t *)p_Var3,0x55);
  if (iVar4 != 0) goto LAB_004684cc;
  if ((*param_1 == L'C') && (param_1[1] == L'\0')) {
    eVar5 = _wcscpy_s((wchar_t *)param_2,param_3,L"C");
    if (eVar5 == 0) {
      if (param_6 != (undefined4 *)0x0) {
        *param_6 = 0;
        return param_2;
      }
      return param_2;
    }
    goto LAB_004684cc;
  }
  pwVar7 = param_1;
  do {
    wVar1 = *pwVar7;
    pwVar7 = pwVar7 + 1;
  } while (wVar1 != L'\0');
  uVar9 = (int)pwVar7 - (int)(param_1 + 1) >> 1;
  p_Var8 = local_1d8;
  pwVar7 = param_1;
  if (uVar9 < 0x83) {
    do {
      wVar1 = *(wchar_t *)p_Var8;
      bVar10 = (ushort)wVar1 < (ushort)*pwVar7;
      if (wVar1 != *pwVar7) {
LAB_00468281:
        uVar6 = -(uint)bVar10 | 1;
        goto LAB_00468286;
      }
      if (wVar1 == L'\0') break;
      wVar1 = *(wchar_t *)(p_Var8 + 2);
      bVar10 = (ushort)wVar1 < (ushort)pwVar7[1];
      if (wVar1 != pwVar7[1]) goto LAB_00468281;
      p_Var8 = p_Var8 + 4;
      pwVar7 = pwVar7 + 2;
    } while (wVar1 != L'\0');
    uVar6 = 0;
LAB_00468286:
    p_Var8 = local_1e4;
    pwVar7 = param_1;
    if (uVar6 != 0) {
      do {
        wVar1 = *(wchar_t *)p_Var8;
        bVar10 = (ushort)wVar1 < (ushort)*pwVar7;
        if (wVar1 != *pwVar7) {
LAB_004682bc:
          uVar6 = -(uint)bVar10 | 1;
          goto LAB_004682c1;
        }
        if (wVar1 == L'\0') break;
        wVar1 = *(wchar_t *)(p_Var8 + 2);
        bVar10 = (ushort)wVar1 < (ushort)pwVar7[1];
        if (wVar1 != pwVar7[1]) goto LAB_004682bc;
        p_Var8 = p_Var8 + 4;
        pwVar7 = pwVar7 + 2;
      } while (wVar1 != L'\0');
      uVar6 = 0;
LAB_004682c1:
      if (uVar6 != 0) goto LAB_004682c9;
    }
  }
  else {
LAB_004682c9:
    bVar10 = FUN_00469c24();
    iVar4 = FUN_00467f9b(local_1d4,param_1);
    p_Var8 = local_1dc;
    if (iVar4 == 0) {
      if (bVar10) {
        iVar4 = FUN_00472731((int)local_1d4,(UINT *)local_1dc,local_1d4);
      }
      else {
        iVar4 = ___acrt_get_qualified_locale_downlevel((int)local_1d4,(UINT *)local_1dc,local_1d4);
      }
      if (iVar4 == 0) goto LAB_0046837c;
      FUN_00467f2b((wchar_t *)local_1d8,0x83,local_1d4);
      if (local_1e0 != (__acrt_ptd *)0x0) {
        pwVar7 = &local_b4;
        do {
          wVar1 = *pwVar7;
          pwVar7 = pwVar7 + 1;
        } while (wVar1 != L'\0');
        uVar6 = ((int)pwVar7 - (int)local_b2 >> 1) + 1;
        p_Var3 = local_1e0;
        pwVar7 = &local_b4;
        goto LAB_004683fe;
      }
    }
    else {
LAB_0046837c:
      iVar4 = ___acrt_IsValidLocaleName_4(param_1);
      if (iVar4 == 0) {
        p_Var8 = local_1e0;
        do {
          sVar2 = *(short *)p_Var8;
          p_Var8 = p_Var8 + 2;
        } while (sVar2 != 0);
        iVar4 = FUN_0047002f((wchar_t *)p_Var3,0x55,(wchar_t *)local_1e0,
                             ((int)p_Var8 - (int)(local_1e0 + 2) >> 1) + 1);
        if (iVar4 == 0) {
          return (__acrt_ptd *)0x0;
        }
        goto LAB_004684cc;
      }
      iVar4 = ___acrt_GetLocaleInfoEx_16(param_1,0x20001004,(LPWSTR)&local_1e8,2);
      if ((iVar4 == 0) || (local_1e8 == 0)) {
        local_1e8 = GetACP();
      }
      *(uint *)p_Var8 = local_1e8 & 0xffff;
      uVar6 = uVar9 + 1;
      iVar4 = FUN_0047002f((wchar_t *)local_1d8,0x83,param_1,uVar6);
      if ((iVar4 != 0) ||
         (iVar4 = FUN_0047002f((wchar_t *)local_1e0,param_5,param_1,uVar6), iVar4 != 0))
      goto LAB_004684cc;
      param_5 = 0x55;
      pwVar7 = param_1;
LAB_004683fe:
      iVar4 = FUN_0047002f((wchar_t *)p_Var3,param_5,pwVar7,uVar6);
      if (iVar4 != 0) goto LAB_004684cc;
    }
    if ((*param_1 == L'\0') || (0x82 < uVar9)) {
      *(undefined2 *)local_1e4 = 0;
    }
    else {
      iVar4 = FUN_0047002f((wchar_t *)local_1e4,0x83,param_1,uVar9 + 1);
      if (iVar4 != 0) goto LAB_004684cc;
    }
  }
  p_Var3 = local_1d8;
  if (param_6 != (undefined4 *)0x0) {
    *param_6 = *(undefined4 *)local_1dc;
  }
  eVar5 = _wcscpy_s((wchar_t *)param_2,param_3,(wchar_t *)local_1d8);
  if (eVar5 == 0) {
    return p_Var3;
  }
LAB_004684cc:
                    /* WARNING: Subroutine does not return */
  __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
}


