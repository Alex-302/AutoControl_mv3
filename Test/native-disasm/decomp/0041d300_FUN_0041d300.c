// FUN_0041d300 @ 0041d300 size=62 callers=1

UINT __fastcall FUN_0041d300(HMENU param_1,ushort param_2)

{
  tagMENUITEMINFOA local_34;
  
  local_34.cbSize = 0x30;
  local_34.fMask = 2;
  local_34.fType = 0;
  local_34.fState = 0;
  local_34.wID = 0;
  local_34.hSubMenu = (HMENU)0x0;
  local_34.hbmpChecked = (HBITMAP)0x0;
  local_34.hbmpUnchecked = (HBITMAP)0x0;
  local_34.dwItemData = 0;
  local_34.dwTypeData = (LPSTR)0x0;
  local_34.cch = 0;
  local_34.hbmpItem = (HBITMAP)0x0;
  GetMenuItemInfoA(param_1,(uint)param_2,1,&local_34);
  return local_34.wID;
}


