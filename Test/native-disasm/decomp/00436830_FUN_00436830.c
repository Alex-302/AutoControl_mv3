// FUN_00436830 @ 00436830 size=436 callers=2

undefined4 * FUN_00436830(undefined4 *param_1,ushort *param_2)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  ushort *puVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  ushort *puVar12;
  
  puVar4 = DAT_004a2f94;
  puVar8 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    puVar8 = *(ushort **)param_2;
  }
  uVar7 = 0;
  uVar11 = 0x811c9dc5;
  if (*(int *)(param_2 + 8) * 2 != 0) {
    do {
      pbVar1 = (byte *)((int)puVar8 + uVar7);
      uVar7 = uVar7 + 1;
      uVar11 = (*pbVar1 ^ uVar11) * 0x1000193;
    } while (uVar7 < (uint)(*(int *)(param_2 + 8) * 2));
  }
  puVar5 = *(undefined4 **)(DAT_004a2f9c + (uVar11 & DAT_004a2fa8) * 8);
  iVar9 = (uVar11 & DAT_004a2fa8) * 2 + 1;
  puVar3 = *(undefined4 **)(DAT_004a2f9c + -4 + iVar9 * 4);
  puVar2 = (undefined4 *)(DAT_004a2f9c + iVar9 * 4);
  do {
    puVar6 = DAT_004a2f94;
    if (puVar3 != DAT_004a2f94) {
      puVar6 = *(undefined4 **)*puVar2;
    }
    if (puVar5 == puVar6) goto LAB_004369d5;
    puVar8 = (ushort *)(puVar5 + 2);
    puVar12 = param_2;
    if (7 < *(uint *)(param_2 + 10)) {
      puVar12 = *(ushort **)param_2;
    }
    if (7 < (uint)puVar5[7]) {
      puVar8 = *(ushort **)puVar8;
    }
    uVar7 = puVar5[6];
    uVar11 = *(uint *)(param_2 + 8);
    if (uVar7 < *(uint *)(param_2 + 8)) {
      uVar11 = uVar7;
    }
    for (; uVar11 != 0; uVar11 = uVar11 - 1) {
      if (*puVar8 != *puVar12) {
        iVar9 = (-(uint)(*puVar8 < *puVar12) & 0xfffffffe) + 1;
        goto LAB_004368e0;
      }
      puVar8 = puVar8 + 1;
      puVar12 = puVar12 + 1;
    }
    iVar9 = 0;
LAB_004368e0:
    if (((iVar9 == 0) && (*(uint *)(param_2 + 8) <= uVar7)) &&
       (puVar6 = puVar5, uVar7 <= *(uint *)(param_2 + 8))) break;
    puVar5 = (undefined4 *)*puVar5;
  } while( true );
LAB_00436930:
  puVar10 = DAT_004a2f94;
  if (puVar3 != DAT_004a2f94) {
    puVar10 = *(undefined4 **)*puVar2;
  }
  if (puVar6 == puVar10) {
LAB_004369b9:
    if (puVar5 != puVar6) {
      param_1[1] = puVar6;
      *param_1 = puVar5;
      return param_1;
    }
LAB_004369d5:
    *param_1 = DAT_004a2f94;
    param_1[1] = puVar4;
    return param_1;
  }
  puVar8 = (ushort *)(puVar6 + 2);
  if (7 < (uint)puVar6[7]) {
    puVar8 = *(ushort **)puVar8;
  }
  puVar12 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    puVar12 = *(ushort **)param_2;
  }
  uVar7 = puVar6[6];
  if (*(uint *)(param_2 + 8) < uVar7) {
    uVar7 = *(uint *)(param_2 + 8);
  }
  for (; uVar7 != 0; uVar7 = uVar7 - 1) {
    if (*puVar12 != *puVar8) {
      iVar9 = (-(uint)(*puVar12 < *puVar8) & 0xfffffffe) + 1;
      goto LAB_0043697b;
    }
    puVar12 = puVar12 + 1;
    puVar8 = puVar8 + 1;
  }
  iVar9 = 0;
LAB_0043697b:
  if (((iVar9 != 0) || (uVar7 = puVar6[6], *(uint *)(param_2 + 8) < uVar7)) ||
     (*(uint *)(param_2 + 8) != uVar7)) goto LAB_004369b9;
  puVar6 = (undefined4 *)*puVar6;
  goto LAB_00436930;
}


