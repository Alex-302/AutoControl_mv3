// FUN_00433130 @ 00433130 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00433130(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a280c != (void *)0x0) {
    FUN_00402430(DAT_004a280c,DAT_004a2814 - (int)DAT_004a280c >> 2,4);
    DAT_004a280c = (void *)0x0;
    _DAT_004a2810 = 0;
    DAT_004a2814 = 0;
  }
  _Memory = (int *)*DAT_004a2804;
  *DAT_004a2804 = (int)DAT_004a2804;
  DAT_004a2804[1] = (int)DAT_004a2804;
  DAT_004a2808 = 0;
  if (_Memory != DAT_004a2804) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a2804);
  }
  FID_conflict__free(DAT_004a2804);
  return;
}


