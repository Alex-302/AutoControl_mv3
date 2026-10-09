// FUN_004250d0 @ 004250d0 size=384 callers=1

void * __cdecl FUN_004250d0(void *param_1,void *param_2)

{
  HWND hWnd;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047c069;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = 0;
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_2c,(uint *)"refWin",6);
  local_8 = 1;
  hWnd = (HWND)FUN_004409d0(param_2,local_2c,0);
  local_8 = local_8 & 0xffffff00;
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  if (hWnd == (HWND)0x0) {
    DAT_004a2460 = 0;
  }
  else if (DAT_004a2460 == 0) {
    DAT_004a2460 = GetWindowThreadProcessId(hWnd,&DAT_004a2454);
  }
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  local_8 = 0;
  local_14 = 1;
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_0043ace0(local_44,(uint *)"inclHjkd",8);
  local_8 = 2;
  DAT_004a2a88 = FUN_00441100(param_2,local_44);
  if (0xf < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  if (DAT_004a2a88 != '\0') {
    DAT_004a3344 = GetDesktopWindow();
    EnumChildWindows(DAT_004a3344,thunk_FUN_00425250,(LPARAM)param_1);
    ExceptionList = local_10;
    return param_1;
  }
  EnumThreadWindows(DAT_004a2460,thunk_FUN_00425250,(LPARAM)param_1);
  ExceptionList = local_10;
  return param_1;
}


