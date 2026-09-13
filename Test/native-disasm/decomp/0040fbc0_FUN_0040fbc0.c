// FUN_0040fbc0 @ 0040fbc0 size=222 callers=1

void FUN_0040fbc0(undefined4 param_1,undefined4 param_2,UINT_PTR param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *local_8;
  int *local_4;
  
  iVar1 = *(int *)ThreadLocalStoragePointer;
  iVar3 = *(int *)(iVar1 + 4) * 0x20;
  FUN_00436350(&DAT_004a2850 + iVar3,(int *)&local_8,(byte *)&param_3);
  iVar5 = 0;
  piVar4 = local_8;
  if (local_8 != local_4) {
    do {
      piVar4 = (int *)*piVar4;
      iVar5 = iVar5 + 1;
    } while (piVar4 != local_4);
    if (iVar5 != 0) {
      FUN_00436250(&DAT_004a2850 + iVar3,(int *)&local_8,(byte *)&param_3);
      if (local_8 == *(int **)(&DAT_004a2854 + iVar3)) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ee4("invalid unordered_map<K, T> key");
      }
      if ((int *)local_8[0xd] == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
        FUN_00458e87();
      }
      cVar2 = (**(code **)(*(int *)local_8[0xd] + 8))();
      if (cVar2 != '\0') {
        return;
      }
    }
  }
  if (param_3 != 0) {
    KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),param_3);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00436350(&DAT_004a2850 + iVar1 * 0x20,(int *)&local_8,(byte *)&param_3);
    for (piVar4 = local_8; piVar4 != local_4; piVar4 = (int *)*piVar4) {
    }
    FUN_00436710(&DAT_004a2850 + iVar1 * 0x20,&param_3,local_8,local_4);
  }
  return;
}


