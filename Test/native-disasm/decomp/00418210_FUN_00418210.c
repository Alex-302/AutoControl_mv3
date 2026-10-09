// FUN_00418210 @ 00418210 size=323 callers=1

undefined4 * __fastcall FUN_00418210(undefined4 *param_1)

{
  HWND hWndNewOwner;
  undefined4 *this;
  BOOL BVar1;
  UINT format;
  undefined4 *this_00;
  int iVar2;
  bool bVar3;
  uint local_44 [6];
  UINT local_2c;
  HGLOBAL local_28;
  HGLOBAL local_24;
  char local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b221;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  iVar2 = 0;
  local_18 = 1;
  hWndNewOwner = *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4);
  local_1c = param_1;
  do {
    BVar1 = OpenClipboard(hWndNewOwner);
    bVar3 = BVar1 != 0;
    local_11 = bVar3;
    if (bVar3) break;
    Sleep(10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 5);
  local_8 = 1;
  format = EnumClipboardFormats(0);
  this = local_1c;
  for (; format != 0; format = EnumClipboardFormats(format)) {
    if ((((format != 2) && (format != 0xe)) && (format != 1)) && ((format != 7 && (format != 8)))) {
      this_00 = FUN_00416c20(&local_11,&local_28,format);
      local_8 = CONCAT31(local_8._1_3_,2);
      FUN_00416ae0(this_00,(undefined1 *)local_44);
      if (local_24 != (HGLOBAL)0x0) {
        GlobalUnlock(local_24);
      }
      if ((local_28 != (HGLOBAL)0x0) && (local_20 != '\0')) {
        GlobalFree(local_28);
      }
      local_8._0_1_ = 3;
      local_2c = format;
      FUN_004322c0(this,local_44);
      local_8 = CONCAT31(local_8._1_3_,1);
      FUN_004061c0(local_44);
    }
  }
  if (bVar3) {
    CloseClipboard();
  }
  ExceptionList = local_10;
  return this;
}


