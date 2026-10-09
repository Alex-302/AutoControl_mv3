// FUN_00406060 @ 00406060 size=342 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00406060(void)

{
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_00479554;
  local_10 = ExceptionList;
  ram0x004a25e0 = 0;
  DAT_004a25e4 = 0;
  DAT_004a25e8 = 0;
  DAT_004a25ec = 0;
  DAT_004a25f0 = 0;
  DAT_004a25f4 = 0;
  local_8 = 1;
  uStack_7 = 0;
  local_14 = 0;
  DAT_004a25f8 = 0;
  _DAT_004a25fc = 0;
  DAT_004a2600 = 0;
  ExceptionList = &local_10;
  FUN_0043ef20(&DAT_004a25f8,0,&local_14);
  _DAT_004a2604 = 0;
  DAT_004a2608 = 0;
  DAT_004a260c = 0;
  DAT_004a2610 = 0;
  DAT_004a2628 = 0xf;
  _DAT_004a2624 = 0;
  DAT_004a2614._0_1_ = 0;
  DAT_004a263c = 0;
  _DAT_004a264a = 0x5300;
  DAT_004a264c = 0;
  _local_8 = CONCAT31(uStack_7,4);
  _eh_vector_constructor_iterator_(&DAT_004a2650,0x18,4,FUN_00435660,FUN_004061c0);
  DAT_004a26b2 = 0;
  _DAT_004a26b8 = 0;
  _DAT_004a26c0 = 0;
  _DAT_004a26c5 = 0;
  DAT_004a26c7 = 0;
  ExceptionList = local_10;
  return 0x4a25e0;
}


