// FUN_0045d075 @ 0045d075 size=73 callers=1

void __cdecl FUN_0045d075(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = ___vcrt_getptd();
  if (param_1 == *(int *)(iVar1 + 0x24)) {
    iVar1 = ___vcrt_getptd();
    *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_1 + 4);
  }
  else {
    iVar1 = ___vcrt_getptd();
    iVar1 = *(int *)(iVar1 + 0x24);
    do {
      iVar2 = iVar1;
      if (*(int *)(iVar2 + 4) == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00464131();
      }
      iVar1 = *(int *)(iVar2 + 4);
    } while (param_1 != *(int *)(iVar2 + 4));
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 4);
  }
  return;
}


