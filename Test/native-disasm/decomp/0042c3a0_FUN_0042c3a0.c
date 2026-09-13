// FUN_0042c3a0 @ 0042c3a0 size=153 callers=1

void __cdecl FUN_0042c3a0(undefined1 *param_1,undefined4 param_2)

{
  undefined **local_44;
  undefined4 local_40;
  int local_3c;
  undefined ***local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  local_3c = (int)&param_2 + 3;
  local_40 = param_2;
  local_20 = &local_44;
  local_14 = 0;
  local_44 = &PTR_LAB_0048e3a0;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_0040f7a0(DAT_004a23dc,(int *)local_20);
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])(local_20 != &local_44);
  }
  local_1c = CONCAT31(local_1c._1_3_,param_2._3_1_);
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 8) = local_1c;
  *(undefined4 *)(param_1 + 0xc) = local_18;
  *param_1 = 4;
  ExceptionList = local_10;
  return;
}


