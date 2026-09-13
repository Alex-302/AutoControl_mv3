// FUN_004324a0 @ 004324a0 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004324a0(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a332c != (void *)0x0) {
    FUN_00402430(DAT_004a332c,DAT_004a3334 - (int)DAT_004a332c >> 2,4);
    DAT_004a332c = (void *)0x0;
    _DAT_004a3330 = 0;
    DAT_004a3334 = 0;
  }
  _Memory = (int *)*DAT_004a3324;
  *DAT_004a3324 = (int)DAT_004a3324;
  DAT_004a3324[1] = (int)DAT_004a3324;
  DAT_004a3328 = 0;
  if (_Memory != DAT_004a3324) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a3324);
  }
  FID_conflict__free(DAT_004a3324);
  return;
}


