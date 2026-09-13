// FUN_00418e70 @ 00418e70 size=131 callers=1

void FUN_00418e70(char param_1)

{
  undefined4 *puVar1;
  
  if (9 < (uint)(DAT_004a25ac - DAT_004a25a8 >> 2)) {
    if ((DAT_004a25dc != '\0') || (DAT_004a25d4 == (HWND)0x0)) {
      DAT_004a25c4 = 0;
      puVar1 = &DAT_004a25b4;
      if (0xf < DAT_004a25c8) {
        puVar1 = DAT_004a25b4;
      }
      *(undefined1 *)puVar1 = 0;
      DestroyWindow(DAT_004a25d4);
      DAT_004a25d4 = (HWND)0x0;
      DAT_004a25dc = '\0';
    }
    if (DAT_004a25c4 < 0x19) {
      FUN_0043aef0(&DAT_004a25b4,1,param_1);
    }
    FUN_00418cc0();
  }
  return;
}


