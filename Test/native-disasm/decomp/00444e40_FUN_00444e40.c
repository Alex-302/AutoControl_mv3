// FUN_00444e40 @ 00444e40 size=508 callers=1

undefined8 __thiscall
FUN_00444e40(void *this,void *param_1,void *param_2,uint *param_3,void *param_4)

{
  uint *puVar1;
  uint *puVar2;
  void *pvVar3;
  void *pvVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  
  puVar1 = param_3;
  if (param_3 != (uint *)0x0) {
    uVar6 = *(uint *)((int)this + 0x14);
    puVar2 = this;
    if (0xf < uVar6) {
      puVar2 = *(uint **)this;
    }
    if (puVar2 <= param_3) {
      pvVar3 = this;
      if (0xf < uVar6) {
        pvVar3 = *(void **)this;
      }
      if (param_3 < (uint *)(*(int *)((int)this + 0x10) + (int)pvVar3)) {
        pvVar3 = this;
        if (0xf < uVar6) {
          pvVar3 = *(void **)this;
        }
        uVar8 = FUN_004401f0(this,param_1,param_2,this,(int)param_3 - (int)pvVar3,param_4);
        return uVar8;
      }
    }
  }
  pvVar3 = *(void **)((int)this + 0x10);
  if (pvVar3 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  pvVar5 = (void *)((int)pvVar3 - (int)param_1);
  pvVar4 = param_2;
  if (pvVar5 < param_2) {
    pvVar4 = pvVar5;
  }
  if (~(uint)param_4 <= (uint)((int)pvVar3 - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar6 = (int)pvVar5 - (int)pvVar4;
  if (param_4 < pvVar4) {
    param_2 = this;
    param_3 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      param_2 = *(void **)this;
      param_3 = *(uint **)this;
    }
    if (uVar6 != 0) {
      FUN_0045b0e0((uint *)((int)param_3 + (int)param_1 + (int)param_4),
                   (uint *)((int)param_2 + (int)param_1 + (int)pvVar4),uVar6);
    }
  }
  uVar7 = (*(int *)((int)this + 0x10) - (int)pvVar4) + (int)param_4;
  if ((param_4 != (void *)0x0) || (pvVar4 != (void *)0x0)) {
    if (uVar7 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar7) {
      FUN_0043f5f0(this,uVar7);
      if (uVar7 == 0) goto LAB_00445014;
    }
    else if (uVar7 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (0xf < *(uint *)((int)this + 0x14)) {
        **(undefined1 **)this = 0;
        return CONCAT44(param_4,this);
      }
      *(undefined1 *)this = 0;
      return CONCAT44(param_4,this);
    }
    if (pvVar4 < param_4) {
      param_2 = this;
      param_3 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        param_2 = *(void **)this;
        param_3 = *(uint **)this;
      }
      if (uVar6 != 0) {
        FUN_0045b0e0((uint *)((int)param_3 + (int)param_1 + (int)param_4),
                     (uint *)((int)param_2 + (int)param_1 + (int)pvVar4),uVar6);
      }
    }
    pvVar3 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar3 = *(void **)this;
    }
    if (param_4 != (void *)0x0) {
      uVar9 = FUN_0045c870((uint *)((int)pvVar3 + (int)param_1),puVar1,(uint)param_4);
      param_4 = (void *)(uVar9 >> 0x20);
    }
    *(uint *)((int)this + 0x10) = uVar7;
    if (0xf < *(uint *)((int)this + 0x14)) {
      *(undefined1 *)(*(int *)this + uVar7) = 0;
      return CONCAT44(param_4,this);
    }
    *(undefined1 *)((int)this + uVar7) = 0;
  }
LAB_00445014:
  return CONCAT44(param_4,this);
}


