// FUN_00406da0 @ 00406da0 size=120 callers=1

undefined4 FUN_00406da0(HWND param_1,int *param_2)

{
  BOOL BVar1;
  tagRECT local_30;
  RECT local_20;
  
  if (param_1 == (HWND)*param_2) {
    return 0;
  }
  BVar1 = IsWindowVisible(param_1);
  if ((BVar1 != 0) && (BVar1 = IsIconic(param_1), BVar1 == 0)) {
    local_30.left = 0;
    local_30.top = 0;
    local_30.right = 0;
    local_30.bottom = 0;
    GetWindowRect(param_1,&local_30);
    local_20.left = local_30.left;
    local_20.top = local_30.top;
    local_20.right = local_30.right;
    local_20.bottom = local_30.bottom;
    FUN_00406800((void *)param_2[1],&local_20);
    if (*(uint *)(param_2[1] + 0xc) < (uint)param_2[2]) {
      return 0;
    }
  }
  return 1;
}


