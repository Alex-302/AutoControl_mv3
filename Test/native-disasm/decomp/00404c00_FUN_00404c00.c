// FUN_00404c00 @ 00404c00 size=50 callers=2

LPRECT __fastcall FUN_00404c00(HWND param_1,char param_2,LPRECT param_3)

{
  int iVar1;
  
  param_3->left = 0;
  param_3->top = 0;
  param_3->right = 0;
  param_3->bottom = 0;
  GetWindowRect(param_1,param_3);
  if (param_2 != '\0') {
    iVar1 = GetSystemMetrics(0x20);
    param_3->left = param_3->left + iVar1;
    param_3->top = param_3->top + iVar1;
    param_3->right = param_3->right - iVar1;
    param_3->bottom = param_3->bottom - iVar1;
  }
  return param_3;
}


