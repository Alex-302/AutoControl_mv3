// FUN_00447590 @ 00447590 size=146 callers=1

int __fastcall FUN_00447590(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e4e0;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  puVar2 = FUN_00449540(param_1 + 9,0);
  FUN_00449310(param_1);
  if (*param_1 != param_1[2]) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(0xe);
  }
  FUN_004494b0(param_1 + 9,(int)puVar2);
  FUN_0044e3a0(param_1 + 9,0x15);
  iVar1 = param_1[9];
  *(int *)(iVar1 + 0x14) = param_1[0x10];
  *(int *)(iVar1 + 0x1c) = param_1[3] + 1;
  FUN_00403570(iVar1,0,0);
  ExceptionList = local_10;
  return iVar1;
}


