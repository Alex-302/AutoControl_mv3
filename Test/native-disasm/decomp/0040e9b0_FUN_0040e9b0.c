// FUN_0040e9b0 @ 0040e9b0 size=146 callers=4

void __fastcall FUN_0040e9b0(HWND param_1,char param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int *piVar5;
  tagRECT local_30;
  int local_20 [7];
  
  cVar4 = FUN_00409750(param_1);
  if (cVar4 != '\0') {
    piVar5 = (int *)FUN_0040e5c0(param_1,param_2,local_20);
    iVar1 = piVar5[1];
    iVar2 = piVar5[2];
    iVar3 = piVar5[3];
    *param_3 = *piVar5;
    param_3[1] = iVar1;
    param_3[2] = iVar2;
    param_3[3] = iVar3;
    return;
  }
  local_30.left = 0;
  local_30.top = 0;
  local_30.right = 0;
  local_30.bottom = 0;
  GetClientRect(param_1,&local_30);
  ClientToScreen(param_1,(LPPOINT)&local_30);
  *param_3 = local_30.left;
  param_3[1] = local_30.top;
  param_3[2] = local_30.right + local_30.left;
  param_3[3] = local_30.bottom + local_30.top;
  return;
}


