// FUN_004322c0 @ 004322c0 size=179 callers=1

void __thiscall FUN_004322c0(void *this,uint *param_1)

{
  uint *puVar1;
  uint *puVar2;
  undefined1 *puVar3;
  int iVar4;
  
  puVar1 = *(uint **)((int)this + 4);
  if ((param_1 < puVar1) && (puVar2 = *(uint **)this, puVar2 <= param_1)) {
    if (puVar1 == *(uint **)((int)this + 8)) {
      FUN_00435d00(this);
    }
    puVar3 = *(undefined1 **)((int)this + 4);
    if (puVar3 != (undefined1 *)0x0) {
      iVar4 = *(int *)this;
      *(undefined4 *)(puVar3 + 0x14) = 0xf;
      *(undefined4 *)(puVar3 + 0x10) = 0;
      *puVar3 = 0;
      puVar1 = (uint *)(iVar4 + (((int)param_1 - (int)puVar2) / 0x1c) * 0x1c);
      FUN_0043b1c0(puVar3,puVar1);
      *(uint *)(puVar3 + 0x18) = puVar1[6];
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x1c;
      return;
    }
  }
  else {
    if (puVar1 == *(uint **)((int)this + 8)) {
      FUN_00435d00(this);
    }
    puVar3 = *(undefined1 **)((int)this + 4);
    if (puVar3 != (undefined1 *)0x0) {
      *(undefined4 *)(puVar3 + 0x14) = 0xf;
      *(undefined4 *)(puVar3 + 0x10) = 0;
      *puVar3 = 0;
      FUN_0043b1c0(puVar3,param_1);
      *(uint *)(puVar3 + 0x18) = param_1[6];
    }
  }
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x1c;
  return;
}


