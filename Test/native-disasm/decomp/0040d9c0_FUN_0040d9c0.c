// FUN_0040d9c0 @ 0040d9c0 size=126 callers=1

void * __thiscall FUN_0040d9c0(void *this,undefined4 *param_1)

{
  uint *this_00;
  uint *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = *param_1;
  this_00 = (uint *)((int)this + 4);
  if (this_00 != param_1 + 1) {
    if (0xf < *(uint *)((int)this + 0x18)) {
      FUN_00402430((void *)*this_00,*(uint *)((int)this + 0x18) + 1,1);
    }
    *(undefined4 *)((int)this + 0x18) = 0xf;
    *(undefined4 *)((int)this + 0x14) = 0;
    puVar1 = this_00;
    if (0xf < *(uint *)((int)this + 0x18)) {
      puVar1 = (uint *)*this_00;
    }
    *(undefined1 *)puVar1 = 0;
    FUN_0043b1c0(this_00,param_1 + 1);
  }
  ExceptionList = local_10;
  return this;
}


