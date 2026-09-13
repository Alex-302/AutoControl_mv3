// FUN_00418490 @ 00418490 size=781 callers=2

void __fastcall FUN_00418490(char param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char local_6c [8];
  undefined8 local_64;
  undefined1 local_5c [8];
  undefined8 local_54;
  undefined1 local_4c [8];
  undefined8 local_44;
  undefined1 local_3c [8];
  undefined8 local_34;
  char local_2c [4];
  void *local_28 [2];
  int local_20;
  void *local_1c [2];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b2b3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2b6c) {
    ExceptionList = &local_10;
    FUN_0045a219(&DAT_004a2b6c);
    if (DAT_004a2b6c == -1) {
      local_8 = 0;
      uVar1 = 0;
      uVar2 = 0;
      local_6c[0] = '\0';
      local_64 = 0;
      FUN_00450f50(local_6c,0xa2);
      local_5c[0] = 0;
      local_54 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_5c,0x58);
      local_4c[0] = 0;
      local_44 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_4c,0x458);
      local_3c[0] = 0;
      local_34 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_3c,0x4a2);
      local_8._0_1_ = 1;
      FUN_00434b50(local_2c,local_6c,local_2c,'\x01','\x02');
      local_8._0_1_ = 2;
      FUN_0040c190((int *)&DAT_004a2ea0,local_2c,0xd6c18935,'\0');
      FUN_00434820(local_2c);
      local_8._0_1_ = 5;
      _eh_vector_destructor_iterator_(local_6c,0x10,4,FUN_00434820);
      uVar1 = 0;
      uVar2 = 0;
      local_6c[0] = '\0';
      local_64 = 0;
      FUN_00450f50(local_6c,0xa2);
      local_5c[0] = 0;
      local_54 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_5c,0x43);
      local_4c[0] = 0;
      local_44 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_4c,0x443);
      local_3c[0] = 0;
      local_34 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_3c,0x4a2);
      local_8._0_1_ = 6;
      FUN_00434b50(local_2c,local_6c,local_2c,'\x01','\x02');
      local_8._0_1_ = 7;
      FUN_0040c190((int *)&DAT_004a2eac,local_2c,0xd6c18935,'\0');
      FUN_00434820(local_2c);
      local_8._0_1_ = 10;
      _eh_vector_destructor_iterator_(local_6c,0x10,4,FUN_00434820);
      uVar1 = 0;
      uVar2 = 0;
      local_6c[0] = '\0';
      local_64 = 0;
      FUN_00450f50(local_6c,0xa2);
      local_5c[0] = 0;
      local_54 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_5c,0x56);
      local_4c[0] = 0;
      local_44 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_4c,0x456);
      local_3c[0] = 0;
      local_34 = CONCAT44(uVar2,uVar1);
      FUN_00450f50(local_3c,0x4a2);
      local_8._0_1_ = 0xb;
      FUN_00434b50(local_2c,local_6c,local_2c,'\x01','\x02');
      local_8._0_1_ = 0xc;
      FUN_0040c190((int *)&DAT_004a2eb8,local_2c,0xd6c18935,'\0');
      FUN_00434820(local_2c);
      local_8 = CONCAT31(local_8._1_3_,0xf);
      _eh_vector_destructor_iterator_(local_6c,0x10,4,FUN_00434820);
      _atexit(FUN_0047f580);
      local_8 = 0xffffffff;
      FUN_0045a1da(&DAT_004a2b6c);
    }
  }
  FUN_0040c920((int *)local_1c);
  local_8 = 0x10;
  SendInput((*(int *)(&DAT_004a2ea4 + param_1 * 0xc) -
            (int)*(LPINPUT *)(&DAT_004a2ea0 + param_1 * 0xc)) / 0x1c,
            *(LPINPUT *)(&DAT_004a2ea0 + param_1 * 0xc),0x1c);
  FUN_0040cab0((uint *)local_28,local_1c);
  if (local_28[0] != (void *)0x0) {
    FUN_00402430(local_28[0],local_20 - (int)local_28[0] >> 1,2);
  }
  if (local_1c[0] != (void *)0x0) {
    FUN_00402430(local_1c[0],local_14 - (int)local_1c[0] >> 1,2);
  }
  ExceptionList = local_10;
  return;
}


