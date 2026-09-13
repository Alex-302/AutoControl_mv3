// FUN_004684d2 @ 004684d2 size=64 callers=4

void __cdecl FUN_004684d2(wchar_t *param_1,rsize_t param_2,int param_3)

{
  errno_t eVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  if (0 < param_3) {
    piVar3 = &param_3;
    do {
      piVar3 = piVar3 + 1;
      eVar1 = _wcscat_s(param_1,param_2,(wchar_t *)*piVar3);
      if (eVar1 != 0) {
                    /* WARNING: Subroutine does not return */
        __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_3);
  }
  return;
}


