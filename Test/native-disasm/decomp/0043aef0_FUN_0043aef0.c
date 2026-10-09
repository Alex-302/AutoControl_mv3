// FUN_0043aef0 @ 0043aef0 size=159 callers=25

void * __thiscall FUN_0043aef0(void *this,uint param_1,char param_2)

{
  uint uVar1;
  
  if (~*(uint *)((int)this + 0x10) <= param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = *(uint *)((int)this + 0x10) + param_1;
  if (param_1 != 0) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043f5f0(this,uVar1);
      if (uVar1 == 0) {
        return this;
      }
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 0x10) {
        *(undefined1 *)this = 0;
        return this;
      }
      **(undefined1 **)this = 0;
      return this;
    }
    FUN_0043de90(this,*(int *)((int)this + 0x10),param_1,param_2);
    *(uint *)((int)this + 0x10) = uVar1;
    if (0xf < *(uint *)((int)this + 0x14)) {
      *(undefined1 *)(*(int *)this + uVar1) = 0;
      return this;
    }
    *(undefined1 *)((int)this + uVar1) = 0;
  }
  return this;
}


