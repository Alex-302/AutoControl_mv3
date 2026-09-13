// FUN_0043ee10 @ 0043ee10 size=171 callers=1

void __fastcall FUN_0043ee10(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_1 != &DAT_004a29f0) {
    uVar2 = *param_1;
    *param_1 = DAT_004a29f0;
    puVar1 = param_1 + 1;
    DAT_004a29f0 = uVar2;
    if (puVar1 != &DAT_004a29f4) {
      uVar2 = *puVar1;
      *puVar1 = DAT_004a29f4;
      uVar3 = param_1[2];
      DAT_004a29f4 = uVar2;
      param_1[2] = DAT_004a29f8;
      DAT_004a29f8 = uVar3;
    }
    puVar1 = param_1 + 3;
    if (puVar1 != &DAT_004a29fc) {
      uVar2 = *puVar1;
      *puVar1 = DAT_004a29fc;
      uVar3 = param_1[4];
      DAT_004a29fc = uVar2;
      param_1[4] = DAT_004a2a00;
      uVar2 = param_1[5];
      DAT_004a2a00 = uVar3;
      param_1[5] = DAT_004a2a04;
      DAT_004a2a04 = uVar2;
    }
    uVar2 = param_1[6];
    param_1[6] = DAT_004a2a08;
    uVar3 = param_1[7];
    DAT_004a2a08 = uVar2;
    param_1[7] = DAT_004a2a0c;
    DAT_004a2a0c = uVar3;
  }
  return;
}


