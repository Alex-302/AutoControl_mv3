// FUN_00472033 @ 00472033 size=136 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_00472033(int param_1)

{
  wchar_t wVar1;
  int iVar2;
  wchar_t *pwVar3;
  wchar_t local_b4;
  undefined1 local_b2 [170];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x104;
  iVar2 = ___acrt_GetUserDefaultLocaleName_8(&local_b4,0x55);
  if (1 < iVar2) {
    pwVar3 = &local_b4;
    do {
      wVar1 = *pwVar3;
      pwVar3 = pwVar3 + 1;
    } while (wVar1 != L'\0');
    iVar2 = FUN_0047002f((wchar_t *)(param_1 + 0x250),0x55,&local_b4,
                         ((int)pwVar3 - (int)local_b2 >> 1) + 1);
    if (iVar2 != 0) {
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
  }
  return;
}


