// FUN_0043b0c0 @ 0043b0c0 size=244 callers=12

undefined8 __thiscall FUN_0043b0c0(void *this,undefined4 *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  void *pvVar2;
  ulonglong uVar3;
  
  if ((uint)param_1[4] < param_2) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  uVar1 = param_1[4] - param_2;
  if (uVar1 < param_3) {
    param_3 = uVar1;
  }
  if (~*(uint *)((int)this + 0x10) <= param_3) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = *(uint *)((int)this + 0x10) + param_3;
  if (param_3 != 0) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043f5f0(this,uVar1);
      if (uVar1 == 0) goto LAB_0043b18d;
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 0x10) {
        *(undefined1 *)this = 0;
        return CONCAT44(param_2,this);
      }
      **(undefined1 **)this = 0;
      return CONCAT44(param_2,this);
    }
    if (0xf < (uint)param_1[5]) {
      param_1 = (undefined4 *)*param_1;
    }
    pvVar2 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar2 = *(void **)this;
    }
    if (param_3 != 0) {
      uVar3 = FUN_0045c870((uint *)(*(int *)((int)this + 0x10) + (int)pvVar2),
                           (uint *)((int)param_1 + param_2),param_3);
      param_2 = (uint)(uVar3 >> 0x20);
    }
    *(uint *)((int)this + 0x10) = uVar1;
    if (0xf < *(uint *)((int)this + 0x14)) {
      *(undefined1 *)(*(int *)this + uVar1) = 0;
      return CONCAT44(param_2,this);
    }
    *(undefined1 *)((int)this + uVar1) = 0;
  }
LAB_0043b18d:
  return CONCAT44(param_2,this);
}


