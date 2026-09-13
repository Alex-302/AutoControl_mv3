// FUN_00418cc0 @ 00418cc0 size=419 callers=3

void FUN_00418cc0(void)

{
  HWND pHVar1;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar2;
  WNDCLASSEXA local_58;
  POINT local_28;
  HDC local_20;
  HGDIOBJ local_1c;
  SIZE local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b2c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00418910(&local_20);
  local_8 = 0;
  FUN_0040a930(&local_20,&local_18.cx);
  pHVar1 = DAT_004a25d4;
  if (DAT_004a25d4 == (HWND)0x0) {
    iVar2 = *(int *)ThreadLocalStoragePointer;
    if (*(int *)(iVar2 + 8) < DAT_004a2e40) {
      FUN_0045a219(&DAT_004a2e40);
      iVar2 = extraout_ECX;
      if (DAT_004a2e40 == -1) {
        local_58.cbSize = 0x30;
        local_58.style = (UINT)pHVar1;
        local_58.lpfnWndProc = DefWindowProcA_exref;
        local_58.cbClsExtra = (int)pHVar1;
        local_58.cbWndExtra = (int)pHVar1;
        local_58.hInstance = GetModuleHandleA((LPCSTR)0x0);
        local_58.hIcon = (HICON)pHVar1;
        local_58.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
        local_58.hbrBackground = (HBRUSH)0x10;
        local_58.lpszMenuName = (LPCSTR)pHVar1;
        local_58.lpszClassName = "ACNH_gestDisplay";
        local_58.hIconSm = (HICON)pHVar1;
        RegisterClassExA(&local_58);
        FUN_0045a1da(&DAT_004a2e40);
        iVar2 = extraout_ECX_00;
      }
    }
    FUN_004187a0(iVar2,local_18.cy);
    DAT_004a25d4 = CreateWindowExA(0x800a8,"ACNH_gestDisplay","",0x80000000,-0x80000000,-0x80000000,
                                   local_18.cx,local_18.cy,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,
                                   (LPVOID)0x0);
    ShowWindow(DAT_004a25d4,4);
  }
  SetWindowPos(DAT_004a25d4,(HWND)0x0,DAT_004a25cc - local_18.cx / 2,DAT_004a25d0 - local_18.cy / 2,
               local_18.cx,local_18.cy,0x14);
  local_28.x = 0;
  local_28.y = 0;
  UpdateLayeredWindow(DAT_004a25d4,(HDC)0x0,(POINT *)0x0,&local_18,local_20,&local_28,0,
                      (BLENDFUNCTION *)&DAT_0049da80,2);
  DeleteDC(local_20);
  DeleteObject(local_1c);
  ExceptionList = local_10;
  return;
}


