// FUN_00440fd0 @ 00440fd0 size=201 callers=2

char * __fastcall FUN_00440fd0(char *param_1,char *param_2)

{
  undefined1 *puVar1;
  void *this;
  int *in_stack_00000028;
  undefined1 auStack_d8 [36];
  undefined4 local_b4;
  char *pcVar2;
  undefined1 local_9c [44];
  int *local_70;
  undefined1 local_68 [80];
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047e04b;
  local_10 = ExceptionList;
  local_18 = 0;
  local_14 = auStack_d8;
  local_b4 = 0;
  local_8 = 1;
  uStack_7 = 0;
  ExceptionList = &local_10;
  pcVar2 = param_1;
  puVar1 = auStack_d8;
  if (in_stack_00000028 != (int *)0x0) {
    ExceptionList = &local_10;
    local_b4 = (**(code **)*in_stack_00000028)(auStack_d8);
    puVar1 = local_14;
  }
  local_14 = puVar1;
  local_8 = 0;
  this = FUN_00444080(local_9c,param_2);
  _local_8 = CONCAT31(uStack_7,2);
  local_b4 = 0x441044;
  FUN_00443f70(this,pcVar2);
  FUN_0040da40((int)local_68);
  if (local_70 != (int *)0x0) {
    local_b4 = 0x441067;
    (**(code **)(*local_70 + 0x10))();
    local_70 = (int *)0x0;
  }
  if (in_stack_00000028 != (int *)0x0) {
    local_b4 = 0x441086;
    (**(code **)(*in_stack_00000028 + 0x10))();
  }
  ExceptionList = local_10;
  return param_1;
}


