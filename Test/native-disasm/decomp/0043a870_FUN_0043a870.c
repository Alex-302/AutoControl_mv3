// FUN_0043a870 @ 0043a870 size=174 callers=13

void * __thiscall FUN_0043a870(void *this,uint param_1,undefined2 param_2)

{
  uint uVar1;
  
  if (~*(uint *)((int)this + 0x10) <= param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = *(uint *)((int)this + 0x10) + param_1;
  if (param_1 != 0) {
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043d830(this,uVar1);
      if (uVar1 == 0) {
        return this;
      }
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 8) {
        *(undefined2 *)this = 0;
        return this;
      }
      **(undefined2 **)this = 0;
      return this;
    }
    FUN_0043a100(this,*(int *)((int)this + 0x10),param_1,param_2);
    *(uint *)((int)this + 0x10) = uVar1;
    if (7 < *(uint *)((int)this + 0x14)) {
      *(undefined2 *)(*(int *)this + uVar1 * 2) = 0;
      return this;
    }
    *(undefined2 *)((int)this + uVar1 * 2) = 0;
  }
  return this;
}


