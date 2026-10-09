// FUN_00401130 @ 00401130 size=182 callers=1

void FUN_00401130(void)

{
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004794c4;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00442b40(&DAT_004a29f4);
  DAT_004a29f4 = 0;
  DAT_004a29f8 = 0;
  DAT_004a29f4 = FUN_00448fe0((undefined4 *)0x0,(undefined4 *)0x0);
  local_8 = 0;
  FUN_00442b40(&local_11);
  FUN_00442b40(&DAT_004a29fc);
  DAT_004a29fc = 0;
  DAT_004a2a00 = 0;
  DAT_004a2a04 = 0;
  local_8 = CONCAT31(local_8._1_3_,1);
  DAT_004a29f0 = 0x3f800000;
  FUN_00435e50(&DAT_004a29f0,8);
  _atexit(FUN_0047eee0);
  ExceptionList = local_10;
  return;
}


