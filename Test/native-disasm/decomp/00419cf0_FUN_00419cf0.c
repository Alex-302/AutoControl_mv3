// FUN_00419cf0 @ 00419cf0 size=321 callers=2

void __fastcall FUN_00419cf0(undefined4 param_1,undefined1 param_2)

{
  undefined4 extraout_EDX;
  char local_84 [16];
  undefined1 local_74 [16];
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [8];
  undefined8 local_3c;
  undefined1 local_34 [8];
  undefined8 local_2c;
  char local_24 [20];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b591;
  local_10 = ExceptionList;
  local_44[0] = '\0';
  local_3c = 0;
  DAT_004a29c4 = param_1;
  ExceptionList = &local_10;
  FUN_00451110(local_44,(uint *)"itemId");
  local_34[0] = 0;
  local_2c = 0;
  FUN_00451040(local_34,param_1);
  local_8 = 0;
  FUN_00434b50(local_84,local_44,local_24,'\x01','\x02');
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_44,0x10,2,FUN_00434820);
  local_64[0] = '\0';
  local_5c = 0;
  FUN_00451110(local_64,(uint *)"selMode");
  local_54[0] = 0;
  local_4c = 0;
  FUN_00451320(local_54,CONCAT31((int3)((uint)extraout_EDX >> 8),param_2));
  local_8._0_1_ = 3;
  FUN_00434b50(local_74,local_64,local_44,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
  local_8 = 6;
  FUN_00434b50(local_24,local_84,local_64,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,7);
  FUN_00408600(0x302,local_24);
  FUN_00434820(local_24);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_84,0x10,2,FUN_00434820);
  ExceptionList = local_10;
  return;
}


