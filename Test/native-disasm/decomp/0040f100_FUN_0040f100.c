// FUN_0040f100 @ 0040f100 size=524 callers=1

/* WARNING: Removing unreachable block (ram,0x0040f2b0) */

void __fastcall FUN_0040f100(char param_1)

{
  bool bVar1;
  BOOL BVar2;
  BOOL BVar3;
  int iVar4;
  undefined1 uVar5;
  void *in_stack_ffffff28;
  char local_b8 [16];
  undefined1 local_a8 [16];
  undefined1 local_98 [16];
  void *local_88;
  undefined1 *puStack_84;
  undefined4 local_80;
  char local_7c [16];
  char local_6c [8];
  undefined8 local_64;
  undefined1 local_5c [8];
  undefined8 local_54;
  char local_4c [8];
  undefined8 local_44;
  undefined1 local_3c [8];
  undefined8 local_34;
  char local_2c [8];
  undefined8 local_24;
  undefined1 local_1c;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_80 = 0xffffffff;
  puStack_84 = &LAB_0047a4cc;
  local_88 = ExceptionList;
  ExceptionList = &local_88;
  BVar2 = UnhookWindowsHookEx(DAT_004a23d0);
  BVar3 = UnhookWindowsHookEx(DAT_004a23e8);
  if ((BVar2 == 0) || (BVar3 == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  local_4c[0] = '\0';
  local_44 = 0;
  FUN_00451110(local_4c,(uint *)"devIdx");
  local_3c[0] = 0;
  local_34 = 0;
  FUN_004511e0(local_3c,param_1);
  local_80 = 0;
  FUN_00434b50(local_b8,local_4c,local_2c,'\x01','\x02');
  local_80._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_4c,0x10,2,FUN_00434820);
  local_6c[0] = '\0';
  local_64 = 0;
  FUN_00450f70(local_6c,(uint *)"hooksTimeout");
  iVar4 = FUN_0040eff0();
  local_5c[0] = 0;
  local_54 = 0;
  FUN_00450f50(local_5c,iVar4);
  local_80._0_1_ = 3;
  FUN_00434b50(local_a8,local_6c,local_4c,'\x01','\x02');
  local_80._0_1_ = 5;
  _eh_vector_destructor_iterator_(local_6c,0x10,2,FUN_00434820);
  local_2c[0] = '\0';
  local_24 = 0;
  FUN_00451110(local_2c,(uint *)"needed");
  local_c = CONCAT31(local_c._1_3_,!bVar1);
  local_1c = 4;
  _local_14 = CONCAT44(local_8,local_c);
  local_80._0_1_ = 6;
  FUN_00434b50(local_98,local_2c,(char *)&local_c,'\x01','\x02');
  local_80 = CONCAT31(local_80._1_3_,8);
  _eh_vector_destructor_iterator_(local_2c,0x10,2,FUN_00434820);
  local_80 = 9;
  FUN_00434b50(local_7c,local_b8,(char *)&local_88,'\x01','\x02');
  local_80 = CONCAT31(local_80._1_3_,10);
                    /* WARNING: Ignoring partial resolution of indirect */
  uVar5 = 0;
  FUN_0043ace0(&stack0xffffff28,(uint *)"no-hook-notice",0xe);
  FUN_00408c90(local_7c,in_stack_ffffff28);
  FUN_00434820(local_7c);
  local_80 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_b8,0x10,3,FUN_00434820);
  FUN_00412ad0();
  FUN_00431110();
  ExceptionList = local_88;
  return;
}


