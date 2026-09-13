// FUN_0040e800 @ 0040e800 size=207 callers=1

HWND __fastcall FUN_0040e800(HWND param_1)

{
  LONG LVar1;
  int *piVar2;
  HWND hWnd;
  tagRECT local_30;
  int local_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  
  if (DAT_004a23a4 < 0x47) {
    local_30.left = 0;
    local_30.top = 0;
    local_30.right = 0;
    local_30.bottom = 0;
    GetWindowRect(param_1,&local_30);
    LVar1 = local_30.top;
    iStack_18 = local_30.right - local_30.left;
    iStack_14 = local_30.bottom - local_30.top;
    local_20 = local_30.left;
    iStack_1c = local_30.top;
    piVar2 = FUN_0040e3a0(param_1,&local_20,&local_30.left,'\0');
    local_20 = *piVar2;
    iStack_1c = piVar2[1];
    iStack_18 = piVar2[2];
    iStack_14 = piVar2[3];
    hWnd = GetWindow(param_1,5);
    local_30.left = 0;
    local_30.top = 0;
    local_30.right = 0;
    local_30.bottom = 0;
    GetWindowRect(hWnd,&local_30);
    if (((LVar1 + 0x32 < local_30.top) && (local_30.top < iStack_1c + 10)) &&
       (local_30.right < local_20 + -0x19 + iStack_18)) {
      return hWnd;
    }
  }
  return (HWND)0x0;
}


