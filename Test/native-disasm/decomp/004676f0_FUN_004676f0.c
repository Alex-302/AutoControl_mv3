// FUN_004676f0 @ 004676f0 size=208 callers=1

undefined4 * __cdecl FUN_004676f0(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *_Dst;
  errno_t eVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *local_8;
  
  iVar5 = 0;
  cVar1 = *param_1;
  pcVar4 = param_1;
  while (cVar1 != '\0') {
    if (cVar1 != '=') {
      iVar5 = iVar5 + 1;
    }
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    cVar1 = *pcVar4;
  }
  puVar2 = __calloc_base(iVar5 + 1,4);
  local_8 = puVar2;
  if (puVar2 == (undefined4 *)0x0) {
LAB_004677a1:
    puVar2 = (undefined4 *)0x0;
  }
  else {
    for (; *param_1 != '\0'; param_1 = param_1 + (int)pcVar4) {
      pcVar4 = param_1;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      pcVar4 = pcVar4 + (1 - (int)(param_1 + 1));
      if (*param_1 != '=') {
        _Dst = __calloc_base((uint)pcVar4,1);
        if (_Dst == (char *)0x0) {
          free_environment<>(puVar2);
          FID_conflict__free((void *)0x0);
          goto LAB_004677a1;
        }
        eVar3 = _strcpy_s(_Dst,(rsize_t)pcVar4,param_1);
        if (eVar3 != 0) {
                    /* WARNING: Subroutine does not return */
          __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        *local_8 = _Dst;
        local_8 = local_8 + 1;
        FID_conflict__free((void *)0x0);
      }
    }
  }
  FID_conflict__free((void *)0x0);
  return puVar2;
}


