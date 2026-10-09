// FUN_00433aa0 @ 00433aa0 size=130 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00433aa0(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a282c != (void *)0x0) {
    FUN_00402430(DAT_004a282c,DAT_004a2834 - (int)DAT_004a282c >> 2,4);
    DAT_004a282c = (void *)0x0;
    _DAT_004a2830 = 0;
    DAT_004a2834 = 0;
  }
  _Memory = (int *)*DAT_004a2824;
  *DAT_004a2824 = (int)DAT_004a2824;
  DAT_004a2824[1] = (int)DAT_004a2824;
  DAT_004a2828 = 0;
  if (_Memory != DAT_004a2824) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a2824);
  }
  FID_conflict__free(DAT_004a2824);
  return;
}


