// FUN_0041d600 @ 0041d600 size=145 callers=2

undefined4 __fastcall FUN_0041d600(HMENU param_1,UINT param_2)

{
  ushort uVar1;
  BOOL BVar2;
  undefined *puVar3;
  undefined4 uVar4;
  MENUITEMINFOA local_38;
  
  local_38.cbSize = 0x30;
  local_38.fMask = 2;
  local_38.fType = 0;
  local_38.fState = 0;
  local_38.wID = 0xfffffffd;
  local_38.hSubMenu = (HMENU)0x0;
  local_38.hbmpChecked = (HBITMAP)0x0;
  local_38.hbmpUnchecked = (HBITMAP)0x0;
  local_38.dwItemData = 0;
  local_38.hbmpItem = (HBITMAP)0x0;
  local_38.dwTypeData = (LPSTR)0x0;
  local_38.cch = 0;
  BVar2 = SetMenuItemInfoA(param_1,param_2,0,&local_38);
  if (BVar2 != 0) {
    if (param_1 == (HMENU)0x0) {
      puVar3 = FUN_00419890(0xfffffffd);
      param_1 = *(HMENU *)(puVar3 + 0x1c);
    }
    uVar1 = FUN_0041d340(param_1,0xfffffffd);
    uVar4 = FUN_0041d510(param_1,uVar1);
    return CONCAT31((int3)((uint)uVar4 >> 8),1);
  }
  return 0;
}


