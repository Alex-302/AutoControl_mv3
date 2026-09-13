// FUN_00428ed0 @ 00428ed0 size=341 callers=1

void __fastcall FUN_00428ed0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aedc;
  local_10 = ExceptionList;
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  uVar2 = *(undefined4 *)param_1[0x14];
  ExceptionList = &local_10;
  *(undefined4 *)param_1[0x14] = DAT_004a29e8;
  DAT_004a29e8 = uVar2;
  FUN_0043ace0(local_30,(uint *)"usesJoystk",10);
  if (*(char *)param_1[0x15] == '\x01') {
    FUN_004437f0(*(void **)((char *)param_1[0x15] + 8),(int *)&local_18,(byte *)local_30);
    iVar3 = FUN_00447a70(local_18,local_14);
  }
  else {
    iVar3 = 0;
  }
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  DAT_004a23c7 = iVar3 != 0;
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_004073f0(DAT_004a23c7);
  FUN_00412ad0();
  FUN_004339e0(&DAT_004a25f8,param_1);
  puVar1 = param_1 + 4;
  DAT_004a25f0 = DAT_004a25ec;
  DAT_004a260c = DAT_004a2608;
  DAT_004a263c = 0;
  if (puVar1 != &DAT_004a29f0) {
    FUN_0043ee10(puVar1);
    local_8 = 0;
    FUN_0043edd0(param_1 + 5);
    FUN_00435e50(puVar1,8);
    local_8 = 0xffffffff;
  }
  puVar1 = param_1 + 0xc;
  if (puVar1 != &DAT_004a2a10) {
    FUN_0043ecd0(puVar1);
    local_8 = 1;
    FUN_0043e550(param_1 + 0xd);
    FUN_00435e50(puVar1,8);
  }
  ExceptionList = local_10;
  return;
}


