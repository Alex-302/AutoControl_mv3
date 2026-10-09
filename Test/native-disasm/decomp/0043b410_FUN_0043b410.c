// FUN_0043b410 @ 0043b410 size=299 callers=1

void __thiscall
FUN_0043b410(void *this,uint *param_1,uint param_2,int param_3,uint param_4,int param_5,
            undefined4 param_6,undefined4 param_7,uint param_8)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar7 = param_4 + param_2;
  uVar5 = param_5 + param_3 + (uint)CARRY4(param_4,param_2);
  uVar6 = **(uint **)((int)this + 0x20);
  if ((uVar6 != 0) && (*(uint *)((int)this + 0x38) < uVar6)) {
    *(uint *)((int)this + 0x38) = uVar6;
  }
  if ((uVar7 != DAT_00480cc0) || (uVar6 = uVar5, uVar8 = uVar7, uVar5 != DAT_00480cc4)) {
    uVar6 = DAT_00480cc4;
    uVar8 = DAT_00480cc0;
    if (((param_8 & 1) == 0) || (**(int **)((int)this + 0x1c) == 0)) {
      if ((((param_8 & 2) != 0) && (**(uint **)((int)this + 0x20) != 0)) && (-1 < (int)uVar5)) {
        uVar3 = *(int *)((int)this + 0x38) - **(int **)((int)this + 0xc);
        iVar4 = (int)uVar3 >> 0x1f;
        if (((int)uVar5 <= iVar4) && (((int)uVar5 < iVar4 || (uVar7 <= uVar3)))) {
          iVar4 = (**(int **)((int)this + 0xc) - **(int **)((int)this + 0x20)) + uVar7;
          **(int **)((int)this + 0x30) = **(int **)((int)this + 0x30) - iVar4;
          **(int **)((int)this + 0x20) = **(int **)((int)this + 0x20) + iVar4;
          uVar6 = uVar5;
          uVar8 = uVar7;
        }
      }
    }
    else if (-1 < (int)uVar5) {
      uVar3 = *(int *)((int)this + 0x38) - **(int **)((int)this + 0xc);
      iVar4 = (int)uVar3 >> 0x1f;
      if (((int)uVar5 <= iVar4) && (((int)uVar5 < iVar4 || (uVar7 <= uVar3)))) {
        iVar4 = (**(int **)((int)this + 0xc) - **(int **)((int)this + 0x1c)) + uVar7;
        **(int **)((int)this + 0x2c) = **(int **)((int)this + 0x2c) - iVar4;
        **(int **)((int)this + 0x1c) = **(int **)((int)this + 0x1c) + iVar4;
        uVar6 = uVar5;
        uVar8 = uVar7;
        if (((param_8 & 2) != 0) && (iVar4 = **(int **)((int)this + 0x20), iVar4 != 0)) {
          iVar1 = **(int **)((int)this + 0x1c);
          iVar2 = **(int **)((int)this + 0x30);
          **(int **)((int)this + 0x20) = iVar1;
          **(int **)((int)this + 0x30) = (iVar2 + iVar4) - iVar1;
        }
      }
    }
  }
  *param_1 = uVar8;
  param_1[1] = uVar6;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}


