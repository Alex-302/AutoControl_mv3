// FUN_00406200 @ 00406200 size=366 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406200(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  _eh_vector_destructor_iterator_(&DAT_004a2650,0x18,4,FUN_004061c0);
  if (0xf < DAT_004a2628) {
    FUN_00402430(DAT_004a2614,DAT_004a2628 + 1,1);
  }
  DAT_004a2628 = 0xf;
  _DAT_004a2624 = 0;
  DAT_004a2614 = (void *)((uint)DAT_004a2614 & 0xffffff00);
  if (DAT_004a2608 != (void *)0x0) {
    FUN_00402430(DAT_004a2608,DAT_004a2610 - (int)DAT_004a2608 >> 2,4);
    DAT_004a2608 = (void *)0x0;
    DAT_004a260c = 0;
    DAT_004a2610 = 0;
  }
  if (DAT_004a25f8 != (void *)0x0) {
    FUN_00402430(DAT_004a25f8,DAT_004a2600 - (int)DAT_004a25f8 >> 2,4);
    DAT_004a25f8 = (void *)0x0;
    _DAT_004a25fc = 0;
    DAT_004a2600 = 0;
  }
  if (DAT_004a25ec != (void *)0x0) {
    FUN_00402430(DAT_004a25ec,DAT_004a25f4 - (int)DAT_004a25ec >> 1,2);
    DAT_004a25ec = (void *)0x0;
    DAT_004a25f0 = 0;
    DAT_004a25f4 = 0;
  }
  if (ram0x004a25e0 != (void *)0x0) {
    FUN_00402430(ram0x004a25e0,DAT_004a25e8 - (int)ram0x004a25e0 >> 2,4);
    ram0x004a25e0 = (void *)0x0;
    DAT_004a25e4 = 0;
    DAT_004a25e8 = 0;
  }
  ExceptionList = local_10;
  return;
}


