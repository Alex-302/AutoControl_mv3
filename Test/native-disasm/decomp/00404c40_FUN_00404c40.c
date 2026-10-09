// FUN_00404c40 @ 00404c40 size=145 callers=5

void __thiscall FUN_00404c40(void *this,int *param_1)

{
  HMONITOR hMonitor;
  tagMONITORINFO local_60;
  WINDOWPLACEMENT local_34;
  
  local_34.length = 0x2c;
  local_34.flags = 0;
  local_34.showCmd = 0;
  local_34.ptMinPosition.x = 0;
  local_34.ptMinPosition.y = 0;
  local_34.ptMaxPosition.x = 0;
  local_34.ptMaxPosition.y = 0;
  local_34.rcNormalPosition.left = 0;
  local_34.rcNormalPosition.top = 0;
  local_34.rcNormalPosition.right = 0;
  local_34.rcNormalPosition.bottom = 0;
  GetWindowPlacement(this,&local_34);
  hMonitor = MonitorFromWindow(this,2);
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
  *param_1 = local_34.rcNormalPosition.left + local_60.rcWork.left;
  param_1[1] = local_34.rcNormalPosition.top + local_60.rcWork.top;
  param_1[2] = local_34.rcNormalPosition.right + local_60.rcWork.left;
  param_1[3] = local_34.rcNormalPosition.bottom + local_60.rcWork.top;
  return;
}


