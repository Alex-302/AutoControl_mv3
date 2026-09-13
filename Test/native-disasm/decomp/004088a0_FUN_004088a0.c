// FUN_004088a0 @ 004088a0 size=349 callers=2

void __thiscall
FUN_004088a0(char param_1,char param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  char local_8c [16];
  undefined1 local_7c [16];
  char local_6c [8];
  undefined8 local_64;
  char local_5c;
  undefined4 local_54;
  undefined4 local_50;
  char local_4c [8];
  undefined8 local_44;
  undefined1 local_3c [8];
  undefined8 local_34;
  char local_2c [16];
  undefined8 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0047999f;
  local_10 = ExceptionList;
  local_8 = 0;
  local_4c[0] = '\0';
  local_44 = 0;
  ExceptionList = &local_10;
  FUN_00451110(local_4c,(uint *)"actionType");
  local_3c[0] = 0;
  local_34 = 0;
  FUN_004511e0(local_3c,param_1);
  local_8._0_1_ = 1;
  FUN_00434b50(local_8c,local_4c,local_2c,'\x01','\x02');
  local_8._0_1_ = 3;
  _eh_vector_destructor_iterator_(local_4c,0x10,2,FUN_00434820);
  local_6c[0] = '\0';
  local_64 = 0;
  FUN_00451110(local_6c,(uint *)"actionSpec");
  local_5c = param_2;
  local_54 = param_4;
  local_50 = param_5;
  local_1c = 0;
  param_4 = 0;
  param_2 = '\0';
  param_5 = 0;
  local_8._0_1_ = 4;
  FUN_00434b50(local_7c,local_6c,local_4c,'\x01','\x02');
  local_8._0_1_ = 6;
  _eh_vector_destructor_iterator_(local_6c,0x10,2,FUN_00434820);
  local_8._0_1_ = 7;
  FUN_00434b50(local_2c,local_8c,local_6c,'\x01','\x02');
  local_8._0_1_ = 8;
  FUN_00408600(0x2f8,local_2c);
  FUN_00434820(local_2c);
  local_8 = (uint)local_8._1_3_ << 8;
  _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
  FUN_00434820(&param_2);
  ExceptionList = local_10;
  return;
}


