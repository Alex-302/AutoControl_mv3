// FUN_00422cd0 @ 00422cd0 size=285 callers=2

void __fastcall FUN_00422cd0(undefined4 param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  void *pvVar5;
  BOOL BVar6;
  undefined4 *in_stack_fffffeb0;
  undefined4 local_124 [24];
  void *local_c4 [5];
  uint uStack_b0;
  LPVOID local_6c [2];
  int iStack_64;
  undefined4 local_4c;
  HANDLE local_48;
  int local_44;
  DWORD local_38;
  char local_34;
  undefined4 local_2c;
  undefined4 local_28;
  char local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bde2;
  pvStack_10 = ExceptionList;
  local_14 = &stack0xfffffecc;
  ExceptionList = &pvStack_10;
  local_4c = param_1;
  FUN_00404910((int *)&stack0xfffffeb0);
  pvVar5 = FUN_00403a70(local_124,in_stack_fffffeb0);
  local_8 = 0;
  FUN_00441f50((undefined2 *)local_c4,pvVar5,param_2);
  local_8._0_1_ = 2;
  FUN_00403c20(local_124);
  FUN_00405440(&local_48,(LPCWSTR)local_c4,'R',0x4000000);
  local_8._0_1_ = 3;
  uVar4 = (undefined1)local_8;
  local_8._0_1_ = 3;
  if (local_44 == 0) {
    local_38 = GetFileSize(local_48,(LPDWORD)0x0);
    FUN_00434da0(local_6c,local_38);
    local_8._0_1_ = 4;
    BVar6 = ReadFile(local_48,local_6c[0],local_38,&local_38,(LPOVERLAPPED)0x0);
    if (BVar6 != 0) {
      local_8._0_1_ = 5;
      local_34 = '\0';
      FUN_004381d0(&local_2c,'\0');
      local_8 = CONCAT31(local_8._1_3_,7);
      FUN_00433c80(local_24,(int *)local_6c);
      uVar3 = local_28;
      uVar2 = local_2c;
      cVar1 = local_34;
      local_34 = local_24[0];
      local_24[0] = cVar1;
      local_2c = local_1c;
      local_1c = uVar2;
      local_28 = local_18;
      local_18 = uVar3;
      FUN_00434820(local_24);
      local_8 = 6;
      FUN_00422e00();
      return;
    }
    uVar4 = (undefined1)local_8;
    if (local_6c[0] != (void *)0x0) {
      FUN_00402430(local_6c[0],iStack_64 - (int)local_6c[0],1);
      uVar4 = (undefined1)local_8;
    }
  }
  local_8._0_1_ = uVar4;
  if (local_48 != (HANDLE)0x0) {
    CloseHandle(local_48);
  }
  if (7 < uStack_b0) {
    FUN_00402430(local_c4[0],uStack_b0 + 1,2);
  }
  ExceptionList = pvStack_10;
  return;
}


