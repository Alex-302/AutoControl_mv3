// FUN_00428950 @ 00428950 size=309 callers=1

undefined1 * __cdecl FUN_00428950(undefined1 *param_1,void *param_2)

{
  HWND wParam;
  uint uVar1;
  void *this;
  char *pcVar2;
  HWND hWnd;
  undefined4 ****ppppuVar3;
  undefined4 ***local_3c [4];
  int local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  undefined4 ***local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c7ce;
  local_10 = ExceptionList;
  wParam = *(HWND *)(&DAT_004a2470 + DAT_004a23dc * 4);
  ppppuVar3 = local_3c;
  local_18 = 0;
  ExceptionList = &local_10;
  this = (void *)FUN_00434600(param_2,1);
  FUN_00434740(this,(undefined1 *)ppppuVar3);
  local_8 = 0;
  pcVar2 = (char *)FUN_00434600(param_2,0);
  FUN_00453810(pcVar2,&local_14);
  local_24 = local_14;
  local_20 = local_2c + 1;
  local_1c = local_3c;
  if (0xf < local_28) {
    local_1c = local_3c[0];
  }
  for (hWnd = FindWindowExA((HWND)0xfffffffd,(HWND)0x0,"ACtl.msgWin",(LPCSTR)0x0); hWnd != (HWND)0x0
      ; hWnd = FindWindowExA((HWND)0xfffffffd,hWnd,"ACtl.msgWin",(LPCSTR)0x0)) {
    if (hWnd != wParam) {
      SendMessageA(hWnd,0x4a,(WPARAM)wParam,(LPARAM)&local_24);
    }
  }
  uVar1 = (uint)local_8 >> 8;
  local_8 = CONCAT31((int3)uVar1,1);
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  if (0xf < local_28) {
    ppppuVar3 = (undefined4 ****)local_3c[0];
    if (0xfff < local_28 + 1) {
      if (((uint)local_3c[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      ppppuVar3 = (undefined4 ****)local_3c[0][-1];
      if (local_3c[0] <= ppppuVar3) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_3c[0] - (int)ppppuVar3) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_3c[0] - (int)ppppuVar3)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(ppppuVar3);
  }
  ExceptionList = local_10;
  return param_1;
}


