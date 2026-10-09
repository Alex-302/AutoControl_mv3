// FUN_00406700 @ 00406700 size=251 callers=1

int __fastcall FUN_00406700(RECT *param_1,RECT *param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  tagRECT local_58;
  LONG local_48 [2];
  int local_40 [3];
  LONG local_34;
  LONG local_30;
  int local_2c;
  int local_28;
  int local_24;
  LONG local_20;
  LONG local_1c;
  LONG local_18;
  int local_14;
  int local_10;
  LONG local_c;
  
  local_58.left = 0;
  local_58.top = 0;
  local_58.right = 0;
  local_58.bottom = 0;
  IntersectRect(&local_58,param_1,param_2);
  iVar1 = (local_58.right - local_58.left) * (local_58.bottom - local_58.top);
  if ((-1 < iVar1) && (iVar1 != 0)) {
    local_40[1] = local_58.top;
    local_14 = local_58.top;
    iVar2 = 0;
    local_48[1] = param_1->top;
    local_34 = param_1->top;
    local_30 = param_1->right;
    local_20 = param_1->right;
    local_2c = local_58.bottom;
    local_28 = local_58.left;
    local_24 = local_58.bottom;
    iVar1 = 4;
    local_10 = local_58.left;
    piVar4 = local_48 + 1;
    local_48[0] = param_1->left;
    local_40[0] = local_58.right;
    local_40[2] = local_58.right;
    local_1c = param_1->bottom;
    local_18 = param_1->left;
    local_c = param_1->bottom;
    do {
      iVar3 = (piVar4[2] - *piVar4) * (piVar4[1] - piVar4[-1]);
      if ((-1 < iVar3) && (iVar3 != 0)) {
        FUN_004330c0(param_3,piVar4 + -1);
        iVar2 = iVar2 + iVar3;
      }
      piVar4 = piVar4 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return iVar2;
  }
  FUN_004330c0(param_3,&param_1->left);
  iVar1 = (param_1->bottom - param_1->top) * (param_1->right - param_1->left);
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  return iVar1;
}


