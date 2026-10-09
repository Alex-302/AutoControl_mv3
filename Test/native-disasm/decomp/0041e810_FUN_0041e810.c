// FUN_0041e810 @ 0041e810 size=248 callers=5

void FUN_0041e810(void)

{
  int iVar1;
  int *piVar2;
  undefined **local_44;
  HWND local_40;
  undefined ***local_20;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_004a2440 != 0) {
    iVar1 = *(int *)ThreadLocalStoragePointer;
    ExceptionList = &local_10;
    KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar1 + 4) * 4),DAT_004a2440);
    iVar1 = *(int *)(iVar1 + 4);
    FUN_00436350(&DAT_004a2850 + iVar1 * 0x20,(int *)&local_18,(byte *)&DAT_004a2440);
    for (piVar2 = local_18; piVar2 != local_14; piVar2 = (int *)*piVar2) {
    }
    FUN_00436710(&DAT_004a2850 + iVar1 * 0x20,&local_14,local_18,local_14);
    DAT_004a2440 = 0;
  }
  if (DAT_004a2438 != (HWND)0x0) {
    SendMessageA(DAT_004a2438,0x41c,0,0);
    local_40 = DAT_004a2438;
    local_20 = &local_44;
    local_44 = &PTR_LAB_0048e520;
    local_8 = 0;
    FUN_0040fd50(1000,(int *)local_20);
    if (local_20 != (undefined ***)0x0) {
      (*(code *)(*local_20)[4])(local_20 != &local_44);
    }
    DAT_004a2438 = (HWND)0x0;
  }
  ExceptionList = local_10;
  return;
}


