// FUN_0043a650 @ 0043a650 size=243 callers=9

void * __thiscall FUN_0043a650(void *this,uint *param_1,uint param_2)

{
  uint uVar1;
  uint *puVar2;
  void *pvVar3;
  
  if (param_1 != (uint *)0x0) {
    uVar1 = *(uint *)((int)this + 0x14);
    puVar2 = this;
    if (7 < uVar1) {
      puVar2 = *(uint **)this;
    }
    if (puVar2 <= param_1) {
      pvVar3 = this;
      if (7 < uVar1) {
        pvVar3 = *(void **)this;
      }
      if (param_1 < (uint *)((int)pvVar3 + *(int *)((int)this + 0x10) * 2)) {
        pvVar3 = this;
        if (7 < uVar1) {
          pvVar3 = *(void **)this;
        }
        pvVar3 = FUN_0043a750(this,this,(int)param_1 - (int)pvVar3 >> 1,param_2);
        return pvVar3;
      }
    }
  }
  if (0x7ffffffe < param_2) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_2) {
    FUN_0043d830(this,param_2);
    if (param_2 == 0) {
      return this;
    }
  }
  else if (param_2 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (7 < *(uint *)((int)this + 0x14)) {
      **(undefined2 **)this = 0;
      return this;
    }
    *(undefined2 *)this = 0;
    return this;
  }
  puVar2 = this;
  if (7 < *(uint *)((int)this + 0x14)) {
    puVar2 = *(uint **)this;
  }
  if (param_2 != 0) {
    FUN_0045c870(puVar2,param_1,param_2 * 2);
  }
  *(uint *)((int)this + 0x10) = param_2;
  if (*(uint *)((int)this + 0x14) < 8) {
    *(undefined2 *)((int)this + param_2 * 2) = 0;
    return this;
  }
  *(undefined2 *)(*(int *)this + param_2 * 2) = 0;
  return this;
}


