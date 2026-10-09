// FUN_00404ce0 @ 00404ce0 size=179 callers=2

void __fastcall
FUN_00404ce0(HWND param_1,UINT param_2,int param_3,int param_4,int param_5,int param_6)

{
  HMONITOR hMonitor;
  tagMONITORINFO local_60;
  WINDOWPLACEMENT local_34;
  
  hMonitor = MonitorFromWindow(param_1,2);
  local_60.cbSize = 0x28;
  local_60.dwFlags = 0;
  local_60.rcMonitor.left = 0;
  local_60.rcMonitor.top = 0;
  local_60.rcMonitor.right = 0;
  local_60.rcMonitor.bottom = 0;
  local_60.rcWork.left = 0;
  local_60.rcWork.top = 0;
  local_60.rcWork.right = 0;
  local_60.rcWork.bottom = 0;
  GetMonitorInfoA(hMonitor,&local_60);
  local_34.rcNormalPosition.left = param_3 - local_60.rcWork.left;
  local_34.rcNormalPosition.right = param_5 - local_60.rcWork.left;
  local_34.rcNormalPosition.top = param_4 - local_60.rcWork.top;
  local_34.rcNormalPosition.bottom = param_6 - local_60.rcWork.top;
  local_34.ptMinPosition.x = 0;
  local_34.ptMinPosition.y = 0;
  local_34.ptMaxPosition.x = 0;
  local_34.ptMaxPosition.y = 0;
  local_34.length = 0x2c;
  local_34.flags = 0;
  local_34.showCmd = param_2;
  SetWindowPlacement(param_1,&local_34);
  return;
}


