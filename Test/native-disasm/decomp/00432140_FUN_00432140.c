// FUN_00432140 @ 00432140 size=129 callers=1

void __thiscall FUN_00432140(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  puVar2 = *(undefined4 **)((int)this + 4);
  if ((param_1 < puVar2) && (*(undefined4 **)this <= param_1)) {
    iVar4 = ((int)param_1 - (int)*(undefined4 **)this) / 0x14;
    if (puVar2 == *(undefined4 **)((int)this + 8)) {
      FUN_00435b00(this);
    }
    puVar2 = *(undefined4 **)((int)this + 4);
    if (puVar2 != (undefined4 *)0x0) {
      iVar3 = *(int *)this;
      puVar1 = (undefined4 *)(iVar3 + iVar4 * 0x14);
      uVar5 = puVar1[1];
      uVar6 = puVar1[2];
      uVar7 = puVar1[3];
      *puVar2 = *puVar1;
      puVar2[1] = uVar5;
      puVar2[2] = uVar6;
      puVar2[3] = uVar7;
      puVar2[4] = *(undefined4 *)(iVar3 + 0x10 + iVar4 * 0x14);
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x14;
      return;
    }
  }
  else {
    if (puVar2 == *(undefined4 **)((int)this + 8)) {
      FUN_00435b00(this);
    }
    puVar2 = *(undefined4 **)((int)this + 4);
    if (puVar2 != (undefined4 *)0x0) {
      uVar5 = param_1[1];
      uVar6 = param_1[2];
      uVar7 = param_1[3];
      *puVar2 = *param_1;
      puVar2[1] = uVar5;
      puVar2[2] = uVar6;
      puVar2[3] = uVar7;
      puVar2[4] = param_1[4];
    }
  }
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + 0x14;
  return;
}


