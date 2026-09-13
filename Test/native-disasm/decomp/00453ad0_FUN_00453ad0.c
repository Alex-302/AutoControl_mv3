// FUN_00453ad0 @ 00453ad0 size=119 callers=2

undefined4 __thiscall FUN_00453ad0(void *this,char param_1)

{
  byte *pbVar1;
  ushort uVar2;
  uint in_EAX;
  undefined2 extraout_var;
  undefined4 uVar3;
  
  pbVar1 = *(byte **)this;
  if (pbVar1 != *(byte **)((int)this + 8)) {
    uVar2 = FUN_00455ee0(*(void **)((int)this + 0x3c),pbVar1,pbVar1 + 1,
                         (byte)((uint)*(undefined4 *)((int)this + 0x40) >> 8) & 1);
    in_EAX = CONCAT22(extraout_var,uVar2);
    if (uVar2 != 0) {
      if (param_1 != '\0') {
        FUN_00453e50((int)this + 0x24);
      }
      FUN_00456550((void *)((int)this + 0x24),*(int *)((int)this + 0x28),uVar2,
                   *(byte *)(*(int *)(*(int *)(*(int *)((int)this + 0x3c) + 4) + 0xc) +
                            (uint)*(byte *)((int)this + 0x48) * 2) & 1);
      uVar3 = FUN_0044dfd0(this);
      return CONCAT31((int3)((uint)uVar3 >> 8),1);
    }
  }
  return in_EAX & 0xffffff00;
}


