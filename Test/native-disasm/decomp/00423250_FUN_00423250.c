// FUN_00423250 @ 00423250 size=381 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00423250(int param_1,char param_2)

{
  undefined1 uVar1;
  char local_8c [16];
  undefined1 local_7c [16];
  char local_6c [8];
  undefined8 local_64;
  undefined1 local_5c [8];
  undefined8 local_54;
  char local_4c [8];
  undefined8 local_44;
  undefined1 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  char local_2c [16];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047be77;
  local_10 = ExceptionList;
  if ((DAT_004a2388 == '\0') && (param_2 != '\0')) {
    DAT_004a2388 = '\x01';
  }
  local_6c[0] = '\0';
  local_64 = 0;
  ExceptionList = &local_10;
  FUN_00451110(local_6c,(uint *)&DAT_0048d7f8);
  local_5c[0] = 0;
  local_54 = 0;
  FUN_00451040(local_5c,param_1 - _DAT_004a23bc);
  local_8 = 0;
  FUN_00434b50(local_8c,local_6c,local_4c,'\x01','\x02');
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_6c,0x10,2,FUN_00434820);
  local_4c[0] = '\0';
  local_44 = 0;
  FUN_00451110(local_4c,(uint *)"noEvt");
  if ((DAT_004a2388 == '\0') && (param_2 == '\0')) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  local_1c = CONCAT31(local_1c._1_3_,uVar1);
  local_3c = 4;
  _local_34 = CONCAT44(local_18,local_1c);
  local_8._0_1_ = 3;
  FUN_00434b50(local_7c,local_4c,local_2c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_destructor_iterator_(local_4c,0x10,2,FUN_00434820);
  local_8 = 6;
  FUN_00434b50(local_2c,local_8c,local_6c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,7);
  FUN_00408600(0x2d1,local_2c);
  FUN_00434820(local_2c);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
  ExceptionList = local_10;
  return;
}


