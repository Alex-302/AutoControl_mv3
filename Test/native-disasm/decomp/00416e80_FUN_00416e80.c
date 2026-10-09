// FUN_00416e80 @ 00416e80 size=348 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * FUN_00416e80(void)

{
  HWND hWndNewOwner;
  BOOL BVar1;
  UINT UVar2;
  undefined4 *this;
  int iVar3;
  bool bVar4;
  HGLOBAL local_2c;
  HGLOBAL local_28;
  char local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  int local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b000;
  local_10 = ExceptionList;
  local_18 = *(int *)ThreadLocalStoragePointer;
  iVar3 = 0;
  local_20 = 0;
  hWndNewOwner = *(HWND *)(&DAT_004a2470 + *(int *)(local_18 + 4) * 4);
  ExceptionList = &local_10;
  do {
    BVar1 = OpenClipboard(hWndNewOwner);
    bVar4 = BVar1 != 0;
    local_11 = bVar4;
    if (bVar4) break;
    Sleep(10);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 5);
  local_8 = 0;
  if ((*(int *)(local_18 + 8) < DAT_004a2e94) && (FUN_0045a219(&DAT_004a2e94), DAT_004a2e94 == -1))
  {
    _DAT_0049d9d0 = DAT_004a26f4;
    _DAT_0049d9d4 = 0xf;
    _DAT_0049d9d8 = 0xd;
    _DAT_0049d9dc = 1;
    FUN_0045a1da(&DAT_004a2e94);
  }
  iVar3 = 5;
  if (DAT_004a26f4 == 0) {
    iVar3 = 1;
  }
  UVar2 = GetPriorityClipboardFormat((UINT *)(&DAT_0049d9cc + (uint)(DAT_004a26f4 == 0) * 4),iVar3);
  if ((int)UVar2 < 1) {
    UVar2 = 0;
  }
  else if (UVar2 == DAT_004a26f4) {
    UVar2 = 0x5b;
  }
  this = FUN_00416c20(&local_11,&local_2c,UVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00416ae0(this,local_1c);
  if (local_28 != (HGLOBAL)0x0) {
    GlobalUnlock(local_28);
  }
  if ((local_2c != (HGLOBAL)0x0) && (local_24 != '\0')) {
    GlobalFree(local_2c);
  }
  *(UINT *)(local_1c + 0x18) = UVar2;
  if (bVar4) {
    CloseClipboard();
  }
  ExceptionList = local_10;
  return local_1c;
}


