// FUN_0040f6b0 @ 0040f6b0 size=237 callers=36

int * __fastcall FUN_0040f6b0(int param_1,int *param_2,WPARAM param_3)

{
  int *piVar1;
  int *lParam;
  int iVar2;
  BOOL BVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a547;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  lParam = operator_new(0x30);
  lParam[9] = 0;
  local_8 = 1;
  piVar1 = (int *)param_2[9];
  if (piVar1 != (int *)0x0) {
    if (piVar1 == param_2) {
      iVar2 = (**(code **)(*piVar1 + 4))(lParam);
      lParam[9] = iVar2;
      piVar1 = (int *)param_2[9];
      if (piVar1 == (int *)0x0) goto LAB_0040f732;
      (**(code **)(*piVar1 + 0x10))(piVar1 != param_2);
    }
    else {
      lParam[9] = (int)piVar1;
    }
    param_2[9] = 0;
  }
LAB_0040f732:
  *(undefined1 *)(lParam + 10) = 1;
  BVar3 = PostMessageA(*(HWND *)(&DAT_004a2470 + param_1 * 4),0x9e41,param_3,(LPARAM)lParam);
  if (BVar3 == 0) {
    piVar1 = (int *)lParam[9];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x10))(piVar1 != lParam);
      lParam[9] = 0;
    }
    FUN_0045a6a4(lParam);
    ExceptionList = local_10;
    return (int *)0x0;
  }
  ExceptionList = local_10;
  return lParam;
}


