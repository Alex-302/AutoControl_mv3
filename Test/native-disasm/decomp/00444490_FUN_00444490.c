// FUN_00444490 @ 00444490 size=148 callers=1

void FUN_00444490(uint param_1)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = FUN_0043f9c0(param_1);
  FUN_0045b0e0(puVar1,DAT_004a3348,(int)DAT_004a334c - (int)DAT_004a3348);
  iVar2 = (int)DAT_004a334c - (int)DAT_004a3348;
  if (DAT_004a3348 != (uint *)0x0) {
    FUN_00402430(DAT_004a3348,((int)DAT_004a3350 - (int)DAT_004a3348) / 0x14,0x14);
  }
  DAT_004a3348 = puVar1;
  DAT_004a3350 = puVar1 + param_1 * 5;
  DAT_004a334c = puVar1 + (iVar2 / 0x14) * 5;
  return;
}


