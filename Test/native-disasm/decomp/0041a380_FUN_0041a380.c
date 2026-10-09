// FUN_0041a380 @ 0041a380 size=192 callers=2

undefined4 __fastcall FUN_0041a380(int param_1)

{
  float fVar1;
  int *piVar2;
  undefined4 *puVar3;
  int local_24 [2];
  undefined4 *local_1c;
  undefined *local_18;
  float local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b648;
  local_10 = ExceptionList;
  if (*(char *)(param_1 + 0x24) != '3') {
    fVar1 = *(float *)(param_1 + 0x20);
    if (fVar1 != 0.0) {
      local_18 = &DAT_004a292c;
      if (*(char *)(param_1 + 0x24) != ',') {
        local_18 = &DAT_004a290c;
      }
      ExceptionList = &local_10;
      local_14 = fVar1;
      FUN_00436250(local_18,(int *)&local_1c,(byte *)&local_14);
      puVar3 = local_1c;
      if (local_1c == *(undefined4 **)(local_18 + 4)) {
        FUN_0041a1e0((int *)&local_1c,fVar1,*(int **)(param_1 + 0x18));
        local_8 = 0;
        piVar2 = FUN_00441e80(local_18,local_24,&local_14,&local_1c);
        puVar3 = (undefined4 *)*piVar2;
        if (local_1c != (undefined4 *)0x0) {
          (**(code **)*local_1c)(1);
        }
      }
      ExceptionList = local_10;
      return puVar3[3];
    }
  }
  return 0;
}


