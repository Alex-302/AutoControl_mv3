// FUN_0043cb70 @ 0043cb70 size=428 callers=2

void __thiscall
FUN_0043cb70(void *this,int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint *local_20;
  uint local_18;
  int local_14;
  int *local_10;
  
  uVar5 = 0;
  puVar1 = *(uint **)this;
  puVar7 = puVar1;
  if (*(int *)((int)this + 0xc) != 0) {
    uVar5 = (param_2 - (int)puVar1 >> 2) * 0x20 + param_3;
    if (((int)uVar5 < 0) && (uVar5 != 0)) {
      iVar3 = (-uVar5 - 1 >> 5) * -4 + -4;
    }
    else {
      iVar3 = (uVar5 >> 5) * 4;
    }
    puVar7 = (uint *)((int)puVar1 + iVar3);
    uVar5 = uVar5 & 0x1f;
  }
  uVar9 = 0;
  local_20 = puVar1;
  if (*(int *)((int)this + 0xc) != 0) {
    uVar9 = (param_4 - (int)puVar1 >> 2) * 0x20 + param_5;
    if (((int)uVar9 < 0) && (uVar9 != 0)) {
      iVar3 = (-uVar9 - 1 >> 5) * -4 + -4;
    }
    else {
      iVar3 = (uVar9 >> 5) * 4;
    }
    local_20 = (uint *)((int)puVar1 + iVar3);
    uVar9 = uVar9 & 0x1f;
  }
  uVar8 = ((int)puVar7 - (int)puVar1 >> 2) * 0x20 + uVar5;
  local_10 = this;
  if ((puVar7 != local_20) || (uVar5 != uVar9)) {
    uVar6 = 0;
    uVar2 = *(uint *)((int)this + 0xc);
    puVar4 = puVar1;
    if (uVar2 != 0) {
      if (((int)uVar2 < 0) && (uVar2 != 0)) {
        iVar3 = (-uVar2 - 1 >> 5) * -4 + -4;
      }
      else {
        iVar3 = (uVar2 >> 5) * 4;
      }
      puVar4 = (uint *)((int)puVar1 + iVar3);
      uVar6 = uVar2 & 0x1f;
    }
    local_18 = (uint)puVar1 & 0xffffff00;
    FUN_004531c0(&local_18,local_18,local_20,uVar9,puVar4,uVar6,puVar7,uVar5);
    FUN_004378c0(local_10,((int)(local_18 - *local_10) >> 2) * 0x20 + local_14);
  }
  iVar3 = *local_10;
  if (((int)uVar8 < 0) && (uVar8 != 0)) {
    *param_1 = iVar3 + (-uVar8 - 1 >> 5) * -4 + -4;
    param_1[1] = uVar8 & 0x1f;
    return;
  }
  param_1[1] = uVar8 & 0x1f;
  *param_1 = iVar3 + (uVar8 >> 5) * 4;
  return;
}


