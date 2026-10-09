// FUN_0042b730 @ 0042b730 size=415 callers=1

undefined1 * __cdecl FUN_0042b730(undefined1 *param_1,void *param_2)

{
  LPCSTR pCVar1;
  int *piVar2;
  UINT UVar3;
  undefined4 *in_stack_ffffff7c;
  void *local_60 [4];
  undefined4 local_50;
  uint local_4c;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [2];
  int local_28;
  void *local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cc08;
  local_10 = ExceptionList;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_0040c920((int *)local_30);
  local_8 = 0;
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  FUN_0043ace0(local_48,(uint *)&DAT_0048d624,4);
  local_8._0_1_ = 1;
  pCVar1 = (LPCSTR)FUN_004342f0(param_2,local_60,local_48,(uint *)&DAT_0048e75c);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00404640((LPWSTR)&stack0xffffff7c,pCVar1);
  piVar2 = FUN_0040c030((int *)&local_24,0xd6c18935,in_stack_ffffff7c);
  UVar3 = SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
  if (local_24 != (void *)0x0) {
    FUN_00402430(local_24,(local_1c - (int)local_24) / 0x1c,0x1c);
    local_24 = (void *)0x0;
    local_20 = 0;
    local_1c = 0;
  }
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  local_8 = local_8 & 0xffffff00;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  if (0xf < local_34) {
    FUN_00402430(local_48[0],local_34 + 1,1);
  }
  FUN_0040cab0((uint *)&local_24,local_30);
  if (local_24 != (void *)0x0) {
    FUN_00402430(local_24,local_1c - (int)local_24 >> 1,2);
  }
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  FUN_00451040(param_1,UVar3);
  if (local_30[0] != (void *)0x0) {
    FUN_00402430(local_30[0],local_28 - (int)local_30[0] >> 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}


