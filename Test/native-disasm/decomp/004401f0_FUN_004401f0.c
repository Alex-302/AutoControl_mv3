// FUN_004401f0 @ 004401f0 size=967 callers=2

undefined8 __thiscall
FUN_004401f0(void *this,void *param_1,void *param_2,undefined4 *param_3,uint param_4,void *param_5)

{
  uint uVar1;
  undefined1 *puVar2;
  uint *puVar3;
  uint *puVar4;
  void *pvVar5;
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  void *pvVar9;
  ulonglong uVar10;
  
  pvVar6 = param_1;
  pvVar8 = *(void **)((int)this + 0x10);
  if (pvVar8 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if ((uint)param_3[4] < param_4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  pvVar7 = (void *)((int)pvVar8 - (int)param_1);
  pvVar5 = param_2;
  if (pvVar7 < param_2) {
    pvVar5 = pvVar7;
  }
  pvVar9 = (void *)(param_3[4] - param_4);
  if (pvVar9 < param_5) {
    param_5 = pvVar9;
  }
  if (~(uint)param_5 <= (uint)((int)pvVar8 - (int)pvVar5)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  pvVar7 = (void *)((int)pvVar7 - (int)pvVar5);
  uVar1 = ((int)pvVar8 - (int)pvVar5) + (int)param_5;
  if (*(uint *)((int)this + 0x10) < uVar1) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043f5f0(this,uVar1);
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      puVar2 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        puVar2 = *(undefined1 **)this;
      }
      *puVar2 = 0;
    }
  }
  pvVar8 = pvVar7;
  if (param_5 == pvVar5) {
    if (0xf < (uint)param_3[5]) {
      param_3 = (undefined4 *)*param_3;
    }
    pvVar6 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar6 = *(void **)this;
    }
    if (param_5 == (void *)0x0) goto LAB_00440564;
    puVar3 = (uint *)(param_4 + (int)param_3);
    puVar4 = (uint *)((int)pvVar6 + (int)param_1);
    pvVar7 = param_5;
  }
  else {
    param_2 = this;
    if (this != param_3) {
      param_1 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        param_2 = *(void **)this;
        param_1 = *(void **)this;
      }
      if (pvVar7 != (void *)0x0) {
        uVar10 = FUN_0045b0e0((uint *)((int)param_1 + (int)pvVar6 + (int)param_5),
                              (uint *)((int)param_2 + (int)pvVar6 + (int)pvVar5),(uint)pvVar7);
        pvVar8 = (void *)(uVar10 >> 0x20);
      }
      if (0xf < (uint)param_3[5]) {
        param_3 = (undefined4 *)*param_3;
      }
      pvVar5 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar5 = *(void **)this;
      }
      if (param_5 != (void *)0x0) {
        uVar10 = FUN_0045c870((uint *)((int)pvVar5 + (int)pvVar6),(uint *)(param_4 + (int)param_3),
                              (uint)param_5);
        pvVar8 = (void *)(uVar10 >> 0x20);
      }
      goto LAB_00440564;
    }
    pvVar8 = this;
    if (param_5 < pvVar5) {
      pvVar9 = this;
      pvVar6 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar9 = *(void **)this;
        pvVar6 = *(void **)this;
      }
      if (param_5 != (void *)0x0) {
        FUN_0045b0e0((uint *)((int)pvVar9 + (int)param_1),(uint *)(param_4 + (int)pvVar6),
                     (uint)param_5);
      }
      pvVar6 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar8 = *(void **)this;
        pvVar6 = *(void **)this;
      }
      if (pvVar7 == (void *)0x0) goto LAB_00440564;
      puVar3 = (uint *)((int)param_1 + (int)pvVar6 + (int)pvVar5);
      puVar4 = (uint *)((int)pvVar8 + (int)param_1 + (int)param_5);
    }
    else if (param_1 < param_4) {
      if (param_4 < (uint)((int)param_1 + (int)pvVar5)) {
        pvVar9 = this;
        pvVar6 = this;
        if (0xf < *(uint *)((int)this + 0x14)) {
          pvVar9 = *(void **)this;
          pvVar6 = *(void **)this;
        }
        if (pvVar5 != (void *)0x0) {
          FUN_0045b0e0((uint *)((int)pvVar9 + (int)param_1),(uint *)(param_4 + (int)pvVar6),
                       (uint)pvVar5);
        }
        pvVar9 = this;
        pvVar6 = this;
        if (0xf < *(uint *)((int)this + 0x14)) {
          pvVar9 = *(void **)this;
          pvVar6 = *(void **)this;
        }
        if (pvVar7 != (void *)0x0) {
          FUN_0045b0e0((uint *)((int)pvVar9 + (int)param_1 + (int)param_5),
                       (uint *)((int)param_1 + (int)pvVar6 + (int)pvVar5),(uint)pvVar7);
        }
        pvVar6 = this;
        if (0xf < *(uint *)((int)this + 0x14)) {
          pvVar8 = *(void **)this;
          pvVar6 = *(void **)this;
        }
        pvVar7 = (void *)((int)param_5 - (int)pvVar5);
        if (pvVar7 == (void *)0x0) goto LAB_00440564;
        puVar3 = (uint *)(param_4 + (int)pvVar6 + (int)param_5);
        puVar4 = (uint *)((int)pvVar8 + (int)param_1 + (int)pvVar5);
      }
      else {
        pvVar9 = this;
        param_1 = this;
        if (0xf < *(uint *)((int)this + 0x14)) {
          param_1 = *(void **)this;
          pvVar9 = *(void **)this;
        }
        if (pvVar7 != (void *)0x0) {
          FUN_0045b0e0((uint *)((int)pvVar6 + (int)pvVar9 + (int)param_5),
                       (uint *)((int)param_1 + (int)pvVar6 + (int)pvVar5),(uint)pvVar7);
        }
        pvVar7 = this;
        if (0xf < *(uint *)((int)this + 0x14)) {
          pvVar8 = *(void **)this;
          pvVar7 = *(void **)this;
        }
        if (param_5 == (void *)0x0) goto LAB_00440564;
        puVar3 = (uint *)((int)pvVar7 + (param_4 - (int)pvVar5) + (int)param_5);
        puVar4 = (uint *)((int)pvVar8 + (int)pvVar6);
        pvVar7 = param_5;
      }
    }
    else {
      pvVar6 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        param_2 = *(void **)this;
        pvVar6 = *(void **)this;
      }
      if (pvVar7 != (void *)0x0) {
        FUN_0045b0e0((uint *)((int)param_1 + (int)pvVar6 + (int)param_5),
                     (uint *)((int)param_2 + (int)param_1 + (int)pvVar5),(uint)pvVar7);
      }
      pvVar6 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar6 = *(void **)this;
        pvVar8 = *(void **)this;
      }
      if (param_5 == (void *)0x0) goto LAB_00440564;
      puVar3 = (uint *)(param_4 + (int)pvVar8);
      puVar4 = (uint *)((int)pvVar6 + (int)param_1);
      pvVar7 = param_5;
    }
  }
  uVar10 = FUN_0045b0e0(puVar4,puVar3,(uint)pvVar7);
  pvVar8 = (void *)(uVar10 >> 0x20);
LAB_00440564:
  *(uint *)((int)this + 0x10) = uVar1;
  if (0xf < *(uint *)((int)this + 0x14)) {
    *(undefined1 *)(*(int *)this + uVar1) = 0;
    return CONCAT44(pvVar8,this);
  }
  *(undefined1 *)((int)this + uVar1) = 0;
  return CONCAT44(pvVar8,this);
}


