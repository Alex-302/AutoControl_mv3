// FUN_0047eee0 @ 0047eee0 size=115 callers=1

void FUN_0047eee0(void)

{
  void *_Memory;
  
  if (DAT_004a29fc != (void *)0x0) {
    guard_check_icall();
    FUN_00435da0();
    FUN_00402430(DAT_004a29fc,DAT_004a2a04 - (int)DAT_004a29fc >> 2,4);
    DAT_004a29fc = (void *)0x0;
    DAT_004a2a00 = 0;
    DAT_004a2a04 = 0;
  }
  FUN_0043edd0(&DAT_004a29f4);
  FUN_0043ba10();
  _Memory = (void *)FUN_0043ba10();
  FID_conflict__free(_Memory);
  return;
}


