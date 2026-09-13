// FUN_0043c190 @ 0043c190 size=111 callers=1

void FUN_0043c190(uint param_1)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = FUN_0043f960(param_1);
  FUN_0045b0e0(puVar1,DAT_004a2508,(int)DAT_004a250c - (int)DAT_004a2508);
  iVar2 = (int)DAT_004a250c - (int)DAT_004a2508;
  if (DAT_004a2508 != (uint *)0x0) {
    FUN_00402430(DAT_004a2508,(int)DAT_004a2510 - (int)DAT_004a2508 >> 2,4);
  }
  DAT_004a2508 = puVar1;
  DAT_004a2510 = puVar1 + param_1;
  DAT_004a250c = puVar1 + (iVar2 >> 2);
  return;
}


