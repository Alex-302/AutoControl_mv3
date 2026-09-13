// FUN_004724cf @ 004724cf size=192 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_004724cf(wchar_t *param_1)

{
  wchar_t wVar1;
  __acrt_ptd *p_Var2;
  int iVar3;
  uint uVar4;
  wchar_t *pwVar5;
  WCHAR local_f8 [120];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  p_Var2 = FUN_0046aa74();
  iVar3 = ___acrt_GetLocaleInfoEx_16
                    (param_1,(-(uint)(*(int *)(p_Var2 + 0x60) != 0) & 0xfffff002) + 0x1001,local_f8,
                     0x78);
  if (iVar3 == 0) {
    *(undefined4 *)(p_Var2 + 0x58) = 0;
    uVar4 = 1;
  }
  else {
    iVar3 = __wcsicmp(*(wchar_t **)(p_Var2 + 0x50),local_f8);
    if (iVar3 == 0) {
      pwVar5 = param_1;
      do {
        wVar1 = *pwVar5;
        pwVar5 = pwVar5 + 1;
      } while (wVar1 != L'\0');
      iVar3 = FUN_0047002f((wchar_t *)(p_Var2 + 0x2a0),0x55,param_1,
                           ((int)pwVar5 - (int)(param_1 + 1) >> 1) + 1);
      if (iVar3 != 0) {
                    /* WARNING: Subroutine does not return */
        __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
      }
      *(uint *)(p_Var2 + 0x58) = *(uint *)(p_Var2 + 0x58) | 4;
    }
    uVar4 = ~(*(uint *)(p_Var2 + 0x58) >> 2) & 1;
  }
  return uVar4;
}


