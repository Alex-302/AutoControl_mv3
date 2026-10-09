// FUN_00415d10 @ 00415d10 size=275 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte FUN_00415d10(void)

{
  HWND hwnd;
  HRESULT HVar1;
  DWORD idThread;
  tagGUITHREADINFO *pgui;
  tagGUITHREADINFO local_68;
  undefined4 local_38;
  undefined4 uStack_34;
  int iStack_30;
  int iStack_2c;
  int *local_28;
  byte local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_0047af3e;
  local_1c = ExceptionList;
  local_28 = (int *)0x0;
  local_14 = 0;
  ExceptionList = &local_1c;
  hwnd = GetForegroundWindow();
  HVar1 = AccessibleObjectFromWindow(hwnd,0xfffffff8,(IID *)&DAT_00483d48,&local_28);
  if (HVar1 == 0) {
    local_38 = 0;
    uStack_34 = 0;
    iStack_30 = 0;
    iStack_2c = 0;
    if (local_28 != (int *)0x0) {
      (**(code **)(*local_28 + 0x58))
                (local_28,&local_38,&uStack_34,&iStack_30,&iStack_2c,_DAT_0048e618,_UNK_0048e61c,
                 _UNK_0048e620,_UNK_0048e624);
    }
    if ((iStack_30 != 0) && (iStack_2c != 0)) {
      local_21 = 1;
      goto LAB_00415de6;
    }
  }
  local_68.cbSize = 0x30;
  _memset(&local_68.flags,0,0x2c);
  pgui = &local_68;
  idThread = GetWindowThreadProcessId(hwnd,(LPDWORD)0x0);
  GetGUIThreadInfo(idThread,pgui);
  local_21 = (byte)local_68.flags & 1;
LAB_00415de6:
  local_14 = 2;
  if (local_28 != (int *)0x0) {
    (**(code **)(*local_28 + 8))(local_28);
    ExceptionList = local_1c;
    return local_21;
  }
  ExceptionList = local_1c;
  return local_21;
}


