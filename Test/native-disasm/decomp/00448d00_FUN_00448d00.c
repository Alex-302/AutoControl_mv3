// FUN_00448d00 @ 00448d00 size=274 callers=2

void FUN_00448d00(undefined4 *param_1,ushort *param_2)

{
  byte *pbVar1;
  undefined4 *puVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  
  uVar5 = *(uint *)(param_2 + 8);
  puVar3 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    puVar3 = *(ushort **)param_2;
  }
  uVar6 = 0;
  uVar7 = 0x811c9dc5;
  if (uVar5 * 2 != 0) {
    do {
      pbVar1 = (byte *)((int)puVar3 + uVar6);
      uVar6 = uVar6 + 1;
      uVar7 = (*pbVar1 ^ uVar7) * 0x1000193;
    } while (uVar6 < uVar5 * 2);
  }
  uVar7 = DAT_004a2fa8 & uVar7;
  puVar9 = *(undefined4 **)(DAT_004a2f9c + uVar7 * 8);
  do {
    puVar2 = DAT_004a2f94;
    if (*(undefined4 **)(DAT_004a2f9c + uVar7 * 8) != DAT_004a2f94) {
      puVar2 = (undefined4 *)**(undefined4 **)(DAT_004a2f9c + (uVar7 * 2 + 1) * 4);
    }
    if (puVar9 == puVar2) {
      *param_1 = DAT_004a2f94;
      return;
    }
    puVar3 = (ushort *)(puVar9 + 2);
    puVar8 = param_2;
    if (7 < *(uint *)(param_2 + 10)) {
      puVar8 = *(ushort **)param_2;
    }
    if (7 < (uint)puVar9[7]) {
      puVar3 = *(ushort **)puVar3;
    }
    uVar6 = puVar9[6];
    uVar10 = uVar5;
    if (uVar6 < uVar5) {
      uVar10 = uVar6;
    }
    for (; uVar10 != 0; uVar10 = uVar10 - 1) {
      if (*puVar3 != *puVar8) {
        iVar4 = (-(uint)(*puVar3 < *puVar8) & 0xfffffffe) + 1;
        goto LAB_00448da5;
      }
      puVar3 = puVar3 + 1;
      puVar8 = puVar8 + 1;
    }
    iVar4 = 0;
LAB_00448da5:
    if (((iVar4 == 0) && (uVar5 <= uVar6)) && (uVar6 <= uVar5)) {
      uVar5 = FUN_004443e0(param_2,(ushort *)(puVar9 + 2));
      if (uVar5 != 0) {
        puVar9 = DAT_004a2f94;
      }
      *param_1 = puVar9;
      return;
    }
    puVar9 = (undefined4 *)*puVar9;
  } while( true );
}


