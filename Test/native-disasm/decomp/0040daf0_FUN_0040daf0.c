// FUN_0040daf0 @ 0040daf0 size=58 callers=1

undefined4 __fastcall FUN_0040daf0(HWND param_1)

{
  HWND hWnd;
  LRESULT LVar1;
  HWND local_4;
  
  local_4 = param_1;
  hWnd = FindWindowExA(param_1,(HWND)0x0,PTR_s_Chrome_RenderWidgetHostHWND_0049d9f0,(LPCSTR)0x0);
  if (hWnd != (HWND)0x0) {
    LVar1 = SendMessageTimeoutA(hWnd,0x3d,0,1,0x22,1000,(PDWORD_PTR)&local_4);
    if (LVar1 != 0) {
      return CONCAT31((int3)((uint)LVar1 >> 8),1);
    }
  }
  return 0;
}


