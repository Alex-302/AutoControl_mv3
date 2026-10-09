// FUN_00419890 @ 00419890 size=1036 callers=26

undefined * __fastcall FUN_00419890(uint param_1)

{
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  char local_134 [16];
  undefined1 local_124 [16];
  undefined1 local_114 [16];
  char local_104 [16];
  char local_f4 [16];
  char local_e4 [16];
  char local_d4 [16];
  char local_c4 [8];
  undefined8 local_bc;
  undefined1 local_b4 [8];
  undefined8 local_ac;
  char local_a4 [8];
  undefined8 local_9c;
  undefined1 local_94 [8];
  undefined8 local_8c;
  char local_84 [8];
  undefined8 local_7c;
  undefined1 local_74 [8];
  undefined8 local_6c;
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [8];
  undefined8 local_3c;
  undefined1 local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  char local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b532;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a32ec) {
    ExceptionList = &local_10;
    FUN_0045a219(&DAT_004a32ec);
    if (DAT_004a32ec == -1) {
      local_64[0] = '\0';
      local_5c = 0;
      FUN_00451110(local_64,(uint *)"itemType");
      local_54[0] = 0;
      local_4c = 0;
      FUN_00451320(local_54,CONCAT31((int3)((uint)extraout_EDX >> 8),1));
      local_8 = 0;
      FUN_00434b50(local_24,local_64,local_44,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,2);
      _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
      local_8 = 3;
      FUN_00434b50(local_e4,local_24,local_14,'\x01','\x02');
      local_8._0_1_ = 4;
      FUN_00410fb0(&DAT_004a2a90,local_e4,0);
      FUN_00434820(local_e4);
      local_8._0_1_ = 7;
      _eh_vector_destructor_iterator_(local_24,0x10,1,FUN_00434820);
      local_84[0] = '\0';
      local_7c = 0;
      FUN_00451110(local_84,(uint *)"itemType");
      local_74[0] = 0;
      local_6c = 0;
      FUN_00451320(local_74,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),2));
      local_8._0_1_ = 8;
      FUN_00434b50(local_134,local_84,local_64,'\x01','\x02');
      local_8._0_1_ = 10;
      _eh_vector_destructor_iterator_(local_84,0x10,2,FUN_00434820);
      local_a4[0] = '\0';
      local_9c = 0;
      FUN_00451110(local_a4,(uint *)"title");
      local_8._0_1_ = 0xb;
      local_94[0] = 0;
      local_8c = 0;
      FUN_00451110(local_94,(uint *)"(empty)");
      local_8._0_1_ = 0xc;
      FUN_00434b50(local_124,local_a4,local_84,'\x01','\x02');
      local_8._0_1_ = 0xe;
      _eh_vector_destructor_iterator_(local_a4,0x10,2,FUN_00434820);
      local_44[0] = '\0';
      local_3c = 0;
      FUN_00451110(local_44,(uint *)"disabled");
      local_1c = CONCAT31(local_1c._1_3_,1);
      local_34 = 4;
      _local_2c = CONCAT44(local_18,local_1c);
      local_8._0_1_ = 0xf;
      FUN_00434b50(local_114,local_44,local_24,'\x01','\x02');
      local_8._0_1_ = 0x11;
      _eh_vector_destructor_iterator_(local_44,0x10,2,FUN_00434820);
      local_8._0_1_ = 0x12;
      FUN_00434b50(local_f4,local_134,local_104,'\x01','\x02');
      local_8._0_1_ = 0x13;
      FUN_00410fb0(&DAT_004a2ab8,local_f4,0);
      FUN_00434820(local_f4);
      local_8._0_1_ = 0x16;
      _eh_vector_destructor_iterator_(local_134,0x10,3,FUN_00434820);
      local_c4[0] = '\0';
      local_bc = 0;
      FUN_00451110(local_c4,(uint *)"itemType");
      local_b4[0] = 0;
      local_ac = 0;
      FUN_00451320(local_b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),3));
      local_8._0_1_ = 0x17;
      FUN_00434b50(local_d4,local_c4,local_a4,'\x01','\x02');
      local_8._0_1_ = 0x19;
      _eh_vector_destructor_iterator_(local_c4,0x10,2,FUN_00434820);
      local_8._0_1_ = 0x1a;
      FUN_00434b50(local_104,local_d4,local_c4,'\x01','\x02');
      local_8._0_1_ = 0x1b;
      FUN_00410fb0(&DAT_004a2ae0,local_104,0);
      FUN_00434820(local_104);
      local_8 = CONCAT31(local_8._1_3_,0x1e);
      _eh_vector_destructor_iterator_(local_d4,0x10,1,FUN_00434820);
      local_8 = 0xffffffff;
      _atexit(FUN_0047f610);
      FUN_0045a1da(&DAT_004a32ec);
    }
  }
  if ((int)param_1 < 0) {
    ExceptionList = local_10;
    return &DAT_004a2a90 + (param_1 + 1) * -0x28;
  }
  if ((uint)((DAT_004a2904 - DAT_004a2900) / 0x28) <= param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid vector<T> subscript");
  }
  ExceptionList = local_10;
  return (undefined *)(DAT_004a2900 + param_1 * 0x28);
}


