// FUN_00411fb0 @ 00411fb0 size=241 callers=1

undefined * FUN_00411fb0(void)

{
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aaaf;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_004365f0(&local_14);
  DAT_004a2900 = 0;
  DAT_004a2904 = 0;
  DAT_004a2908 = 0;
  local_8._0_1_ = 1;
  local_8._1_3_ = 0;
  FUN_004329e0((undefined4 *)&DAT_004a290c);
  local_8._0_1_ = 2;
  FUN_004329e0((undefined4 *)&DAT_004a292c);
  local_8._0_1_ = 3;
  FUN_004327c0((undefined4 *)&DAT_004a294c);
  local_8._0_1_ = 4;
  FUN_00432680((undefined4 *)&DAT_004a296c);
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_constructor_iterator_(&DAT_004a298c,4,2,FUN_00432c50,FUN_00422890);
  DAT_004a2994 = 0;
  DAT_004a299c = 0;
  DAT_004a29a0 = 0;
  DAT_004a29a4 = 0;
  DAT_004a29c4 = 0;
  ExceptionList = local_10;
  return &DAT_004a28e0;
}


