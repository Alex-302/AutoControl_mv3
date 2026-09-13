// FUN_0043a080 @ 0043a080 size=112 callers=1

bool __thiscall FUN_0043a080(void *this,uint param_1,char param_2)

{
  uint uVar1;
  
  if (0x7ffffffe < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_1) {
    FUN_0043d830(this,param_1);
    return param_1 != 0;
  }
  if ((param_2 != '\0') && (param_1 < 8)) {
    uVar1 = *(uint *)((int)this + 0x10);
    if (param_1 < *(uint *)((int)this + 0x10)) {
      uVar1 = param_1;
    }
    FUN_0043a010(this,'\x01',uVar1);
    return param_1 != 0;
  }
  if (param_1 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (7 < *(uint *)((int)this + 0x14)) {
      this = *(void **)this;
    }
    *(undefined2 *)this = 0;
  }
  return param_1 != 0;
}


