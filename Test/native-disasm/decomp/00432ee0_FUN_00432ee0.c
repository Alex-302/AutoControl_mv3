// FUN_00432ee0 @ 00432ee0 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00432ee0(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a27bc != (void *)0x0) {
    FUN_00402430(DAT_004a27bc,DAT_004a27c4 - (int)DAT_004a27bc >> 2,4);
    DAT_004a27bc = (void *)0x0;
    _DAT_004a27c0 = 0;
    DAT_004a27c4 = 0;
  }
  _Memory = (int *)*DAT_004a27b4;
  *DAT_004a27b4 = (int)DAT_004a27b4;
  DAT_004a27b4[1] = (int)DAT_004a27b4;
  DAT_004a27b8 = 0;
  if (_Memory != DAT_004a27b4) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a27b4);
  }
  FID_conflict__free(DAT_004a27b4);
  return;
}


