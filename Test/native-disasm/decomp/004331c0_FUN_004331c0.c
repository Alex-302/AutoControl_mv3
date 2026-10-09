// FUN_004331c0 @ 004331c0 size=130 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004331c0(void)

{
  int *piVar1;
  int *_Memory;
  
  if (DAT_004a256c != (void *)0x0) {
    FUN_00402430(DAT_004a256c,_DAT_004a2574 - (int)DAT_004a256c >> 2,4);
    DAT_004a256c = (void *)0x0;
    _DAT_004a2570 = 0;
    _DAT_004a2574 = 0;
  }
  _Memory = (int *)*DAT_004a2564;
  *DAT_004a2564 = (int)DAT_004a2564;
  DAT_004a2564[1] = (int)DAT_004a2564;
  _DAT_004a2568 = 0;
  if (_Memory != DAT_004a2564) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a2564);
  }
  FID_conflict__free(DAT_004a2564);
  return;
}


