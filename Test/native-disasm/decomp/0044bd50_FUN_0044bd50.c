// FUN_0044bd50 @ 0044bd50 size=102 callers=1

void __fastcall FUN_0044bd50(int param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ulonglong local_10;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar1 = *(undefined1 *)(param_1 + 8);
  uVar2 = *(undefined4 *)(param_1 + 0x10);
  uVar3 = *(undefined4 *)(param_1 + 0x14);
  *(undefined1 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  local_10 = (ulonglong)DAT_004a2748;
  local_4 = DAT_004a2754;
  local_8 = DAT_004a2750;
  DAT_004a2748 = uVar1;
  DAT_004a2750 = uVar2;
  DAT_004a2754 = uVar3;
  FUN_00434820((char *)&local_10);
  return;
}


