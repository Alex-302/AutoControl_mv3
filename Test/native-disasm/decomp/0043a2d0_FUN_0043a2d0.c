// FUN_0043a2d0 @ 0043a2d0 size=136 callers=3

int __thiscall FUN_0043a2d0(void *this,ushort *param_1)

{
  ushort uVar1;
  void *pvVar2;
  ushort *puVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  
  if (*(int *)((int)this + 0x10) == 0) {
    return -1;
  }
  pvVar2 = this;
  if (7 < *(uint *)((int)this + 0x14)) {
    pvVar2 = *(void **)this;
  }
  puVar6 = (ushort *)((int)pvVar2 + (*(int *)((int)this + 0x10) + -1) * 2);
  uVar1 = *param_1;
  do {
    if (*puVar6 == uVar1) {
      iVar5 = 1;
      puVar3 = puVar6;
      puVar4 = param_1;
      while (*puVar3 == *puVar4) {
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
        if (iVar5 == 0) goto LAB_0043a319;
      }
      if ((-(uint)(*puVar3 < *puVar4) & 0xfffffffe) == 0xffffffff) {
LAB_0043a319:
        if (7 < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)puVar6 - (int)this >> 1;
      }
    }
    puVar3 = (ushort *)FUN_0043a000(this);
    if (puVar6 == puVar3) {
      return -1;
    }
    puVar6 = puVar6 + -1;
  } while( true );
}


