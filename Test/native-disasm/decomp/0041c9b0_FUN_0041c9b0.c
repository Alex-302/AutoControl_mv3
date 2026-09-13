// FUN_0041c9b0 @ 0041c9b0 size=93 callers=1

void __thiscall FUN_0041c9b0(void *this,ushort param_1)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)((int)this + 0x3c);
  if (param_1 != uVar1) {
    *(ushort *)((int)this + 0x3c) = param_1;
    if (param_1 == 0xffff) {
      DAT_004a29c0 = 0;
    }
    else {
      DAT_004a29c0 = *(undefined4 *)(*(int *)((int)this + 0xc) + (uint)param_1 * 0x14);
    }
    FUN_0041c080(this,uVar1);
    FUN_0041c080(this,*(ushort *)((int)this + 0x3c));
    FUN_0041c140((int)this);
  }
  return;
}


