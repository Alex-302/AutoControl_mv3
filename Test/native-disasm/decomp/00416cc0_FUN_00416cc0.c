// FUN_00416cc0 @ 00416cc0 size=159 callers=2

undefined1 __thiscall
FUN_00416cc0(void *this,UINT param_1,uint *param_2,SIZE_T param_3,char param_4)

{
  bool bVar1;
  HGLOBAL hMem;
  HANDLE pvVar2;
  undefined1 uVar3;
  uint *hMem_00;
  
  hMem = GlobalAlloc(2,param_3);
  hMem_00 = (uint *)0x0;
  if (hMem != (HGLOBAL)0x0) {
    hMem_00 = GlobalLock(hMem);
  }
  if (hMem_00 != (uint *)0x0) {
    FUN_0045c870(hMem_00,param_2,param_3);
  }
  if (((*(char *)this != '\0') && (hMem != (HGLOBAL)0x0)) && (hMem_00 != (uint *)0x0)) {
    if (param_4 == '\0') {
      EmptyClipboard();
    }
    if (param_1 == 0x5b) {
      param_1 = DAT_004a26f4;
    }
    pvVar2 = SetClipboardData(param_1,hMem);
    if (pvVar2 != (HANDLE)0x0) {
      uVar3 = 1;
      bVar1 = false;
      goto LAB_00416d3c;
    }
  }
  uVar3 = 0;
  bVar1 = true;
LAB_00416d3c:
  if (hMem_00 != (uint *)0x0) {
    GlobalUnlock(hMem_00);
  }
  if ((hMem != (HGLOBAL)0x0) && (bVar1)) {
    GlobalFree(hMem);
  }
  return uVar3;
}


