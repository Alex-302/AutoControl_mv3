// FUN_0040e8d0 @ 0040e8d0 size=214 callers=1

HDC __fastcall FUN_0040e8d0(HDC param_1,HWND param_2,int param_3,HDC param_4)

{
  char cVar1;
  int *piVar2;
  tagRECT local_30;
  int local_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  
  cVar1 = FUN_00409750(param_2);
  if (cVar1 != '\0') {
    local_30.left = 0;
    local_30.top = 0;
    local_30.right = 0;
    local_30.bottom = 0;
    GetWindowRect(param_2,&local_30);
    iStack_18 = local_30.right - local_30.left;
    iStack_14 = local_30.bottom - local_30.top;
    local_20 = local_30.left;
    iStack_1c = local_30.top;
    if ((200 < iStack_18) && (0x32 < iStack_14)) {
      piVar2 = FUN_0040e3a0(param_2,&local_20,&local_30.left,'\0');
      local_30.left = *piVar2;
      local_30.top = piVar2[1];
      local_30.right = piVar2[2];
      local_30.bottom = piVar2[3];
      if (10 < local_30.bottom) {
        FUN_0040b030(param_1,param_2,&local_20,&local_30.left,param_3,param_4);
        return param_1;
      }
    }
  }
  param_1->unused = 0;
  return param_1;
}


