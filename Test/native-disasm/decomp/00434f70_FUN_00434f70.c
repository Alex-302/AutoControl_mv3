// FUN_00434f70 @ 00434f70 size=162 callers=3

ulonglong __thiscall FUN_00434f70(void *this,uint param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  ulonglong uVar5;
  
  uVar2 = *(uint *)((int)this + 0x10);
  if (uVar2 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if (param_2 < uVar2 - param_1) {
    if (param_2 != 0) {
      pvVar3 = this;
      if (7 < *(uint *)((int)this + 0x14)) {
        pvVar3 = *(void **)this;
      }
      iVar4 = uVar2 - param_2;
      puVar1 = (uint *)((int)pvVar3 + param_1 * 2);
      if (iVar4 - param_1 != 0) {
        uVar5 = FUN_0045b0e0(puVar1,(uint *)((int)puVar1 + param_2 * 2),(iVar4 - param_1) * 2);
        param_2 = (uint)(uVar5 >> 0x20);
      }
      *(int *)((int)this + 0x10) = iVar4;
      if (7 < *(uint *)((int)this + 0x14)) {
        *(undefined2 *)(*(int *)this + iVar4 * 2) = 0;
        return CONCAT44(param_2,this);
      }
      *(undefined2 *)((int)this + iVar4 * 2) = 0;
    }
    return CONCAT44(param_2,this);
  }
  *(uint *)((int)this + 0x10) = param_1;
  if (*(uint *)((int)this + 0x14) < 8) {
    *(undefined2 *)((int)this + param_1 * 2) = 0;
    return ZEXT48(this);
  }
  *(undefined2 *)(*(int *)this + param_1 * 2) = 0;
  return ZEXT48(this);
}


