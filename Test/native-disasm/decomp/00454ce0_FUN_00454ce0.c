// FUN_00454ce0 @ 00454ce0 size=178 callers=2

void __fastcall FUN_00454ce0(char *param_1)

{
  char cVar1;
  undefined8 uVar2;
  short sVar3;
  undefined4 in_XMM1_Da;
  undefined4 in_XMM1_Db;
  char local_2c [8];
  undefined8 local_24;
  double local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_24._0_4_ = in_XMM1_Da;
  local_24._4_4_ = in_XMM1_Db;
  sVar3 = FID_conflict___dtest(&local_1c);
  if (0 < sVar3) {
    local_8 = 0;
    local_2c[0] = '\0';
    FUN_004381d0(&local_24,'\0');
    cVar1 = *param_1;
    *param_1 = local_2c[0];
    uVar2 = *(undefined8 *)(param_1 + 8);
    *(undefined4 *)(param_1 + 8) = (undefined4)local_24;
    *(undefined4 *)(param_1 + 0xc) = local_24._4_4_;
    local_2c[0] = cVar1;
    local_24 = uVar2;
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return;
  }
  *(undefined4 *)(param_1 + 8) = (undefined4)local_24;
  *param_1 = '\a';
  *(undefined4 *)(param_1 + 0xc) = local_24._4_4_;
  ExceptionList = local_10;
  return;
}


