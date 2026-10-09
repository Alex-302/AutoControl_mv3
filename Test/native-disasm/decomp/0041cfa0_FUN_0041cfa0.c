// FUN_0041cfa0 @ 0041cfa0 size=135 callers=1

void __thiscall FUN_0041cfa0(void *this,int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;
  
  if (*(char *)((int)this + 0x40) != '\0') {
    iVar3 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
    uVar4 = 0;
    iVar2 = iVar3 >> 0x1f;
    if (iVar3 / 0x14 + iVar2 != iVar2) {
      uVar5 = 0;
      do {
        puVar1 = FUN_00419890(*(uint *)(*(int *)((int)this + 0xc) + uVar5 * 0x14));
        if (puVar1[0x24] == '3') {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(puVar1 + 0x20);
        }
        if (param_1 == iVar2) {
          FUN_0041c080(this,uVar4);
          FUN_0041c140((int)this);
        }
        uVar4 = uVar4 + 1;
        uVar5 = (uint)uVar4;
      } while (uVar5 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14));
    }
  }
  return;
}


