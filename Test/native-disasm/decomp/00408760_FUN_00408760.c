// FUN_00408760 @ 00408760 size=312 callers=6

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00408760(int param_1,undefined1 *param_2)

{
  char local_84 [16];
  undefined1 local_74 [16];
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [16];
  char local_44 [8];
  undefined8 local_3c;
  undefined1 local_34 [8];
  undefined8 local_2c;
  char local_24 [20];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479929;
  local_10 = ExceptionList;
  local_44[0] = '\0';
  local_3c = 0;
  ExceptionList = &local_10;
  FUN_00451110(local_44,(uint *)&DAT_0048cf30);
  local_34[0] = 0;
  local_2c = 0;
  FUN_00451040(local_34,param_1 - _DAT_004a23f0);
  local_8 = 0;
  FUN_00434b50(local_84,local_44,local_24,'\x01','\x02');
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_44,0x10,2,FUN_00434820);
  local_64[0] = '\0';
  local_5c = 0;
  FUN_00451110(local_64,(uint *)"params");
  local_8._0_1_ = 3;
  FUN_00434940(local_54,param_2);
  local_8._0_1_ = 4;
  FUN_00434b50(local_74,local_64,local_44,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,6);
  _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
  local_8 = 7;
  FUN_00434b50(local_24,local_84,local_64,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,8);
  FUN_00408600(0x2c6,local_24);
  FUN_00434820(local_24);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_84,0x10,2,FUN_00434820);
  ExceptionList = local_10;
  return;
}


