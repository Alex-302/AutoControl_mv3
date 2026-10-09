// FUN_004167f0 @ 004167f0 size=606 callers=2

char __fastcall FUN_004167f0(int param_1)

{
  bool bVar1;
  bool bVar2;
  BOOL BVar3;
  undefined **local_3c;
  int local_38;
  undefined ***local_18;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047afd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_004a23a4 < 0x49) {
    local_18 = &local_3c;
    local_3c = &PTR_LAB_0048eb0c;
    local_8 = 0;
    ExceptionList = &local_10;
    local_38 = param_1;
    FUN_0040f6b0(DAT_004a2458,(int *)local_18,0);
    local_8 = 0xffffffff;
    if (local_18 != (undefined ***)0x0) {
      (*(code *)(*local_18)[4])(local_18 != &local_3c);
      local_18 = (undefined ***)0x0;
    }
  }
  if ((param_1 != 0) && (DAT_0049fc54 != '\0')) {
    ExceptionList = local_10;
    return DAT_0049fc54;
  }
  if (DAT_004a2394 == (HWINEVENTHOOK)0x0) {
LAB_00416893:
    local_11 = '\x01';
  }
  else {
    BVar3 = UnhookWinEvent(DAT_004a2394);
    local_11 = '\0';
    if (BVar3 != 0) goto LAB_00416893;
  }
  if (DAT_004a2a54 != (HWINEVENTHOOK)0x0) {
    BVar3 = UnhookWinEvent(DAT_004a2a54);
    local_12 = '\0';
    if (BVar3 == 0) goto LAB_004168af;
  }
  local_12 = '\x01';
LAB_004168af:
  if ((DAT_0049fc5c == (HWINEVENTHOOK)0x0) || (BVar3 = UnhookWinEvent(DAT_0049fc5c), BVar3 != 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((DAT_0049fc2c == (HWINEVENTHOOK)0x0) || (BVar3 = UnhookWinEvent(DAT_0049fc2c), BVar3 != 0)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (param_1 != 0) {
    if (DAT_0049d9c0 < 0) {
      DAT_0049d9c0 = CoInitialize((LPVOID)0x0);
    }
    DAT_004a2394 = SetWinEventHook(0x8005,0x8005,(HMODULE)0x0,FUN_004166c0,0,0,2);
    DAT_004a2a54 = SetWinEventHook(0x8002,0x8003,(HMODULE)0x0,FUN_004166c0,0,0,2);
    DAT_0049fc5c = SetWinEventHook(4,5,(HMODULE)0x0,FUN_004167e0,0,0,0);
    if (DAT_004a23a4 < 0x3c) {
      DAT_0049fc2c = SetWinEventHook(0x11b,0x11b,(HMODULE)0x0,FUN_004166c0,0,0,2);
    }
    if ((((-1 < DAT_0049d9c0) && (DAT_004a2394 != (HWINEVENTHOOK)0x0)) &&
        ((DAT_004a2a54 != (HWINEVENTHOOK)0x0 && (DAT_0049fc5c != (HWINEVENTHOOK)0x0)))) &&
       ((0x3b < DAT_004a23a4 || (DAT_0049fc2c != (HWINEVENTHOOK)0x0)))) {
      DAT_0049fc54 = '\x01';
      DAT_004a23c5 = FUN_00415d10();
      ExceptionList = local_10;
      return DAT_0049fc54;
    }
    DAT_0049fc54 = 0;
    ExceptionList = local_10;
    return '\0';
  }
  if (-1 < DAT_0049d9c0) {
    CoUninitialize();
    DAT_0049d9c0 = -0x7fffbfff;
  }
  DAT_0049fc54 = 0;
  if ((((local_11 != '\0') && (local_12 != '\0')) && (bVar1)) && (bVar2)) {
    ExceptionList = local_10;
    return '\x01';
  }
  ExceptionList = local_10;
  return '\0';
}


