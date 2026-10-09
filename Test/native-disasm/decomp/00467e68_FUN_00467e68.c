// FUN_00467e68 @ 00467e68 size=101 callers=2

wchar_t * __cdecl FUN_00467e68(wchar_t *param_1)

{
  uint uVar1;
  wchar_t *pwVar2;
  int iVar3;
  
  if (param_1 == (wchar_t *)0x0) {
    return (wchar_t *)0x0;
  }
  uVar1 = FUN_00466f34(param_1,0x55);
  if (uVar1 < 0x55) {
    pwVar2 = __malloc_base(uVar1 * 2 + 2);
    if ((pwVar2 != (wchar_t *)0x0) &&
       (iVar3 = FUN_0047002f(pwVar2,uVar1 + 1,param_1,uVar1 + 1), iVar3 != 0)) {
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
  }
  else {
    pwVar2 = (wchar_t *)0x0;
  }
  return pwVar2;
}


