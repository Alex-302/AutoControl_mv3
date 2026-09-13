// FUN_0043dd10 @ 0043dd10 size=267 callers=5

undefined8 __thiscall FUN_0043dd10(void *this,undefined4 *param_1,uint param_2,uint param_3)

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
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043d830(this,uVar1);
      if (uVar1 == 0) goto LAB_0043ddf4;
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 8) {
        *(undefined2 *)this = 0;
        return CONCAT44(param_2,this);
      }
      **(undefined2 **)this = 0;
      return CONCAT44(param_2,this);
    }
    if (7 < (uint)param_1[5]) {
      param_1 = (undefined4 *)*param_1;
    }
    pvVar2 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      pvVar2 = *(void **)this;
    }
    if (param_3 != 0) {
      uVar3 = FUN_0045c870((uint *)((int)pvVar2 + *(int *)((int)this + 0x10) * 2),
                           (uint *)((int)param_1 + param_2 * 2),param_3 * 2);
      param_2 = (uint)(uVar3 >> 0x20);
    }
    *(uint *)((int)this + 0x10) = uVar1;
    if (7 < *(uint *)((int)this + 0x14)) {
      *(undefined2 *)(*(int *)this + uVar1 * 2) = 0;
      return CONCAT44(param_2,this);
    }
    *(undefined2 *)((int)this + uVar1 * 2) = 0;
  }
LAB_0043ddf4:
  return CONCAT44(param_2,this);
}


