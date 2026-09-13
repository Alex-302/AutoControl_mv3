// FUN_00470f68 @ 00470f68 size=176 callers=1

LPVOID __cdecl FUN_00470f68(int *param_1)

{
  char *pcVar1;
  char cVar2;
  int *piVar3;
  LPVOID pvVar4;
  LPVOID pvVar5;
  errno_t eVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  
  if (param_1 == (int *)0x0) {
    pvVar4 = (LPVOID)0x0;
  }
  else {
    iVar7 = 0;
    iVar9 = *param_1;
    piVar3 = param_1;
    while (iVar9 != 0) {
      piVar3 = piVar3 + 1;
      iVar7 = iVar7 + 1;
      iVar9 = *piVar3;
    }
    pvVar4 = __calloc_base(iVar7 + 1,4);
    if (pvVar4 == (LPVOID)0x0) {
LAB_00471007:
                    /* WARNING: Subroutine does not return */
      _abort();
    }
    if (*param_1 != 0) {
      iVar9 = (int)pvVar4 - (int)param_1;
      do {
        pcVar8 = (char *)*param_1;
        pcVar1 = pcVar8 + 1;
        do {
          cVar2 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        pvVar5 = __calloc_base((uint)(pcVar8 + (1 - (int)pcVar1)),1);
        *(LPVOID *)(iVar9 + (int)param_1) = pvVar5;
        FID_conflict__free((void *)0x0);
        if (*(int *)(iVar9 + (int)param_1) == 0) goto LAB_00471007;
        eVar6 = _strcpy_s(*(char **)(iVar9 + (int)param_1),(rsize_t)(pcVar8 + (1 - (int)pcVar1)),
                          (char *)*param_1);
        if (eVar6 != 0) {
                    /* WARNING: Subroutine does not return */
          __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        param_1 = param_1 + 1;
      } while (*param_1 != 0);
    }
    FID_conflict__free((void *)0x0);
  }
  return pvVar4;
}


