// FUN_00456ba0 @ 00456ba0 size=127 callers=1

void * __thiscall FUN_00456ba0(void *this,undefined4 *param_1)

{
  undefined1 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dfe8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(undefined4 *)((int)this + 0x10) = 0;
  puVar1 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar1 = *(undefined1 **)this;
  }
  *puVar1 = 0;
  FUN_0043ade0(this,param_1,0,0xffffffff);
  local_8 = 0;
  FUN_00434940((void *)((int)this + 0x18),(undefined1 *)(param_1 + 6));
  ExceptionList = local_10;
  return this;
}


