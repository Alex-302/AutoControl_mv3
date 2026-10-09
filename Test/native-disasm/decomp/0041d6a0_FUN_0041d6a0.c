// FUN_0041d6a0 @ 0041d6a0 size=173 callers=2

void * __thiscall FUN_0041d6a0(void *this,HMENU param_1,ushort param_2)

{
  undefined *puVar1;
  tagMENUITEMINFOA local_38;
  
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
  GetMenuItemInfoA(param_1,(uint)param_2,1,&local_38);
  *(UINT *)this = local_38.wID;
  local_38.cbSize = 0x1c;
  local_38.fMask = 8;
  local_38.fType = 0;
  local_38.fState = 0;
  local_38.wID = 0;
  local_38.hSubMenu = (HMENU)0x0;
  local_38.hbmpChecked = (HBITMAP)0x0;
  GetMenuInfo(param_1,(LPMENUINFO)&local_38);
  *(HBITMAP *)((int)this + 4) = local_38.hbmpChecked;
  *(HMENU *)((int)this + 8) = param_1;
  *(ushort *)((int)this + 0xc) = param_2;
  *(undefined4 *)((int)this + 0xe) = 0;
  if (*(uint *)this != 0) {
    puVar1 = FUN_00419890(*(uint *)this);
    *(undefined *)((int)this + 0xe) = puVar1[0x24];
  }
  return this;
}


