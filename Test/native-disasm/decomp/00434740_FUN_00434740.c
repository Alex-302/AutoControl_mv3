// FUN_00434740 @ 00434740 size=213 callers=2

undefined1 * __thiscall FUN_00434740(void *this,undefined1 *param_1)

{
  int local_12c [4];
  undefined1 local_11c [88];
  undefined **local_c4 [18];
  undefined1 local_7c [76];
  void *local_30;
  undefined4 local_20;
  uint local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047db69;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_0043b330(local_12c);
  local_8 = 0;
  FUN_00437fb0(local_7c,local_11c);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00437ab0(local_7c,this,'\0',0,0);
  FUN_0043b230(local_12c,param_1);
  if (0xf < local_1c) {
    FUN_00402430(local_30,local_1c + 1,1);
  }
  local_1c = 0xf;
  local_20 = 0;
  local_30 = (void *)((uint)local_30 & 0xffffff00);
  FUN_0043b250((int)local_c4);
  local_8 = 2;
  local_c4[0] = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor((ios_base *)local_c4);
  ExceptionList = local_10;
  return param_1;
}


