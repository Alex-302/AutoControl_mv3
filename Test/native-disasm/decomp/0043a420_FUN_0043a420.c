// FUN_0043a420 @ 0043a420 size=391 callers=1

undefined8 __thiscall FUN_0043a420(void *this,void *param_1,uint *param_2,void *param_3)

{
  uint uVar1;
  uint *puVar2;
  void *pvVar3;
  int iVar4;
  void *pvVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  
  pvVar3 = param_3;
  if (param_2 != (uint *)0x0) {
    uVar1 = *(uint *)((int)this + 0x14);
    puVar2 = this;
    if (7 < uVar1) {
      puVar2 = *(uint **)this;
    }
    if (puVar2 <= param_2) {
      pvVar5 = this;
      if (7 < uVar1) {
        pvVar5 = *(void **)this;
      }
      if (param_2 < (uint *)((int)pvVar5 + *(int *)((int)this + 0x10) * 2)) {
        pvVar3 = this;
        if (7 < uVar1) {
          pvVar3 = *(void **)this;
        }
        uVar6 = FUN_0043da20(this,param_1,this,(void *)((int)param_2 - (int)pvVar3 >> 1),
                             (uint)param_3);
        return uVar6;
      }
    }
  }
  pvVar5 = *(void **)((int)this + 0x10);
  if (pvVar5 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if ((void *)~(uint)pvVar5 <= param_3) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = (int)pvVar5 + (int)param_3;
  if (param_3 != (void *)0x0) {
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043d830(this,uVar1);
      if (uVar1 == 0) goto LAB_0043a580;
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (7 < *(uint *)((int)this + 0x14)) {
        **(undefined2 **)this = 0;
        return CONCAT44(param_1,this);
      }
      *(undefined2 *)this = 0;
      return CONCAT44(param_1,this);
    }
    pvVar5 = this;
    param_3 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      param_3 = *(void **)this;
      pvVar5 = *(void **)this;
    }
    iVar4 = *(int *)((int)this + 0x10) - (int)param_1;
    if (iVar4 != 0) {
      FUN_0045b0e0((uint *)((int)pvVar5 + ((int)param_1 + (int)pvVar3) * 2),
                   (uint *)((int)param_3 + (int)param_1 * 2),iVar4 * 2);
    }
    pvVar5 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      pvVar5 = *(void **)this;
    }
    if (pvVar3 != (void *)0x0) {
      uVar7 = FUN_0045c870((uint *)((int)pvVar5 + (int)param_1 * 2),param_2,(int)pvVar3 * 2);
      param_1 = (void *)(uVar7 >> 0x20);
    }
    *(uint *)((int)this + 0x10) = uVar1;
    if (7 < *(uint *)((int)this + 0x14)) {
      *(undefined2 *)(*(int *)this + uVar1 * 2) = 0;
      return CONCAT44(param_1,this);
    }
    *(undefined2 *)((int)this + uVar1 * 2) = 0;
  }
LAB_0043a580:
  return CONCAT44(param_1,this);
}


