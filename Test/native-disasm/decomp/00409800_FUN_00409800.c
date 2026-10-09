// FUN_00409800 @ 00409800 size=462 callers=1

void FUN_00409800(int *param_1)

{
  char cVar1;
  int *piVar2;
  undefined8 uVar3;
  char *pcVar4;
  uint in_stack_ffffff54;
  void *pvVar5;
  char local_90 [16];
  undefined1 local_80 [16];
  char local_70 [8];
  undefined8 local_68;
  undefined1 local_60 [8];
  undefined8 local_58;
  char local_50 [8];
  undefined8 local_48;
  undefined1 local_40 [8];
  undefined8 local_38;
  char local_30 [16];
  char local_20 [8];
  undefined8 local_18;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479c0f;
  pvStack_10 = ExceptionList;
  local_50[0] = '\0';
  local_48 = 0;
  piVar2 = (int *)*param_1;
  ExceptionList = &pvStack_10;
  FUN_00451110(local_50,(uint *)&DAT_0048d024);
  local_40[0] = 0;
  local_38 = 0;
  FUN_00451040(local_40,*piVar2);
  local_8 = 0;
  FUN_00434b50(local_90,local_50,local_30,'\x01','\x02');
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_50,0x10,2,FUN_00434820);
  local_70[0] = '\0';
  local_68 = 0;
  FUN_00451110(local_70,(uint *)&DAT_0048d02c);
  local_60[0] = 0;
  local_58 = 0;
  FUN_00450f50(local_60,piVar2[3]);
  local_8._0_1_ = 3;
  FUN_00434b50(local_80,local_70,local_50,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_destructor_iterator_(local_70,0x10,2,FUN_00434820);
  local_8 = 6;
  FUN_00434b50(local_30,local_90,local_70,'\x01','\x02');
  local_8._0_1_ = 8;
  _eh_vector_destructor_iterator_(local_90,0x10,2,FUN_00434820);
  if ((*piVar2 == -0x1f928c9d) && (2 < (uint)piVar2[4])) {
    local_20[0] = '\0';
    local_18 = 0;
    param_1 = (int *)(*(int *)(*(int *)(*(int *)(piVar2[7] + 0xc) + 4) + 4) + 8);
    FUN_00451200(local_20,&param_1);
    local_8._0_1_ = 9;
    pcVar4 = (char *)FUN_00440e70(local_30,(uint *)"excepClass");
    local_8._0_1_ = 8;
    cVar1 = *pcVar4;
    *pcVar4 = local_20[0];
    uVar3 = *(undefined8 *)(pcVar4 + 8);
    *(undefined4 *)(pcVar4 + 8) = (undefined4)local_18;
    *(undefined4 *)(pcVar4 + 0xc) = local_18._4_4_;
    local_20[0] = cVar1;
    local_18 = uVar3;
    FUN_00434820(local_20);
  }
  pvVar5 = (void *)(in_stack_ffffff54 & 0xffffff00);
  FUN_0043ace0(&stack0xffffff54,(uint *)"NH-error",8);
  FUN_00408c90(local_30,pvVar5);
  FUN_0040f310();
                    /* WARNING: Subroutine does not return */
  ExitProcess(1);
}


