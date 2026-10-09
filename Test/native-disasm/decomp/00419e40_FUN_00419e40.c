// FUN_00419e40 @ 00419e40 size=367 callers=2

undefined4 * __fastcall FUN_00419e40(undefined4 *param_1,uint param_2)

{
  char cVar1;
  undefined *puVar2;
  undefined1 auStack_8c [8];
  undefined4 uStack_84;
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [16];
  char local_34 [24];
  undefined1 *local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b5e4;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  local_14 = param_1;
  puVar2 = FUN_00419890(param_2);
  cVar1 = puVar2[0x24];
  if (((cVar1 == ')') || (cVar1 == ',')) || (cVar1 == '.')) {
    local_64[0] = '\0';
    local_5c = 0;
    FUN_00451110(local_64,(uint *)"itemId");
    local_54[0] = 0;
    local_4c = 0;
    FUN_00451040(local_54,param_2);
    local_8 = 0;
    FUN_00434b50(local_44,local_64,local_44,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,2);
    _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
    local_1c = &stack0xffffff84;
    local_8._0_1_ = 4;
    local_8._1_3_ = 0;
    uStack_84 = 0x419f05;
    FUN_004381d0(&stack0xffffff8c,'\0');
    local_8._0_1_ = 5;
    FUN_00434b50(auStack_8c,local_44,local_34,'\x01','\x02');
    local_8._0_1_ = 3;
    FUN_00408a00(local_34,0x30d);
    local_8 = CONCAT31(local_8._1_3_,7);
    _eh_vector_destructor_iterator_(local_44,0x10,1,FUN_00434820);
    if (local_34[0] == '\x03') {
      FUN_00440d90(local_34,param_1);
      FUN_00434820(local_34);
      ExceptionList = local_10;
      return param_1;
    }
    local_8 = 0xffffffff;
    FUN_00434820(local_34);
  }
  param_1[5] = 0xf;
  param_1[4] = 0;
  *(undefined1 *)param_1 = 0;
  FUN_0043ace0(param_1,(uint *)&DAT_0048e75c,0);
  ExceptionList = local_10;
  return param_1;
}


