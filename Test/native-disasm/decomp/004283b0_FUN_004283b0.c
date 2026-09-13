// FUN_004283b0 @ 004283b0 size=140 callers=1

void __fastcall FUN_004283b0(undefined4 *param_1,undefined1 param_2)

{
  uint in_stack_ffffffa4;
  void *pvVar1;
  undefined **local_44;
  undefined1 *local_40;
  undefined ***local_20;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  local_40 = local_14;
  local_44 = &PTR_LAB_0048ea20;
  local_20 = &local_44;
  local_8 = 0;
  pvVar1 = (void *)(in_stack_ffffffa4 & 0xffff0000);
  ExceptionList = &local_10;
  local_14[0] = param_2;
  FUN_0043a750(&stack0xffffffa4,param_1,0,0xffffffff);
  FUN_00427f50(pvVar1);
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])();
  }
  ExceptionList = local_10;
  return;
}


