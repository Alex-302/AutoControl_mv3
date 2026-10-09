// FUN_00413270 @ 00413270 size=224 callers=2

void * __thiscall FUN_00413270(void *this,ushort param_1)

{
  undefined1 uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uVar4 = param_1 & 0xfc00;
  uVar3 = param_1 & 0x3ff;
  *(undefined1 *)((int)this + 2) = 0;
  *(ushort *)this = uVar3;
  if (uVar4 < 0x801) {
    if (uVar4 == 0x800) {
      *(undefined1 *)((int)this + 3) = 0xb;
      return this;
    }
    if (((param_1 & 0xfc00) != 0) && (uVar4 != 0x400)) {
LAB_0041332f:
      *(undefined1 *)((int)this + 3) = 99;
      return this;
    }
    uVar1 = 0x44;
    if (uVar4 == 0x400) {
      uVar1 = 0x55;
    }
    *(undefined1 *)((int)this + 2) = uVar1;
    if (((5 < (ushort)(uVar3 - 1)) || (uVar3 == 3)) && ((uVar3 < 0x200 || (0x203 < uVar3)))) {
      if (0x21f < uVar3) {
        uVar2 = FUN_00408230(param_1);
        *(char *)((int)this + 3) = (char)uVar2 + '\x02';
        return this;
      }
      *(undefined1 *)((int)this + 3) = 0;
      return this;
    }
  }
  else if (uVar4 != 0x1000) {
    if (uVar4 == 0x1400) {
      *(undefined1 *)((int)this + 3) = 10;
      return this;
    }
    goto LAB_0041332f;
  }
  *(undefined1 *)((int)this + 3) = 1;
  return this;
}


