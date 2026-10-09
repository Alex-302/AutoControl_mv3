// FUN_00432980 @ 00432980 size=85 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00432980(void)

{
  if (DAT_004a28ec != (void *)0x0) {
    FUN_00402430(DAT_004a28ec,DAT_004a28f4 - (int)DAT_004a28ec >> 2,4);
    DAT_004a28ec = (void *)0x0;
    _DAT_004a28f0 = 0;
    DAT_004a28f4 = 0;
  }
  FUN_00436540((int *)&DAT_004a28e4);
  FID_conflict__free(DAT_004a28e4);
  return;
}


