// FUN_0040fb40 @ 0040fb40 size=122 callers=7

void __fastcall FUN_0040fb40(UINT_PTR *param_1,char param_2)

{
  int iVar1;
  int *piVar2;
  int *local_8;
  int *local_4;
  
  if (*param_1 != 0) {
    iVar1 = *(int *)ThreadLocalStoragePointer;
    KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),*param_1);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00436350(&DAT_004a2850 + iVar1 * 0x20,(int *)&local_8,(byte *)param_1);
    for (piVar2 = local_8; piVar2 != local_4; piVar2 = (int *)*piVar2) {
    }
    FUN_00436710(&DAT_004a2850 + iVar1 * 0x20,&local_8,local_8,local_4);
    if (param_2 != '\0') {
      *param_1 = 0;
    }
  }
  return;
}


