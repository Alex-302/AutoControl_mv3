// FUN_0043a360 @ 0043a360 size=185 callers=1

int __thiscall FUN_0043a360(void *this,ushort *param_1)

{
  ushort *puVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  ushort *puVar5;
  ushort *local_8;
  
  iVar4 = *(int *)((int)this + 0x10);
  if ((iVar4 == 0) || (iVar4 == 0)) {
    return -1;
  }
  local_8 = this;
  if (7 < *(uint *)((int)this + 0x14)) {
    local_8 = *(ushort **)this;
  }
  do {
    if (iVar4 != 0) {
      puVar1 = local_8;
      iVar2 = iVar4;
      do {
        if (*puVar1 == *param_1) goto LAB_0043a3af;
        puVar1 = puVar1 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    puVar1 = (ushort *)0x0;
LAB_0043a3af:
    if (puVar1 == (ushort *)0x0) {
      return -1;
    }
    iVar2 = 1;
    puVar3 = param_1;
    puVar5 = puVar1;
    while (*puVar5 == *puVar3) {
      puVar5 = puVar5 + 1;
      puVar3 = puVar3 + 1;
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) goto LAB_0043a3d3;
    }
    if ((-(uint)(*puVar5 < *puVar3) & 0xfffffffe) == 0xffffffff) {
LAB_0043a3d3:
      if (7 < *(uint *)((int)this + 0x14)) {
        this = *(void **)this;
      }
      return (int)puVar1 - (int)this >> 1;
    }
    iVar4 = iVar4 + (-1 - ((int)puVar1 - (int)local_8 >> 1));
    local_8 = puVar1 + 1;
  } while( true );
}


