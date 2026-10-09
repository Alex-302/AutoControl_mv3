// FUN_00402c90 @ 00402c90 size=188 callers=1

undefined1 * __fastcall
FUN_00402c90(undefined1 *param_1,uint *param_2,undefined4 param_3,undefined4 param_4,void *param_5)

{
  undefined4 *puVar1;
  int in_stack_0000001c;
  uint in_stack_00000020;
  void *local_30 [5];
  uint local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479160;
  local_10 = ExceptionList;
  local_18 = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  local_14 = param_1;
  if (in_stack_0000001c != 0) {
    ExceptionList = &local_10;
    FUN_0043af90((uint *)&param_5,param_2,(uint *)&DAT_0048cb64,2);
  }
  puVar1 = (undefined4 *)FUN_00402bf0(&param_3,local_30);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0043b0c0(&param_5,puVar1,0,0xffffffff);
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)&param_5);
  if (0xf < in_stack_00000020) {
    FUN_00402430(param_5,in_stack_00000020 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}


