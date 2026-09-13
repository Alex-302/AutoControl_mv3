// FUN_004471f0 @ 004471f0 size=203 callers=1

void * __thiscall FUN_004471f0(void *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *in_stack_00000030;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e4b0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  local_8 = 1;
  if (in_stack_00000030 != (int *)0x0) {
    uVar1 = (**(code **)*in_stack_00000030)((int)this + 8);
    *(undefined4 *)((int)this + 0x2c) = uVar1;
  }
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x4c) = 0xf;
  *(undefined4 *)((int)this + 0x48) = 0;
  *(undefined1 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 100) = 0xf;
  *(undefined4 *)((int)this + 0x60) = 0;
  *(undefined1 *)((int)this + 0x50) = 0;
  *(undefined4 *)((int)this + 0x68) = param_1;
  *(undefined4 *)((int)this + 0x74) = param_1;
  *(undefined4 *)((int)this + 0x6c) = param_1;
  *(undefined4 *)((int)this + 0x70) = 0;
  *(undefined4 *)((int)this + 0x7c) = 0xf;
  *(undefined4 *)((int)this + 0x78) = param_2;
  if (in_stack_00000030 != (int *)0x0) {
    (**(code **)(*in_stack_00000030 + 0x10))(in_stack_00000030 != (int *)&stack0x0000000c);
  }
  ExceptionList = local_10;
  return this;
}


