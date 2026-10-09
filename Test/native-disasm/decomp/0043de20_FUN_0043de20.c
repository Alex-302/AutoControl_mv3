// FUN_0043de20 @ 0043de20 size=107 callers=3

bool __thiscall FUN_0043de20(void *this,uint param_1,char param_2)

{
  uint uVar1;
  
  if (param_1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_1) {
    FUN_0043f5f0(this,param_1);
    return param_1 != 0;
  }
  if ((param_2 != '\0') && (param_1 < 0x10)) {
    uVar1 = *(uint *)((int)this + 0x10);
    if (param_1 < *(uint *)((int)this + 0x10)) {
      uVar1 = param_1;
    }
    FUN_0043a990(this,'\x01',uVar1);
    return param_1 != 0;
  }
  if (param_1 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (0xf < *(uint *)((int)this + 0x14)) {
      this = *(void **)this;
    }
    *(undefined1 *)this = 0;
  }
  return param_1 != 0;
}


