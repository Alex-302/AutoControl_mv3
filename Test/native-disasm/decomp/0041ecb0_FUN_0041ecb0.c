// FUN_0041ecb0 @ 0041ecb0 size=484 callers=1

void FUN_0041ecb0(void)

{
  POINT pt;
  HMENU hmenu;
  ushort uVar1;
  BOOL BVar2;
  uint uVar3;
  HMENU pHVar4;
  HWND hwnd;
  HWND hWnd;
  UINT item;
  tagPOINT local_48;
  tagPOINT local_40;
  MENUITEMINFOW local_38;
  
  BVar2 = IsMenu(DAT_004a2528);
  if ((BVar2 != 0) && (uVar3 = FUN_0041eb70('\0'), (char)uVar3 == '\0')) {
    return;
  }
  uVar1 = FUN_0041d340(DAT_004a29dc,DAT_004a29d4);
  item = (uint)(DAT_004a29e4 == 'B') + (uint)uVar1;
  local_48.x = (LONG)FUN_00419890((uint)DAT_004a2520);
  if ((*(byte *)(local_48.x + 0x26) & 2) == 0) {
    pHVar4 = (HMENU)0x0;
  }
  else {
    pHVar4 = FUN_0041dab0(DAT_004a2520,0xf0000000);
  }
  uVar3 = 0;
  if (DAT_004a29e4 == 'T') {
    local_38.cbSize = 0x30;
    local_38.fMask = 0x100;
    local_38.fType = 0;
    local_38.fState = 0;
    local_38.wID = 0;
    local_38.hSubMenu = (HMENU)0x0;
    local_38.hbmpChecked = (HBITMAP)0x0;
    local_38.hbmpUnchecked = (HBITMAP)0x0;
    local_38.dwItemData = 0;
    local_38.dwTypeData = (LPWSTR)0x0;
    local_38.cch = 0;
    local_38.hbmpItem = (HBITMAP)0x0;
    BVar2 = GetMenuItemInfoA(DAT_004a29dc,item,1,(LPMENUITEMINFOA)&local_38);
    if ((BVar2 != 0) && (uVar3 = local_38.fType & 0x60, uVar3 != 0)) {
      local_38.fType = local_38.fType & ~uVar3;
      SetMenuItemInfoA(DAT_004a29dc,item,1,(LPCMENUITEMINFOA)&local_38);
    }
  }
  hmenu = DAT_004a29dc;
  local_38.cbSize = 0x30;
  _memset(&local_38.fMask,0,0x2c);
  local_38.wID = (UINT)DAT_004a2520;
  local_38.fType = uVar3 | 0x100;
  local_38.fMask = 0x127;
  local_38.fState = 0;
  local_38.dwItemData = (ULONG_PTR)hmenu;
  local_38.hSubMenu = pHVar4;
  BVar2 = InsertMenuItemW(hmenu,item,1,&local_38);
  if (BVar2 != 0) {
    *(HMENU *)(local_48.x + 0x1c) = DAT_004a29dc;
    if (DAT_004a29d4 == 0xfffffffe) {
      DeleteMenu(DAT_004a29dc,0xfffffffe,0);
    }
    GetCursorPos(&local_40);
    local_48.x = local_40.x;
    local_48.y = local_40.y;
    hwnd = GetDesktopWindow();
    pt.y = local_48.y;
    pt.x = local_48.x;
    hWnd = ChildWindowFromPointEx(hwnd,pt,5);
    if (hWnd == hwnd) {
      hWnd = (HWND)0x0;
    }
    ScreenToClient(hWnd,&local_48);
    PostMessageA(hWnd,0x200,0,CONCAT22((undefined2)local_48.y,(undefined2)local_48.x));
  }
  return;
}


