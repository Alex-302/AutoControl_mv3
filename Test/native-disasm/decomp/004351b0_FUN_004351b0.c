// FUN_004351b0 @ 004351b0 size=114 callers=4

void * __thiscall FUN_004351b0(void *this,uint *param_1)

{
  undefined2 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  if (this != param_1) {
    ExceptionList = &local_10;
    if (7 < *(uint *)((int)this + 0x14)) {
      ExceptionList = &local_10;
      FUN_00402430(*(void **)this,*(uint *)((int)this + 0x14) + 1,2);
    }
    *(undefined4 *)((int)this + 0x14) = 7;
    *(undefined4 *)((int)this + 0x10) = 0;
    puVar1 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      puVar1 = *(undefined2 **)this;
    }
    *puVar1 = 0;
    FUN_0043a920(this,param_1);
  }
  ExceptionList = local_10;
  return this;
}


