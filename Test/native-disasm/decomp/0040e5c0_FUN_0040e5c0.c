// FUN_0040e5c0 @ 0040e5c0 size=173 callers=2

void __fastcall FUN_0040e5c0(HWND param_1,char param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  tagRECT local_30;
  int local_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int local_10 [4];
  
  local_30.left = 0;
  local_30.top = 0;
  local_30.right = 0;
  local_30.bottom = 0;
  GetWindowRect(param_1,&local_30);
  iStack_18 = local_30.right - local_30.left;
  iStack_14 = local_30.bottom - local_30.top;
  local_20 = local_30.left;
  iStack_1c = local_30.top;
  piVar5 = FUN_0040e3a0(param_1,&local_20,local_10,param_2);
  iVar1 = *piVar5;
  iVar2 = piVar5[1];
  iVar3 = piVar5[2];
  iVar4 = piVar5[3];
  *param_3 = iVar1;
  param_3[1] = iVar2;
  param_3[2] = iVar3 + iVar1;
  param_3[3] = iVar4 + iVar2;
  return;
}


