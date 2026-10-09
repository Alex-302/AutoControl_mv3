// FUN_004187a0 @ 004187a0 size=368 callers=1

void FUN_004187a0(undefined4 param_1,int param_2)

{
  POINT pt;
  char cVar1;
  HMONITOR hMonitor;
  HWND pHVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  UINT gaFlags;
  tagPOINT local_50 [3];
  tagMONITORINFO local_38;
  
  GetCursorPos(local_50);
  DAT_004a25cc = local_50[0].x;
  DAT_004a25d0 = local_50[0].y;
  pt.y = local_50[0].y;
  pt.x = local_50[0].x;
  hMonitor = MonitorFromPoint(pt,2);
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
  iVar4 = local_38.rcWork.top;
  iVar5 = local_38.rcWork.bottom;
  if ((char)DAT_004a25dd != 'S') {
    if ((char)DAT_004a25dd != 'W') {
      cVar1 = (char)((uint)DAT_004a25dd >> 8);
      if (cVar1 == 'T') {
        DAT_004a25d0 = DAT_004a25d0 - param_2;
      }
      else if (cVar1 == 'B') {
        DAT_004a25d0 = DAT_004a25d0 + param_2;
      }
      goto LAB_004188e5;
    }
    gaFlags = 3;
    pHVar2 = GetForegroundWindow();
    pHVar2 = GetAncestor(pHVar2,gaFlags);
    piVar3 = (int *)FUN_0040e9b0(pHVar2,'\0',&local_50[0].x);
    local_38.rcWork.left = *piVar3;
    local_38.rcWork.right = piVar3[2];
    iVar4 = piVar3[1];
    iVar5 = piVar3[3];
  }
  DAT_004a25cc = (local_38.rcWork.right + local_38.rcWork.left) / 2;
  DAT_004a25d0 = (iVar5 + iVar4) / 2;
  cVar1 = (char)((uint)DAT_004a25dd >> 8);
  if (cVar1 == 'T') {
    iVar4 = param_2 / 2 + iVar4 + 0xf;
    if (iVar4 < DAT_004a25d0) {
      DAT_004a25d0 = iVar4;
    }
  }
  else if ((cVar1 == 'B') && (iVar4 = (iVar5 - param_2 / 2) + -0xf, DAT_004a25d0 < iVar4)) {
    DAT_004a25d0 = iVar4;
  }
LAB_004188e5:
  iVar4 = local_38.rcWork.top + param_2 / 2;
  if (iVar4 < DAT_004a25d0) {
    iVar4 = DAT_004a25d0;
  }
  DAT_004a25d0 = local_38.rcWork.bottom - param_2 / 2;
  if (iVar4 < DAT_004a25d0) {
    DAT_004a25d0 = iVar4;
  }
  return;
}


