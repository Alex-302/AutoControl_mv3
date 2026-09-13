// FUN_00418360 @ 00418360 size=291 callers=1

void __fastcall FUN_00418360(undefined4 *param_1)

{
  HWND hWndNewOwner;
  uint *puVar1;
  SIZE_T dwBytes;
  bool bVar2;
  BOOL BVar3;
  HGLOBAL hMem;
  UINT uFormat;
  HANDLE pvVar4;
  uint *hMem_00;
  int iVar5;
  uint *puVar6;
  bool bVar7;
  uint *local_c;
  
  iVar5 = 0;
  hWndNewOwner = *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4);
  do {
    BVar3 = OpenClipboard(hWndNewOwner);
    bVar7 = BVar3 != 0;
    if (bVar7) break;
    Sleep(10);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 5);
  EmptyClipboard();
  puVar1 = (uint *)param_1[1];
  puVar6 = (uint *)*param_1;
  do {
    if (puVar6 == puVar1) {
      if (bVar7) {
                    /* WARNING: Could not recover jumptable at 0x00418479. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        CloseClipboard();
        return;
      }
      return;
    }
    uFormat = puVar6[6];
    dwBytes = puVar6[4];
    local_c = puVar6;
    if (0xf < puVar6[5]) {
      local_c = (uint *)*puVar6;
    }
    hMem = GlobalAlloc(2,dwBytes);
    hMem_00 = (uint *)0x0;
    if (hMem != (HGLOBAL)0x0) {
      hMem_00 = GlobalLock(hMem);
    }
    bVar2 = false;
    if (hMem_00 != (uint *)0x0) {
      FUN_0045c870(hMem_00,local_c,dwBytes);
    }
    if (((bVar7) && (hMem != (HGLOBAL)0x0)) && (hMem_00 != (uint *)0x0)) {
      if (uFormat == 0x5b) {
        uFormat = DAT_004a26f4;
      }
      pvVar4 = SetClipboardData(uFormat,hMem);
      if (pvVar4 == (HANDLE)0x0) goto LAB_0041843e;
    }
    else {
LAB_0041843e:
      bVar2 = true;
    }
    if (hMem_00 != (uint *)0x0) {
      GlobalUnlock(hMem_00);
    }
    if ((hMem != (HGLOBAL)0x0) && (bVar2)) {
      GlobalFree(hMem);
    }
    puVar6 = puVar6 + 7;
  } while( true );
}


