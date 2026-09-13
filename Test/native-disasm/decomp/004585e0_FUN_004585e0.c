// FUN_004585e0 @ 004585e0 size=174 callers=1

int * __fastcall FUN_004585e0(int *param_1,undefined4 param_2,int *param_3)

{
  undefined8 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ed53;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00458690(param_1,param_2,param_3);
  param_1[3] = param_3[3];
  param_1[4] = param_3[4];
  param_1[5] = param_3[5];
  *(short *)(param_1 + 6) = (short)param_3[6];
  local_8 = 0;
  uVar1 = FUN_00458690(param_1 + 7,(int)((ulonglong)uVar1 >> 0x20),param_3 + 7);
  param_1[10] = param_3[10];
  param_1[0xb] = param_3[0xb];
  param_1[0xc] = param_3[0xc];
  *(short *)(param_1 + 0xd) = (short)param_3[0xd];
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00458690(param_1 + 0xe,(int)((ulonglong)uVar1 >> 0x20),param_3 + 0xe);
  *(char *)(param_1 + 0x11) = (char)param_3[0x11];
  *(undefined1 *)((int)param_1 + 0x45) = *(undefined1 *)((int)param_3 + 0x45);
  ExceptionList = local_10;
  return param_1;
}


