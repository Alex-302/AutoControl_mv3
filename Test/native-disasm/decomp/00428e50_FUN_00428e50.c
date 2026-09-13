// FUN_00428e50 @ 00428e50 size=119 callers=1

void __fastcall FUN_00428e50(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ulonglong local_18;
  undefined4 local_10;
  undefined4 local_c;
  
  FUN_004167f0(*param_1);
  iVar3 = param_1[2];
  iVar1 = param_1[4];
  iVar2 = param_1[5];
  *(undefined1 *)(param_1 + 2) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  local_18 = (ulonglong)DAT_004a28d0;
  local_c = DAT_004a28dc;
  local_10 = DAT_004a28d8;
  DAT_004a28d0 = (char)iVar3;
  DAT_004a28d8 = iVar1;
  DAT_004a28dc = iVar2;
  FUN_00434820((char *)&local_18);
  return;
}


