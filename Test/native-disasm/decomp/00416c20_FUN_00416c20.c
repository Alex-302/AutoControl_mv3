// FUN_00416c20 @ 00416c20 size=68 callers=4

undefined4 * __thiscall FUN_00416c20(void *this,undefined4 *param_1,UINT param_2)

{
  HGLOBAL hMem;
  LPVOID pvVar1;
  
  if (*(char *)this == '\0') {
    hMem = (HGLOBAL)0x0;
  }
  else {
    if (param_2 == 0x5b) {
      param_2 = DAT_004a26f4;
    }
    hMem = GetClipboardData(param_2);
  }
  param_1[1] = 0;
  *param_1 = hMem;
  if (hMem != (HGLOBAL)0x0) {
    pvVar1 = GlobalLock(hMem);
    param_1[1] = pvVar1;
  }
  *(undefined1 *)(param_1 + 2) = 0;
  return param_1;
}


