// FUN_00405c80 @ 00405c80 size=365 callers=1

void * __thiscall FUN_00405c80(void *this,void *param_1)

{
  uint uVar1;
  void *local_50 [4];
  undefined4 local_40;
  uint local_3c;
  void *local_38 [4];
  undefined4 local_28;
  uint local_24;
  void *local_20;
  uint local_1c;
  undefined1 local_15;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047949a;
  local_10 = ExceptionList;
  local_8 = 0;
  local_1c = local_1c & 0xffffff00;
  local_15 = 0;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_20 = this;
  FUN_00447980(this,(uint *)&local_15,(int)local_14);
  local_8._0_1_ = 2;
  local_8._1_3_ = 0;
  local_1c = local_1c & 0xffffff00;
  local_15 = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  FUN_00447980((undefined4 *)((int)this + 0x1c),(uint *)&local_15,(int)local_14);
  local_8._0_1_ = 3;
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  FUN_0043ace0(local_38,(uint *)"usedDevs",8);
  local_8._0_1_ = 4;
  FUN_00440aa0(param_1,(int *)((int)this + 0x38),local_38,(void *)0x0,0,0);
  local_8._0_1_ = 6;
  if (0xf < local_24) {
    FUN_00402430(local_38[0],local_24 + 1,1);
  }
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  local_3c = 0xf;
  local_40 = 0;
  local_50[0] = (void *)((uint)local_50[0] & 0xffffff00);
  FUN_0043ace0(local_50,(uint *)"lastStepId",10);
  local_8 = CONCAT31(local_8._1_3_,7);
  uVar1 = FUN_004409d0(param_1,local_50,0);
  *(char *)((int)this + 0x44) = (char)uVar1;
  if (0xf < local_3c) {
    FUN_00402430(local_50[0],local_3c + 1,1);
  }
  ExceptionList = local_10;
  return this;
}


