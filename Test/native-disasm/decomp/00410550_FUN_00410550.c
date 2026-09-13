// FUN_00410550 @ 00410550 size=257 callers=5

void * __fastcall FUN_00410550(void *param_1,int *param_2)

{
  char local_4c [8];
  undefined8 local_44;
  undefined1 local_3c [8];
  undefined8 local_34;
  char local_2c [16];
  char local_1c [4];
  void *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a677;
  local_10 = ExceptionList;
  local_14 = 0;
  local_4c[0] = '\0';
  local_44 = 0;
  DAT_0049fc30 = DAT_0049fc30 + (DAT_0049fc30 / 0x14) * -0x14 + 1;
  ExceptionList = &local_10;
  *param_2 = DAT_0049fc30;
  local_18 = param_1;
  FUN_00451110(local_4c,(uint *)"chunkedData");
  local_3c[0] = 0;
  local_34 = 0;
  FUN_00451040(local_3c,DAT_0049fc30);
  local_8 = 1;
  FUN_00434b50(local_2c,local_4c,local_2c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,3);
  _eh_vector_destructor_iterator_(local_4c,0x10,2,FUN_00434820);
  local_8 = 4;
  FUN_00434b50(param_1,local_2c,local_1c,'\x01','\x02');
  local_14 = 1;
  local_8 = local_8 & 0xffffff00;
  _eh_vector_destructor_iterator_(local_2c,0x10,1,FUN_00434820);
  ExceptionList = local_10;
  return param_1;
}


