// FUN_004420c0 @ 004420c0 size=244 callers=1

char * __fastcall FUN_004420c0(char *param_1,int param_2,int param_3)

{
  void *this;
  int *in_stack_0000002c;
  undefined1 auStack_dc [36];
  undefined4 local_b8;
  char *pcVar1;
  undefined1 local_a0 [44];
  int *local_74;
  undefined1 local_6c [76];
  undefined4 local_20;
  char *local_1c;
  undefined1 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e0f6;
  local_10 = ExceptionList;
  local_20 = 0;
  local_8 = 0;
  pcVar1 = param_1;
  local_1c = param_1;
  if (param_3 == param_2 || param_3 - param_2 < 0) {
    local_b8 = 0;
    ExceptionList = &local_10;
    this = FUN_00444080(local_a0,"");
    local_8 = CONCAT31(local_8._1_3_,1);
  }
  else {
    local_b8 = 0;
    local_8._0_1_ = 2;
    local_8._1_3_ = 0;
    ExceptionList = &local_10;
    local_18 = auStack_dc;
    if (in_stack_0000002c != (int *)0x0) {
      ExceptionList = &local_10;
      local_18 = auStack_dc;
      local_b8 = (**(code **)*in_stack_0000002c)(auStack_dc);
    }
    local_8._0_1_ = 0;
    this = FUN_004471f0(local_a0,param_2,param_3);
    local_8 = CONCAT31(local_8._1_3_,3);
  }
  local_b8 = 0x44215f;
  FUN_00443f70(this,pcVar1);
  FUN_0040da40((int)local_6c);
  if (local_74 != (int *)0x0) {
    local_b8 = 0x442182;
    (**(code **)(*local_74 + 0x10))();
    local_74 = (int *)0x0;
  }
  if (in_stack_0000002c != (int *)0x0) {
    local_b8 = 0x4421a1;
    (**(code **)(*in_stack_0000002c + 0x10))();
  }
  ExceptionList = local_10;
  return param_1;
}


