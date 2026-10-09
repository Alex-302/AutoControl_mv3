// FUN_00467f2b @ 00467f2b size=111 callers=1

void __cdecl FUN_00467f2b(wchar_t *param_1,rsize_t param_2,wchar_t *param_3)

{
  errno_t eVar1;
  
  eVar1 = _wcscpy_s(param_1,param_2,param_3);
  if (eVar1 == 0) {
    if (param_3[0x40] != L'\0') {
      FUN_004684d2(param_1,param_2,2);
    }
    if (param_3[0x80] != L'\0') {
      FUN_004684d2(param_1,param_2,2);
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
}


