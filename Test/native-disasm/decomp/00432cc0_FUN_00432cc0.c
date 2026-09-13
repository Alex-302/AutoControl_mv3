// FUN_00432cc0 @ 00432cc0 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00432cc0(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a2a6c != (void *)0x0) {
    FUN_00402430(DAT_004a2a6c,DAT_004a2a74 - (int)DAT_004a2a6c >> 2,4);
    DAT_004a2a6c = (void *)0x0;
    _DAT_004a2a70 = 0;
    DAT_004a2a74 = 0;
  }
  _Memory = (int *)*DAT_004a2a64;
  *DAT_004a2a64 = (int)DAT_004a2a64;
  DAT_004a2a64[1] = (int)DAT_004a2a64;
  DAT_004a2a68 = 0;
  if (_Memory != DAT_004a2a64) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a2a64);
  }
  FID_conflict__free(DAT_004a2a64);
  return;
}


