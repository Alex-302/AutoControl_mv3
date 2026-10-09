// FUN_004063a0 @ 004063a0 size=207 callers=1

bool __fastcall FUN_004063a0(HWND param_1)

{
  HMONITOR hMonitor;
  BOOL BVar1;
  int iVar2;
  LONG Y;
  int iVar3;
  LONG X;
  tagRECT local_50;
  tagMONITORINFO local_38;
  
  local_50.left = 0;
  local_50.top = 0;
  local_50.right = 0;
  local_50.bottom = 0;
  GetWindowRect(param_1,&local_50);
  hMonitor = MonitorFromWindow(param_1,2);
  local_38.cbSize = 0x28;
  local_38.dwFlags = 0;
  local_38.rcMonitor.left = 0;
  local_38.rcMonitor.top = 0;
  local_38.rcMonitor.right = 0;
  local_38.rcMonitor.bottom = 0;
  local_38.rcWork.left = 0;
  local_38.rcWork.top = 0;
  local_38.rcWork.right = 0;
  local_38.rcWork.bottom = 0;
  GetMonitorInfoA(hMonitor,&local_38);
  iVar3 = local_50.right - local_38.rcMonitor.right;
  iVar2 = iVar3;
  if (iVar3 < 0) {
    iVar2 = 0;
  }
  X = local_38.rcMonitor.left;
  if (local_38.rcMonitor.left <= local_50.left - iVar2) {
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    X = local_50.left - iVar3;
  }
  iVar3 = local_50.bottom - local_38.rcMonitor.bottom;
  iVar2 = iVar3;
  if (iVar3 < 0) {
    iVar2 = 0;
  }
  Y = local_38.rcMonitor.top;
  if (local_38.rcMonitor.top <= local_50.top - iVar2) {
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    Y = local_50.top - iVar3;
  }
  BVar1 = SetWindowPos(param_1,(HWND)0x0,X,Y,0,0,0x215);
  return BVar1 != 0;
}


