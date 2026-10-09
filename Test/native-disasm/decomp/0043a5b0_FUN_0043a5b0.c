// FUN_0043a5b0 @ 0043a5b0 size=151 callers=3

void * __thiscall FUN_0043a5b0(void *this,uint param_1,undefined2 param_2)

{
  if (param_1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (0x7ffffffe < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_1) {
    FUN_0043d830(this,param_1);
    if (param_1 == 0) {
      return this;
    }
  }
  else if (param_1 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (*(uint *)((int)this + 0x14) < 8) {
      *(undefined2 *)this = 0;
      return this;
    }
    **(undefined2 **)this = 0;
    return this;
  }
  FUN_0043a100(this,0,param_1,param_2);
  *(uint *)((int)this + 0x10) = param_1;
  if (*(uint *)((int)this + 0x14) < 8) {
    *(undefined2 *)((int)this + param_1 * 2) = 0;
    return this;
  }
  *(undefined2 *)(*(int *)this + param_1 * 2) = 0;
  return this;
}


