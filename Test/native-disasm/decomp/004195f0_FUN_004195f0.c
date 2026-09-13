// FUN_004195f0 @ 004195f0 size=670 callers=4

bool __thiscall FUN_004195f0(void *this,char param_1,uint param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar4;
  undefined4 uVar5;
  code *pcVar6;
  char local_104 [16];
  undefined1 local_f4 [16];
  undefined1 local_e4 [16];
  undefined1 local_d4 [16];
  undefined1 local_c4 [16];
  char local_b4 [8];
  undefined8 local_ac;
  undefined1 local_a4 [8];
  undefined8 local_9c;
  char local_94 [8];
  undefined8 local_8c;
  undefined1 local_84 [8];
  undefined8 local_7c;
  char local_74 [8];
  undefined8 local_6c;
  undefined1 local_64 [8];
  undefined8 local_5c;
  char local_54 [8];
  undefined8 local_4c;
  undefined1 local_44 [8];
  undefined8 local_3c;
  char local_34 [8];
  undefined8 local_2c;
  undefined1 local_24 [8];
  undefined8 local_1c;
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  char *pcVar3;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b402;
  local_10 = ExceptionList;
  bVar1 = *(char *)((int)this + 0x38) == '\0';
  if (!bVar1) {
    local_34[0] = '\0';
    local_2c = 0;
    ExceptionList = &local_10;
    FUN_00451110(local_34,(uint *)&DAT_0048d65c);
    local_24[0] = 0;
    local_1c = 0;
    FUN_00450f50(local_24,*(int *)((int)this + 0x20));
    local_8 = 0;
    FUN_00434b50(local_104,local_34,local_14,'\x01','\x02');
    local_8._0_1_ = 2;
    _eh_vector_destructor_iterator_(local_34,0x10,2,FUN_00434820);
    local_54[0] = '\0';
    local_4c = 0;
    FUN_00451110(local_54,(uint *)&DAT_0048d660);
    local_44[0] = 0;
    local_3c = 0;
    FUN_00450f50(local_44,*(int *)((int)this + 0x24));
    local_8._0_1_ = 3;
    FUN_00434b50(local_f4,local_54,local_34,'\x01','\x02');
    local_8._0_1_ = 5;
    _eh_vector_destructor_iterator_(local_54,0x10,2,FUN_00434820);
    local_74[0] = '\0';
    local_6c = 0;
    FUN_00451110(local_74,(uint *)"state");
    local_64[0] = 0;
    local_5c = 0;
    FUN_004511e0(local_64,*(char *)((int)this + 0x37));
    local_8._0_1_ = 6;
    FUN_00434b50(local_e4,local_74,local_54,'\x01','\x02');
    local_8._0_1_ = 8;
    _eh_vector_destructor_iterator_(local_74,0x10,2,FUN_00434820);
    local_94[0] = '\0';
    local_8c = 0;
    FUN_00451110(local_94,(uint *)&DAT_0048d07c);
    local_84[0] = 0;
    local_7c = 0;
    FUN_004511e0(local_84,param_1);
    local_8._0_1_ = 9;
    FUN_00434b50(local_d4,local_94,local_74,'\x01','\x02');
    local_8._0_1_ = 0xb;
    _eh_vector_destructor_iterator_(local_94,0x10,2,FUN_00434820);
    local_b4[0] = '\0';
    local_ac = 0;
    FUN_00451110(local_b4,(uint *)&DAT_0048d66c);
    local_a4[0] = 0;
    local_9c = 0;
    FUN_004512e0(local_a4,param_2);
    local_8._0_1_ = 0xc;
    FUN_00434b50(local_c4,local_b4,local_94,'\x01','\x02');
    pcVar6 = FUN_00434820;
    uVar5 = 2;
    uVar4 = 0x10;
    pcVar3 = local_b4;
    local_8 = CONCAT31(local_8._1_3_,0xe);
    _eh_vector_destructor_iterator_(pcVar3,0x10,2,FUN_00434820);
    cVar2 = (char)pcVar3;
    local_8 = 0xf;
    FUN_00434b50(&stack0xfffffee4,local_104,local_b4,'\x01','\x02');
    FUN_004088a0('G',cVar2,uVar4,uVar5,pcVar6);
    local_8 = 0xffffffff;
    _eh_vector_destructor_iterator_(local_104,0x10,5,FUN_00434820);
    bVar1 = *(char *)((int)this + 0x38) == '\0';
  }
  ExceptionList = local_10;
  return !bVar1;
}


