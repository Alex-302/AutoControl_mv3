// FUN_00433270 @ 00433270 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00433270(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a27dc != (void *)0x0) {
    FUN_00402430(DAT_004a27dc,DAT_004a27e4 - (int)DAT_004a27dc >> 2,4);
    DAT_004a27dc = (void *)0x0;
    _DAT_004a27e0 = 0;
    DAT_004a27e4 = 0;
  }
  _Memory = (int *)*DAT_004a27d4;
  *DAT_004a27d4 = (int)DAT_004a27d4;
  DAT_004a27d4[1] = (int)DAT_004a27d4;
  DAT_004a27d8 = 0;
  if (_Memory != DAT_004a27d4) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a27d4);
  }
  FID_conflict__free(DAT_004a27d4);
  return;
}


