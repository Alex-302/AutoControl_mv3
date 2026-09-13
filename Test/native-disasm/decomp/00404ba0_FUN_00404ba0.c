// FUN_00404ba0 @ 00404ba0 size=90 callers=1

void __thiscall FUN_00404ba0(void *this,DWORD *param_1)

{
  HMONITOR hMonitor;
  tagMONITORINFO local_28;
  
  hMonitor = MonitorFromPoint(*(POINT *)this,2);
  local_28.cbSize = 0x28;
  local_28.dwFlags = 0;
  local_28.rcMonitor.left = 0;
  local_28.rcMonitor.top = 0;
  local_28.rcMonitor.right = 0;
  local_28.rcMonitor.bottom = 0;
  local_28.rcWork.left = 0;
  local_28.rcWork.top = 0;
  local_28.rcWork.right = 0;
  local_28.rcWork.bottom = 0;
  GetMonitorInfoA(hMonitor,&local_28);
  *param_1 = local_28.cbSize;
  param_1[1] = local_28.rcMonitor.left;
  param_1[2] = local_28.rcMonitor.top;
  param_1[3] = local_28.rcMonitor.right;
  param_1[4] = local_28.rcMonitor.bottom;
  param_1[5] = local_28.rcWork.left;
  param_1[6] = local_28.rcWork.top;
  param_1[7] = local_28.rcWork.right;
  *(ulonglong *)(param_1 + 8) = CONCAT44(local_28.dwFlags,local_28.rcWork.bottom);
  return;
}


