// FUN_0041eb10 @ 0041eb10 size=93 callers=1

undefined4 __fastcall FUN_0041eb10(uint param_1,HMENU param_2)

{
  tagMENUITEMINFOA local_38;
  
  if (((param_1 >> 0x10 & 0x10) != 0) && ((char)(param_1 >> 0x10) < '\0')) {
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
    GetMenuItemInfoA(param_2,param_1 & 0xffff,1,&local_38);
    DAT_004a29c0 = local_38.wID;
    FUN_0041e810();
  }
  return 0;
}


