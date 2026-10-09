// FUN_00432c60 @ 00432c60 size=85 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00432c60(void)

{
  if (DAT_004a2f9c != (void *)0x0) {
    FUN_00402430(DAT_004a2f9c,DAT_004a2fa4 - (int)DAT_004a2f9c >> 2,4);
    DAT_004a2f9c = (void *)0x0;
    _DAT_004a2fa0 = 0;
    DAT_004a2fa4 = 0;
  }
  FUN_0043e700((int *)&DAT_004a2f94);
  FID_conflict__free(DAT_004a2f94);
  return;
}


