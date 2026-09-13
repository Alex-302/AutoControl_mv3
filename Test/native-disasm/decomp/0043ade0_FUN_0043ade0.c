// FUN_0043ade0 @ 0043ade0 size=259 callers=47

void * __thiscall FUN_0043ade0(void *this,undefined4 *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  void *pvVar2;
  uint *puVar3;
  
  if ((uint)param_1[4] < param_2) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  uVar1 = param_1[4] - param_2;
  if (uVar1 < param_3) {
    param_3 = uVar1;
  }
  if (this == param_1) {
    uVar1 = param_3 + param_2;
    if (uVar1 <= *(uint *)((int)this + 0x10)) {
      *(uint *)((int)this + 0x10) = uVar1;
      pvVar2 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar2 = *(void **)this;
      }
      *(undefined1 *)((int)pvVar2 + uVar1) = 0;
      FUN_004354d0(this,0,param_2);
      return this;
    }
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if (param_3 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_3) {
    FUN_0043f5f0(this,param_3);
    if (param_3 == 0) {
      return this;
    }
  }
  else if (param_3 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (0xf < *(uint *)((int)this + 0x14)) {
      **(undefined1 **)this = 0;
      return this;
    }
    *(undefined1 *)this = 0;
    return this;
  }
  if (0xf < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  puVar3 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar3 = *(uint **)this;
  }
  if (param_3 != 0) {
    FUN_0045c870(puVar3,(uint *)((int)param_1 + param_2),param_3);
  }
  *(uint *)((int)this + 0x10) = param_3;
  if (*(uint *)((int)this + 0x14) < 0x10) {
    *(undefined1 *)((int)this + param_3) = 0;
    return this;
  }
  *(undefined1 *)(*(int *)this + param_3) = 0;
  return this;
}


