// FUN_0041d340 @ 0041d340 size=124 callers=6

ushort __fastcall FUN_0041d340(HMENU param_1,UINT param_2)

{
  int iVar1;
  UINT item;
  ushort uVar2;
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
  iVar1 = GetMenuItemCount(param_1);
  uVar2 = 0;
  if (0 < iVar1) {
    item = 0;
    do {
      GetMenuItemInfoA(param_1,item,1,&local_34);
      if (local_34.wID == param_2) {
        return uVar2;
      }
      uVar2 = uVar2 + 1;
      item = (UINT)uVar2;
    } while ((int)item < iVar1);
  }
  return 0xffff;
}


