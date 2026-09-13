// FUN_00428310 @ 00428310 size=146 callers=1

void __fastcall FUN_00428310(undefined4 *param_1,undefined1 param_2)

{
  uint in_stack_ffffffa0;
  void *pvVar1;
  undefined **local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined ***local_24;
  undefined1 local_18 [8];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b1a8;
  local_10 = ExceptionList;
  local_44 = local_18;
  local_48 = &PTR_LAB_0048e5b4;
  local_40 = &stack0x00000004;
  local_24 = &local_48;
  local_8 = 0;
  pvVar1 = (void *)(in_stack_ffffffa0 & 0xffff0000);
  ExceptionList = &local_10;
  local_18[0] = param_2;
  FUN_0043a750(&stack0xffffffa0,param_1,0,0xffffffff);
  FUN_00427f50(pvVar1);
  if (local_24 != (undefined ***)0x0) {
    (*(code *)(*local_24)[4])();
  }
  ExceptionList = local_10;
  return;
}


