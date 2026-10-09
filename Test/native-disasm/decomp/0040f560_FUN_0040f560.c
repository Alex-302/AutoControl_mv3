// FUN_0040f560 @ 0040f560 size=332 callers=3

void FUN_0040f560(void)

{
  undefined4 uVar1;
  int *piVar2;
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [16];
  char local_34 [16];
  char local_24 [4];
  int *local_20;
  int local_1c;
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a526;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0040f4b0(&local_20);
  piVar2 = local_20;
  local_8 = 0;
  if (local_1c - (int)local_20 >> 2 == DAT_004a2518 - (int)DAT_004a2514 >> 2) {
    local_14 = local_14 & 0xffffff00;
    uVar1 = FUN_004569a0(local_20,local_1c,DAT_004a2514);
    if ((char)uVar1 != '\0') goto LAB_0040f685;
  }
  FUN_00433300(&local_20);
  local_64[0] = '\0';
  local_5c = 0;
  FUN_00451110(local_64,(uint *)&DAT_0048cf28);
  local_8._0_1_ = 1;
  local_54[0] = 0;
  local_4c = 0;
  FUN_0044dd50(local_54,&DAT_004a2514);
  local_8._0_1_ = 2;
  FUN_00434b50(local_34,local_64,local_44,'\x01','\x02');
  local_8._0_1_ = 4;
  _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
  local_8._0_1_ = 5;
  FUN_00434b50(local_44,local_34,local_24,'\x01','\x02');
  local_8._0_1_ = 6;
  FUN_00408600(0x2da,local_44);
  FUN_00434820(local_44);
  local_8 = (uint)local_8._1_3_ << 8;
  _eh_vector_destructor_iterator_(local_34,0x10,1,FUN_00434820);
  piVar2 = local_20;
LAB_0040f685:
  if (piVar2 != (int *)0x0) {
    FUN_00402430(piVar2,local_18 - (int)piVar2 >> 2,4);
  }
  ExceptionList = local_10;
  return;
}


