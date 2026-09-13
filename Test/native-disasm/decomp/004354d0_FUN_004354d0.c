// FUN_004354d0 @ 004354d0 size=148 callers=5

undefined8 __thiscall FUN_004354d0(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  ulonglong uVar4;
  
  uVar1 = *(uint *)((int)this + 0x10);
  if (uVar1 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if (param_2 < uVar1 - param_1) {
    if (param_2 != 0) {
      pvVar2 = this;
      if (0xf < *(uint *)((int)this + 0x14)) {
        pvVar2 = *(void **)this;
      }
      iVar3 = uVar1 - param_2;
      if (iVar3 - param_1 != 0) {
        uVar4 = FUN_0045b0e0((uint *)((int)pvVar2 + param_1),
                             (uint *)((int)((int)pvVar2 + param_1) + param_2),iVar3 - param_1);
        param_2 = (uint)(uVar4 >> 0x20);
      }
      *(int *)((int)this + 0x10) = iVar3;
      if (0xf < *(uint *)((int)this + 0x14)) {
        *(undefined1 *)(*(int *)this + iVar3) = 0;
        return CONCAT44(param_2,this);
      }
      *(undefined1 *)((int)this + iVar3) = 0;
    }
    return CONCAT44(param_2,this);
  }
  *(uint *)((int)this + 0x10) = param_1;
  if (*(uint *)((int)this + 0x14) < 0x10) {
    *(undefined1 *)((int)this + param_1) = 0;
    return CONCAT44(param_2,this);
  }
  *(undefined1 *)(*(int *)this + param_1) = 0;
  return CONCAT44(param_2,this);
}


