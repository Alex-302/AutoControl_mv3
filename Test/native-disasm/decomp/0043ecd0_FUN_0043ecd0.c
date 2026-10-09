// FUN_0043ecd0 @ 0043ecd0 size=171 callers=1

void __fastcall FUN_0043ecd0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_1 != &DAT_004a2a10) {
    uVar2 = *param_1;
    *param_1 = DAT_004a2a10;
    puVar1 = param_1 + 1;
    DAT_004a2a10 = uVar2;
    if (puVar1 != &DAT_004a2a14) {
      uVar2 = *puVar1;
      *puVar1 = DAT_004a2a14;
      uVar3 = param_1[2];
      DAT_004a2a14 = uVar2;
      param_1[2] = DAT_004a2a18;
      DAT_004a2a18 = uVar3;
    }
    puVar1 = param_1 + 3;
    if (puVar1 != &DAT_004a2a1c) {
      uVar2 = *puVar1;
      *puVar1 = DAT_004a2a1c;
      uVar3 = param_1[4];
      DAT_004a2a1c = uVar2;
      param_1[4] = DAT_004a2a20;
      uVar2 = param_1[5];
      DAT_004a2a20 = uVar3;
      param_1[5] = DAT_004a2a24;
      DAT_004a2a24 = uVar2;
    }
    uVar2 = param_1[6];
    param_1[6] = DAT_004a2a28;
    uVar3 = param_1[7];
    DAT_004a2a28 = uVar2;
    param_1[7] = DAT_004a2a2c;
    DAT_004a2a2c = uVar3;
  }
  return;
}


