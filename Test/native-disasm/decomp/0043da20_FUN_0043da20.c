// FUN_0043da20 @ 0043da20 size=439 callers=1

undefined8 __thiscall
FUN_0043da20(void *this,void *param_1,undefined4 *param_2,void *param_3,uint param_4)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  void *extraout_EDX;
  void *pvVar4;
  void *pvVar5;
  undefined4 *puVar6;
  ulonglong uVar7;
  
  puVar6 = param_2;
  pvVar1 = param_1;
  pvVar4 = *(void **)((int)this + 0x10);
  if (pvVar4 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if ((void *)param_2[4] < param_3) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  uVar2 = (int)param_2[4] - (int)param_3;
  if (uVar2 < param_4) {
    param_4 = uVar2;
  }
  if (~(uint)pvVar4 <= param_4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar2 = (int)pvVar4 + param_4;
  pvVar4 = param_3;
  if (param_4 != 0) {
    if (0x7ffffffe < uVar2) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar2) {
      FUN_0043d830(this,uVar2);
      pvVar4 = extraout_EDX;
      if (uVar2 == 0) goto LAB_0043dba6;
    }
    else if (uVar2 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (7 < *(uint *)((int)this + 0x14)) {
        **(undefined2 **)this = 0;
        return CONCAT44(param_3,this);
      }
      *(undefined2 *)this = 0;
      return CONCAT44(param_3,this);
    }
    pvVar4 = this;
    param_2 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      param_2 = *(undefined4 **)this;
      pvVar4 = *(void **)this;
    }
    iVar3 = *(int *)((int)this + 0x10) - (int)param_1;
    if (iVar3 != 0) {
      FUN_0045b0e0((uint *)((int)pvVar4 + ((int)param_1 + param_4) * 2),
                   (uint *)((int)param_2 + (int)param_1 * 2),iVar3 * 2);
    }
    if (this == puVar6) {
      pvVar4 = (void *)((int)param_3 + param_4);
      if (param_3 <= param_1) {
        pvVar4 = param_3;
      }
      pvVar5 = this;
      param_1 = this;
      if (7 < *(uint *)((int)this + 0x14)) {
        param_1 = *(void **)this;
        pvVar5 = *(void **)this;
      }
      if (param_4 != 0) {
        uVar7 = FUN_0045b0e0((uint *)((int)pvVar1 * 2 + (int)pvVar5),
                             (uint *)((int)param_1 + (int)pvVar4 * 2),param_4 * 2);
        pvVar4 = (void *)(uVar7 >> 0x20);
      }
    }
    else {
      if (7 < (uint)puVar6[5]) {
        puVar6 = (undefined4 *)*puVar6;
      }
      pvVar4 = this;
      if (7 < *(uint *)((int)this + 0x14)) {
        pvVar4 = *(void **)this;
      }
      if (param_4 != 0) {
        uVar7 = FUN_0045c870((uint *)((int)pvVar4 + (int)param_1 * 2),
                             (uint *)((int)param_3 * 2 + (int)puVar6),param_4 * 2);
        pvVar4 = (void *)(uVar7 >> 0x20);
      }
    }
    *(uint *)((int)this + 0x10) = uVar2;
    if (7 < *(uint *)((int)this + 0x14)) {
      *(undefined2 *)(*(int *)this + uVar2 * 2) = 0;
      return CONCAT44(pvVar4,this);
    }
    *(undefined2 *)((int)this + uVar2 * 2) = 0;
  }
LAB_0043dba6:
  return CONCAT44(pvVar4,this);
}


