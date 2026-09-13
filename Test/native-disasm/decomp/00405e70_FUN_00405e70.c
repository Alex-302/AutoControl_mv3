// FUN_00405e70 @ 00405e70 size=406 callers=1

void __fastcall FUN_00405e70(void *param_1)

{
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
  puStack_c = &LAB_004794f0;
  local_10 = ExceptionList;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_28,(uint *)"dirPrecision",0xc);
  local_8 = 0;
  DAT_0049d9fc = FUN_004409d0(param_1,local_28,DAT_0049d9fc);
  local_8 = 0xffffffff;
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"stepSize",8);
  local_8 = 1;
  DAT_0049da00 = FUN_004409d0(param_1,local_28,DAT_0049da00);
  local_8 = 0xffffffff;
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"dirChangeSens",0xd);
  local_8 = 2;
  DAT_0049da08 = FUN_004409d0(param_1,local_28,DAT_0049da08);
  local_8 = 0xffffffff;
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  FUN_0043ace0(local_40,(uint *)"segmentSize",0xb);
  local_8 = 3;
  DAT_0049d9ec = FUN_004409d0(param_1,local_40,DAT_0049d9ec);
  if (0xf < local_2c) {
    FUN_00402430(local_40[0],local_2c + 1,1);
  }
  ExceptionList = local_10;
  return;
}


