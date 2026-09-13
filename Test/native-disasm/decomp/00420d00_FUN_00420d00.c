// FUN_00420d00 @ 00420d00 size=201 callers=1

void FUN_00420d00(void)

{
  undefined4 *puVar1;
  undefined **local_48;
  ulonglong local_44;
  undefined4 local_3c;
  undefined ***local_24;
  uint local_20;
  undefined4 uStack_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b1a8;
  local_10 = ExceptionList;
  DAT_004a25c4 = 0;
  puVar1 = &DAT_004a25b4;
  if (0xf < DAT_004a25c8) {
    puVar1 = DAT_004a25b4;
  }
  ExceptionList = &local_10;
  *(undefined1 *)puVar1 = 0;
  DestroyWindow(DAT_004a25d4);
  DAT_004a25d4 = (HWND)0x0;
  DAT_004a25dc = 0x46;
  FUN_00418cc0();
  local_20 = (uint)DAT_004a25d4;
  local_14 = 0x1ff0000;
  uStack_1c = 0;
  local_44 = ZEXT48(DAT_004a25d4);
  local_3c = 0x1ff0000;
  local_24 = &local_48;
  local_48 = &PTR_LAB_0048e7f0;
  local_8 = 0;
  FUN_0040fca0(0x28,(int *)local_24);
  if (local_24 != (undefined ***)0x0) {
    (*(code *)(*local_24)[4])(local_24 != &local_48);
  }
  ExceptionList = local_10;
  return;
}


