// FUN_00435020 @ 00435020 size=265 callers=1

void * __thiscall FUN_00435020(void *this,uint param_1,uint param_2,undefined2 param_3)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  void *pvVar4;
  
  uVar1 = *(uint *)((int)this + 0x10);
  if (uVar1 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if (~uVar1 <= param_2) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = uVar1 + param_2;
  if (param_2 != 0) {
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (*(uint *)((int)this + 0x14) < uVar1) {
      FUN_0043d830(this,uVar1);
      if (uVar1 == 0) {
        return this;
      }
    }
    else if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 8) {
        *(undefined2 *)this = 0;
        return this;
      }
      **(undefined2 **)this = 0;
      return this;
    }
    pvVar4 = this;
    pvVar2 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      pvVar4 = *(void **)this;
      pvVar2 = *(void **)this;
    }
    iVar3 = *(int *)((int)this + 0x10) - param_1;
    if (iVar3 != 0) {
      FUN_0045b0e0((uint *)((int)pvVar4 + (param_2 + param_1) * 2),
                   (uint *)((int)pvVar2 + param_1 * 2),iVar3 * 2);
    }
    FUN_0043a100(this,param_1,param_2,param_3);
    *(uint *)((int)this + 0x10) = uVar1;
    if (7 < *(uint *)((int)this + 0x14)) {
      *(undefined2 *)(*(int *)this + uVar1 * 2) = 0;
      return this;
    }
    *(undefined2 *)((int)this + uVar1 * 2) = 0;
  }
  return this;
}


