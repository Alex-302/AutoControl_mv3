// FUN_0043ace0 @ 0043ace0 size=240 callers=163

void * __thiscall FUN_0043ace0(void *this,uint *param_1,uint param_2)

{
  uint uVar1;
  void *pvVar2;
  uint *puVar3;
  
  if (param_1 != (uint *)0x0) {
    uVar1 = *(uint *)((int)this + 0x14);
    puVar3 = this;
    if (0xf < uVar1) {
      puVar3 = *(uint **)this;
    }
    if (puVar3 <= param_1) {
      pvVar2 = this;
      if (0xf < uVar1) {
        pvVar2 = *(void **)this;
      }
      if (param_1 < (uint *)(*(int *)((int)this + 0x10) + (int)pvVar2)) {
        if (0xf < uVar1) {
          pvVar2 = FUN_0043ade0(this,this,(int)param_1 - *(int *)this,param_2);
          return pvVar2;
        }
        pvVar2 = FUN_0043ade0(this,this,(int)param_1 - (int)this,param_2);
        return pvVar2;
      }
    }
  }
  if (param_2 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_2) {
    FUN_0043f5f0(this,param_2);
    if (param_2 == 0) {
      return this;
    }
  }
  else if (param_2 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (0xf < *(uint *)((int)this + 0x14)) {
      **(undefined1 **)this = 0;
      return this;
    }
    *(undefined1 *)this = 0;
    return this;
  }
  puVar3 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    puVar3 = *(uint **)this;
  }
  if (param_2 != 0) {
    FUN_0045c870(puVar3,param_1,param_2);
  }
  *(uint *)((int)this + 0x10) = param_2;
  if (*(uint *)((int)this + 0x14) < 0x10) {
    *(undefined1 *)((int)this + param_2) = 0;
    return this;
  }
  *(undefined1 *)(*(int *)this + param_2) = 0;
  return this;
}


