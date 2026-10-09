// FUN_00457150 @ 00457150 size=259 callers=1

int * __fastcall FUN_00457150(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ebaf;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00450ec0(param_1,param_2,param_3);
  param_1[3] = param_3[3];
  local_8 = 0;
  param_1[4] = param_3[4];
  param_1[5] = 0;
  param_1[6] = 0;
  iVar1 = FUN_00448fe0((undefined4 *)0x0,(undefined4 *)0x0);
  param_1[5] = iVar1;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  local_8._0_1_ = 2;
  FUN_00457790(param_1 + 4,param_3 + 4);
  local_8._0_1_ = 3;
  param_1[0xc] = param_3[0xc];
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  iVar1 = FUN_00448fb0((undefined4 *)0x0,(undefined4 *)0x0);
  param_1[0xd] = iVar1;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  local_8 = CONCAT31(local_8._1_3_,5);
  FUN_004576d0(param_1 + 0xc,param_3 + 0xc);
  param_1[0x14] = param_3[0x14];
  param_1[0x15] = param_3[0x15];
  ExceptionList = local_10;
  return param_1;
}


