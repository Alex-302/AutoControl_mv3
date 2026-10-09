// FUN_00455b80 @ 00455b80 size=119 callers=2

undefined4 __thiscall FUN_00455b80(void *this,char param_1)

{
  ushort uVar1;
  undefined2 extraout_var;
  undefined4 uVar3;
  uint uVar2;
  
  uVar2 = *(uint *)this;
  if (uVar2 != *(uint *)((int)this + 8)) {
    uVar1 = FUN_00456900(*(void **)((int)this + 0x3c),*(byte **)this,(byte *)(uVar2 + 1),
                         (byte)((uint)*(undefined4 *)((int)this + 0x40) >> 8) & 1);
    uVar2 = CONCAT22(extraout_var,uVar1);
    if (uVar1 != 0) {
      if (param_1 != '\0') {
        FUN_00453e50((int)this + 0x24);
      }
      FUN_00456550((void *)((int)this + 0x24),*(int *)((int)this + 0x28),uVar1,
                   *(byte *)(*(int *)(*(int *)(*(int *)((int)this + 0x3c) + 4) + 0xc) +
                            (uint)*(byte *)((int)this + 0x48) * 2) & 1);
      uVar3 = FUN_0044dfd0(this);
      return CONCAT31((int3)((uint)uVar3 >> 8),1);
    }
  }
  return uVar2 & 0xffffff00;
}


