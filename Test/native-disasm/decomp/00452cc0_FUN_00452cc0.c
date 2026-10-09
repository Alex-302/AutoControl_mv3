// FUN_00452cc0 @ 00452cc0 size=126 callers=1

int __fastcall FUN_00452cc0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  puVar9 = param_2;
  puVar10 = param_1;
  if (param_1 != param_2) {
    do {
      puVar8 = puVar9 + -4;
      if (puVar10 == puVar8) break;
      uVar1 = puVar9[-3];
      uVar2 = puVar9[-2];
      uVar3 = puVar9[-1];
      uVar4 = *puVar10;
      uVar5 = puVar10[1];
      uVar6 = puVar10[2];
      uVar7 = puVar10[3];
      *puVar10 = *puVar8;
      puVar10[1] = uVar1;
      puVar10[2] = uVar2;
      puVar10[3] = uVar3;
      puVar10 = puVar10 + 4;
      *puVar8 = uVar4;
      puVar9[-3] = uVar5;
      puVar9[-2] = uVar6;
      puVar9[-1] = uVar7;
      puVar9 = puVar8;
    } while (puVar10 != puVar8);
  }
  puVar9 = param_3;
  puVar10 = param_2;
  if (param_2 != param_3) {
    do {
      puVar8 = puVar9 + -4;
      if (puVar10 == puVar8) break;
      uVar1 = puVar9[-3];
      uVar2 = puVar9[-2];
      uVar3 = puVar9[-1];
      uVar4 = *puVar10;
      uVar5 = puVar10[1];
      uVar6 = puVar10[2];
      uVar7 = puVar10[3];
      *puVar10 = *puVar8;
      puVar10[1] = uVar1;
      puVar10[2] = uVar2;
      puVar10[3] = uVar3;
      puVar10 = puVar10 + 4;
      *puVar8 = uVar4;
      puVar9[-3] = uVar5;
      puVar9[-2] = uVar6;
      puVar9[-1] = uVar7;
      puVar9 = puVar8;
    } while (puVar10 != puVar8);
  }
  puVar9 = param_3;
  puVar10 = param_1;
  if (param_1 != param_3) {
    do {
      puVar8 = puVar9 + -4;
      if (puVar10 == puVar8) break;
      uVar1 = puVar9[-3];
      uVar2 = puVar9[-2];
      uVar3 = puVar9[-1];
      uVar4 = *puVar10;
      uVar5 = puVar10[1];
      uVar6 = puVar10[2];
      uVar7 = puVar10[3];
      *puVar10 = *puVar8;
      puVar10[1] = uVar1;
      puVar10[2] = uVar2;
      puVar10[3] = uVar3;
      puVar10 = puVar10 + 4;
      *puVar8 = uVar4;
      puVar9[-3] = uVar5;
      puVar9[-2] = uVar6;
      puVar9[-1] = uVar7;
      puVar9 = puVar8;
    } while (puVar10 != puVar8);
  }
  return (int)param_1 + ((int)param_3 - (int)param_2 & 0xfffffff0U);
}


