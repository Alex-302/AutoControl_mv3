// FUN_004226e0 @ 004226e0 size=315 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004226e0(ushort param_1,char param_2,char param_3,byte param_4)

{
  int iVar1;
  int *piVar2;
  undefined **local_40;
  undefined *local_3c;
  undefined ***local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b848;
  local_10 = ExceptionList;
  if (param_2 != '\0') {
    DAT_004a27aa = param_2;
  }
  if (param_3 != '\0') {
    DAT_004a27ab = param_3;
  }
  if (param_4 != 0) {
    _DAT_004a27a8 = (param_4 + 10) * 10;
  }
  ExceptionList = &local_10;
  if (DAT_004a279c != 0) {
    iVar1 = *(int *)ThreadLocalStoragePointer;
    ExceptionList = &local_10;
    KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),DAT_004a279c);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00436350(&DAT_004a2850 + iVar1 * 0x20,(int *)&local_18,(byte *)&DAT_004a279c);
    for (piVar2 = local_18; piVar2 != local_14; piVar2 = (int *)*piVar2) {
    }
    FUN_00436710(&DAT_004a2850 + iVar1 * 0x20,(undefined4 *)&param_2,local_18,local_14);
    DAT_004a279c = 0;
  }
  if (param_1 != 0) {
    local_1c = &local_40;
    local_40 = &PTR_LAB_0048eef0;
    local_3c = &DAT_004a2770;
    local_8 = 0;
    DAT_004a279c = FUN_0040fca0((uint)param_1,(int *)&local_40);
    if (local_1c != (undefined ***)0x0) {
      (*(code *)(*local_1c)[4])(local_1c != &local_40);
    }
  }
  ExceptionList = local_10;
  return;
}


