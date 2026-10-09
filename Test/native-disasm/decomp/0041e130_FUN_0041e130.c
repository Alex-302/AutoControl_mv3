// FUN_0041e130 @ 0041e130 size=238 callers=1

void __fastcall FUN_0041e130(int param_1)

{
  ushort uVar1;
  int iVar2;
  UINT item;
  tagMENUITEMINFOA local_38;
  
  if (DAT_004a29bc == 0) {
    local_38.cbSize = 0x30;
    local_38.fMask = 2;
    local_38.fType = 0;
    local_38.fState = 0;
    local_38.wID = 0;
    local_38.hSubMenu = (HMENU)0x0;
    local_38.hbmpChecked = (HBITMAP)0x0;
    local_38.hbmpUnchecked = (HBITMAP)0x0;
    local_38.dwItemData = 0;
    local_38.dwTypeData = (LPSTR)0x0;
    local_38.cch = 0;
    local_38.hbmpItem = (HBITMAP)0x0;
    GetMenuItemInfoA(DAT_004a2998,0,1,&local_38);
    DAT_004a29bc = local_38.wID;
  }
  uVar1 = FUN_0041d340(DAT_004a2998,DAT_004a29bc);
  iVar2 = GetMenuItemCount(DAT_004a2998);
  if (iVar2 == 0) {
    item = 0;
  }
  else {
    item = (iVar2 + (int)(param_1 + (uint)uVar1) % iVar2) % iVar2 & 0xffff;
  }
  local_38.cbSize = 0x30;
  local_38.fMask = 2;
  local_38.fType = 0;
  local_38.fState = 0;
  local_38.wID = 0;
  local_38.hSubMenu = (HMENU)0x0;
  local_38.hbmpChecked = (HBITMAP)0x0;
  local_38.hbmpUnchecked = (HBITMAP)0x0;
  local_38.dwItemData = 0;
  local_38.dwTypeData = (LPSTR)0x0;
  local_38.cch = 0;
  local_38.hbmpItem = (HBITMAP)0x0;
  GetMenuItemInfoA(DAT_004a2998,item,1,&local_38);
  DAT_004a29bc = local_38.wID;
  FUN_0041d510(DAT_004a2998,uVar1);
  FUN_0041d510(DAT_004a2998,(ushort)item);
  return;
}


