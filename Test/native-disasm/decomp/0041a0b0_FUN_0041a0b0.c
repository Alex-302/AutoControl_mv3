// FUN_0041a0b0 @ 0041a0b0 size=301 callers=3

void FUN_0041a0b0(void)

{
  char local_5c [8];
  undefined8 local_54;
  undefined1 local_4c;
  undefined4 local_44;
  undefined4 uStack_40;
  char local_3c [16];
  char local_2c [16];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b62c;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00436540(&DAT_004a28e4);
  FUN_00435e50(&DAT_004a28e0,8);
  local_8 = 0xffffffff;
  FUN_004479e0(DAT_004a2900,DAT_004a2904);
  DAT_004a2904 = DAT_004a2900;
  local_5c[0] = '\0';
  local_54 = 0;
  FUN_00451110(local_5c,(uint *)"click");
  local_1c = CONCAT31(local_1c._1_3_,DAT_004a2445);
  local_4c = 4;
  _local_44 = CONCAT44(local_18,local_1c);
  local_8 = 1;
  FUN_00434b50(local_2c,local_5c,local_3c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,3);
  _eh_vector_destructor_iterator_(local_5c,0x10,2,FUN_00434820);
  local_8 = 4;
  FUN_00434b50(local_3c,local_2c,(char *)&local_1c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,5);
  FUN_00408600(0x316,local_3c);
  FUN_00434820(local_3c);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_2c,0x10,1,FUN_00434820);
  DAT_004a2445 = 0;
  ExceptionList = local_10;
  return;
}


