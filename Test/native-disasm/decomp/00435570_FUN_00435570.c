// FUN_00435570 @ 00435570 size=112 callers=4

void * __thiscall FUN_00435570(void *this,uint *param_1)

{
  undefined1 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  if (this != param_1) {
    ExceptionList = &local_10;
    if (0xf < *(uint *)((int)this + 0x14)) {
      ExceptionList = &local_10;
      FUN_00402430(*(void **)this,*(uint *)((int)this + 0x14) + 1,1);
    }
    *(undefined4 *)((int)this + 0x14) = 0xf;
    *(undefined4 *)((int)this + 0x10) = 0;
    puVar1 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      puVar1 = *(undefined1 **)this;
    }
    *puVar1 = 0;
    FUN_0043b1c0(this,param_1);
  }
  ExceptionList = local_10;
  return this;
}


