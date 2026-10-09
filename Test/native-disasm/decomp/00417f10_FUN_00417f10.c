// FUN_00417f10 @ 00417f10 size=231 callers=3

void FUN_00417f10(undefined1 param_1)

{
  int iVar1;
  int *piVar2;
  undefined **local_48;
  int *local_44;
  undefined *local_40;
  undefined ***local_24;
  int *local_1c;
  int *local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b1a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_004a24fc != 0) {
    iVar1 = *(int *)ThreadLocalStoragePointer;
    ExceptionList = &local_10;
    KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),DAT_004a24fc);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00436350(&DAT_004a2850 + iVar1 * 0x20,(int *)&local_1c,(byte *)&DAT_004a24fc);
    for (piVar2 = local_1c; piVar2 != local_18[0]; piVar2 = (int *)*piVar2) {
    }
    FUN_00436710(&DAT_004a2850 + iVar1 * 0x20,local_18,local_1c,local_18[0]);
    DAT_004a24fc = 0;
  }
  local_1c = (int *)CONCAT31(local_1c._1_3_,param_1);
  local_44 = local_1c;
  local_24 = &local_48;
  local_48 = &PTR_LAB_0048e59c;
  local_40 = &DAT_004a24d0;
  local_8 = 0;
  DAT_004a24fc = FUN_0040fd50(0x32,(int *)local_24);
  if (local_24 != (undefined ***)0x0) {
    (*(code *)(*local_24)[4])(local_24 != &local_48);
  }
  ExceptionList = local_10;
  return;
}


