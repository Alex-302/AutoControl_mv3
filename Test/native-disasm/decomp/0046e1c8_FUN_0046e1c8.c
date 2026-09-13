// FUN_0046e1c8 @ 0046e1c8 size=433 callers=46

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl
FUN_0046e1c8(__crt_locale_pointers *param_1,int param_2,wchar_t *param_3,uint param_4,int *param_5)

{
  uint uVar1;
  LPVOID pvVar2;
  int iVar3;
  DWORD DVar4;
  LPWSTR _Memory;
  undefined4 uVar5;
  wchar_t *local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  uVar5 = 0;
  local_8c = param_3;
  *param_5 = 0;
  if (param_2 == 1) {
    uVar1 = InternalGetLocaleInfoA(param_1,param_3,param_4,local_88,0x80);
    if (uVar1 != 0) {
      pvVar2 = __calloc_base(uVar1,1);
      *param_5 = (int)pvVar2;
      FID_conflict__free((void *)0x0);
      if (*param_5 == 0) {
        return 0xffffffff;
      }
      iVar3 = FUN_004754f8((char *)*param_5,uVar1,local_88,uVar1 - 1);
      if (iVar3 == 0) {
        return 0;
      }
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    DVar4 = GetLastError();
    if (DVar4 != 0x7a) {
      return 0xffffffff;
    }
    uVar1 = InternalGetLocaleInfoA(param_1,param_3,param_4,(char *)0x0,0);
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    _Memory = __calloc_base(uVar1,1);
    if (_Memory != (LPWSTR)0x0) {
      iVar3 = InternalGetLocaleInfoA(param_1,local_8c,param_4,(char *)_Memory,uVar1);
LAB_0046e2cd:
      if (iVar3 != 0) {
        *param_5 = (int)_Memory;
        _Memory = (LPWSTR)0x0;
        goto LAB_0046e2dc;
      }
    }
  }
  else {
    if (param_2 != 2) {
      if (param_2 != 0) {
        return 0xffffffff;
      }
      local_8c = (wchar_t *)0x0;
      iVar3 = ___acrt_GetLocaleInfoEx_16(param_3,param_4 | 0x20000000,(LPWSTR)&local_8c,2);
      if (iVar3 == 0) {
        return 0xffffffff;
      }
      *(undefined1 *)param_5 = local_8c._0_1_;
      return 0;
    }
    uVar1 = ___acrt_GetLocaleInfoEx_16(param_3,param_4,(LPWSTR)0x0,0);
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    _Memory = __calloc_base(uVar1,2);
    if (_Memory != (LPWSTR)0x0) {
      iVar3 = ___acrt_GetLocaleInfoEx_16(local_8c,param_4,_Memory,uVar1);
      goto LAB_0046e2cd;
    }
  }
  uVar5 = 0xffffffff;
LAB_0046e2dc:
  FID_conflict__free(_Memory);
  return uVar5;
}


