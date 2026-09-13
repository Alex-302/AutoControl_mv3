// FUN_00437090 @ 00437090 size=241 callers=3

undefined4 * FUN_00437090(undefined4 *param_1,byte *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  puVar2 = DAT_004a27d4;
  uVar5 = DAT_004a27e8 &
          ((((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 ^ (uint)param_2[2])
           * 0x1000193 ^ (uint)param_2[3]) * 0x1000193;
  puVar3 = *(undefined4 **)(DAT_004a27dc + uVar5 * 8);
  iVar1 = uVar5 * 8 + 4;
  while( true ) {
    puVar4 = DAT_004a27d4;
    if (*(undefined4 **)(uVar5 * 8 + DAT_004a27dc) != DAT_004a27d4) {
      puVar4 = (undefined4 *)**(undefined4 **)(iVar1 + DAT_004a27dc);
    }
    if (puVar3 == puVar4) goto LAB_0043716f;
    if (puVar3[2] == *(int *)param_2) break;
    puVar3 = (undefined4 *)*puVar3;
  }
  puVar4 = puVar3;
  while( true ) {
    puVar6 = DAT_004a27d4;
    if (*(undefined4 **)(uVar5 * 8 + DAT_004a27dc) != DAT_004a27d4) {
      puVar6 = (undefined4 *)**(undefined4 **)(iVar1 + DAT_004a27dc);
    }
    if ((puVar4 == puVar6) || (*(int *)param_2 != puVar4[2])) break;
    puVar4 = (undefined4 *)*puVar4;
  }
  if (puVar3 != puVar4) {
    param_1[1] = puVar4;
    *param_1 = puVar3;
    return param_1;
  }
LAB_0043716f:
  *param_1 = DAT_004a27d4;
  param_1[1] = puVar2;
  return param_1;
}


