// FUN_0047ef60 @ 0047ef60 size=115 callers=1

void FUN_0047ef60(void)

{
  void *_Memory;
  
  if (DAT_004a2a1c != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a2a1c,DAT_004a2a24 - (int)DAT_004a2a1c >> 2,4);
    DAT_004a2a1c = (void *)0x0;
    DAT_004a2a20 = 0;
    DAT_004a2a24 = 0;
  }
  FUN_0043e550(&DAT_004a2a14);
  FUN_0043ba10();
  _Memory = (void *)FUN_0043ba10();
  FID_conflict__free(_Memory);
  return;
}


