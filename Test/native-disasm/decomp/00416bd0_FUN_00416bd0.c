// FUN_00416bd0 @ 00416bd0 size=58 callers=1

void * __thiscall FUN_00416bd0(void *this,HWND param_1)

{
  BOOL BVar1;
  int iVar2;
  
  iVar2 = 0;
  *(undefined1 *)this = 0;
  do {
    BVar1 = OpenClipboard(param_1);
    *(bool *)this = BVar1 != 0;
    if (BVar1 != 0) {
      return this;
    }
    Sleep(10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 5);
  return this;
}


