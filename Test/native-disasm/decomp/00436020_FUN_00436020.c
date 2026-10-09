// FUN_00436020 @ 00436020 size=435 callers=7

int * __thiscall FUN_00436020(void *this,int *param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  bool bVar12;
  
  uVar1 = *(uint *)(param_2 + 0x10);
  pbVar10 = param_2;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    pbVar10 = *(byte **)param_2;
  }
  uVar6 = 0;
  uVar9 = 0x811c9dc5;
  if (uVar1 != 0) {
    do {
      pbVar11 = pbVar10 + uVar6;
      uVar6 = uVar6 + 1;
      uVar9 = (*pbVar11 ^ uVar9) * 0x1000193;
    } while (uVar6 < uVar1);
  }
  uVar9 = *(uint *)((int)this + 0x18) & uVar9;
  iVar2 = *(int *)((int)this + 0xc);
  puVar5 = *(undefined4 **)(iVar2 + uVar9 * 8);
  puVar3 = *(undefined4 **)((int)this + 4);
  do {
    puVar7 = puVar3;
    if (*(undefined4 **)(iVar2 + uVar9 * 8) != puVar3) {
      puVar7 = (undefined4 *)**(undefined4 **)(iVar2 + (uVar9 * 2 + 1) * 4);
    }
    if (puVar5 == puVar7) {
      *param_1 = (int)puVar3;
      return param_1;
    }
    pbVar10 = (byte *)(puVar5 + 2);
    pbVar11 = param_2;
    if (0xf < *(uint *)(param_2 + 0x14)) {
      pbVar11 = *(byte **)param_2;
    }
    if (0xf < (uint)puVar5[7]) {
      pbVar10 = *(byte **)pbVar10;
    }
    uVar6 = puVar5[6];
    uVar8 = uVar1;
    if (uVar6 < uVar1) {
      uVar8 = uVar6;
    }
    if (uVar8 == 0) {
LAB_0043611a:
      if ((uVar1 <= uVar6) && (uVar6 <= uVar1)) break;
    }
    else {
      while (uVar4 = uVar8 - 4, 3 < uVar8) {
        if (*(int *)pbVar10 != *(int *)pbVar11) goto LAB_004360dc;
        pbVar10 = pbVar10 + 4;
        pbVar11 = pbVar11 + 4;
        uVar8 = uVar4;
      }
      if (uVar4 == 0xfffffffc) {
LAB_00436110:
        uVar8 = 0;
      }
      else {
LAB_004360dc:
        bVar12 = *pbVar10 < *pbVar11;
        if ((*pbVar10 == *pbVar11) &&
           ((uVar4 == 0xfffffffd ||
            ((bVar12 = pbVar10[1] < pbVar11[1], pbVar10[1] == pbVar11[1] &&
             ((uVar4 == 0xfffffffe ||
              ((bVar12 = pbVar10[2] < pbVar11[2], pbVar10[2] == pbVar11[2] &&
               ((uVar4 == 0xffffffff || (bVar12 = pbVar10[3] < pbVar11[3], pbVar10[3] == pbVar11[3])
                ))))))))))) goto LAB_00436110;
        uVar8 = -(uint)bVar12 | 1;
      }
      if (uVar8 == 0) goto LAB_0043611a;
    }
    puVar5 = (undefined4 *)*puVar5;
  } while( true );
  pbVar10 = (byte *)(puVar5 + 2);
  if (0xf < (uint)puVar5[7]) {
    pbVar10 = *(byte **)pbVar10;
  }
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(byte **)param_2;
  }
  uVar6 = puVar5[6];
  uVar9 = uVar6;
  if (uVar1 < uVar6) {
    uVar9 = uVar1;
  }
  if (uVar9 == 0) {
LAB_004361a7:
    if ((uVar6 <= uVar1) && (uVar1 <= uVar6)) goto LAB_004361b1;
  }
  else {
    while (uVar8 = uVar9 - 4, 3 < uVar9) {
      if (*(int *)param_2 != *(int *)pbVar10) goto LAB_0043616d;
      param_2 = param_2 + 4;
      pbVar10 = pbVar10 + 4;
      uVar9 = uVar8;
    }
    if (uVar8 == 0xfffffffc) {
LAB_004361a1:
      uVar9 = 0;
    }
    else {
LAB_0043616d:
      bVar12 = *param_2 < *pbVar10;
      if ((*param_2 == *pbVar10) &&
         ((uVar8 == 0xfffffffd ||
          ((bVar12 = param_2[1] < pbVar10[1], param_2[1] == pbVar10[1] &&
           ((uVar8 == 0xfffffffe ||
            ((bVar12 = param_2[2] < pbVar10[2], param_2[2] == pbVar10[2] &&
             ((uVar8 == 0xffffffff || (bVar12 = param_2[3] < pbVar10[3], param_2[3] == pbVar10[3])))
             ))))))))) goto LAB_004361a1;
      uVar9 = -(uint)bVar12 | 1;
    }
    if (uVar9 == 0) goto LAB_004361a7;
  }
  puVar5 = puVar3;
LAB_004361b1:
  *param_1 = (int)puVar5;
  return param_1;
}


