// FUN_00406900 @ 00406900 size=476 callers=1

int ** __thiscall FUN_00406900(void *this,RECT *param_1)

{
  RECT *pRVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int *piVar7;
  RECT *lprcSrc1;
  tagRECT local_68;
  int local_54 [4];
  int *local_44;
  int *local_40;
  int *local_3c;
  int **local_38;
  int local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_004795c8;
  local_28 = (int *)0x0;
  local_44 = (int *)0x0;
  local_40 = (int *)0x0;
  local_24 = (int *)0x0;
  local_3c = (int *)0x0;
  local_14 = 0;
  pRVar1 = *(RECT **)((int)this + 4);
  lprcSrc1 = *(RECT **)this;
  local_2c = (int *)0x0;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  for (; local_38 = this, lprcSrc1 != pRVar1; lprcSrc1 = lprcSrc1 + 1) {
    local_68.left = 0;
    local_68.top = 0;
    local_68.right = 0;
    local_68.bottom = 0;
    IntersectRect(&local_68,lprcSrc1,param_1);
    local_54[0] = local_68.left;
    local_54[1] = local_68.top;
    local_54[2] = local_68.right;
    local_54[3] = local_68.bottom;
    local_34 = (local_68.bottom - local_68.top) * (local_68.right - local_68.left);
    if ((-1 < local_34) && (local_34 != 0)) {
      if ((local_54 < local_40) && (local_28 <= local_54)) {
        local_30 = (int)local_54 - (int)local_28 >> 4;
        if (local_40 == local_24) {
          FUN_00436dc0((int *)&local_44);
          local_24 = local_3c;
          local_28 = local_44;
        }
        if (local_40 != (int *)0x0) {
          piVar7 = local_28 + local_30 * 4;
          iVar2 = piVar7[1];
          iVar3 = piVar7[2];
          iVar4 = piVar7[3];
          *local_40 = *piVar7;
          local_40[1] = iVar2;
          local_40[2] = iVar3;
          local_40[3] = iVar4;
        }
      }
      else {
        if (local_40 == local_24) {
          FUN_00436dc0((int *)&local_44);
          local_24 = local_3c;
          local_28 = local_44;
        }
        if (local_40 != (int *)0x0) {
          *local_40 = local_68.left;
          local_40[1] = local_68.top;
          local_40[2] = local_68.right;
          local_40[3] = local_68.bottom;
        }
      }
      local_40 = local_40 + 4;
      local_2c = (int *)((int)local_2c + local_34);
    }
    this = local_38;
  }
  piVar5 = local_24;
  piVar7 = local_28;
  if (this != &local_44) {
    piVar7 = *(int **)this;
    *(int **)this = local_28;
    *(int **)((int)this + 4) = local_40;
    piVar5 = *(int **)((int)this + 8);
    *(int **)((int)this + 8) = local_24;
  }
  *(int **)((int)this + 0xc) = local_2c;
  if (piVar7 != (int *)0x0) {
    uVar6 = (int)piVar5 - (int)piVar7 >> 4;
    if (0xfffffff < uVar6) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    piVar5 = piVar7;
    if (0xfff < uVar6 << 4) {
      if (((uint)piVar7 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      piVar5 = (int *)piVar7[-1];
      if (piVar7 <= piVar5) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)piVar7 - (int)piVar5) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)piVar7 - (int)piVar5)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(piVar5);
  }
  ExceptionList = local_1c;
  return this;
}


