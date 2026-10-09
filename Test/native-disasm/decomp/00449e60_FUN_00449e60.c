// FUN_00449e60 @ 00449e60 size=87 callers=3

bool __fastcall FUN_00449e60(int *param_1)

{
  undefined4 uVar1;
  uint *extraout_EDX;
  
  param_1[0x13] = param_1[0x15];
  *param_1 = param_1[0x15];
  FUN_0044d710(param_1 + 1,param_1[0x1a]);
  FUN_00449010(param_1 + 5,param_1[0x1a]);
  *(undefined2 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x1d) = 0;
  param_1[0x1e] = 10000000;
  param_1[0x1f] = 1000;
  uVar1 = FUN_0044e860(param_1,extraout_EDX,(uint *)param_1[0x16]);
  return (char)uVar1 != '\0';
}


