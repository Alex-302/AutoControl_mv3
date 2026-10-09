// FUN_004276d0 @ 004276d0 size=406 callers=1

void __fastcall FUN_004276d0(void *param_1)

{
  char cVar1;
  uint uVar2;
  char cVar3;
  byte bVar4;
  void *local_70 [4];
  undefined4 local_60;
  uint local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c640;
  local_10 = ExceptionList;
  local_5c = 0xf;
  local_60 = 0;
  local_70[0] = (void *)((uint)local_70[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_70,(uint *)"thumbSize",9);
  local_8 = 0;
  local_44 = 0xf;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  FUN_0043ace0(local_58,(uint *)"maxPrevsPerCycle",0x10);
  local_8._0_1_ = 1;
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  FUN_0043ace0(local_40,(uint *)"numCycles",9);
  local_8._0_1_ = 2;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"interval",8);
  local_8 = CONCAT31(local_8._1_3_,3);
  uVar2 = FUN_004409d0(param_1,local_70,0);
  bVar4 = (byte)uVar2;
  uVar2 = FUN_004409d0(param_1,local_58,0);
  cVar3 = (char)uVar2;
  uVar2 = FUN_004409d0(param_1,local_40,0);
  cVar1 = (char)uVar2;
  uVar2 = FUN_004409d0(param_1,local_28,1000);
  FUN_004226e0((ushort)uVar2,cVar1,cVar3,bVar4);
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  if (0xf < local_2c) {
    FUN_00402430(local_40[0],local_2c + 1,1);
  }
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  if (0xf < local_44) {
    FUN_00402430(local_58[0],local_44 + 1,1);
  }
  local_44 = 0xf;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  if (0xf < local_5c) {
    FUN_00402430(local_70[0],local_5c + 1,1);
  }
  ExceptionList = local_10;
  return;
}


