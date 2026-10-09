// FUN_0044f420 @ 0044f420 size=522 callers=4

void __thiscall FUN_0044f420(void *this,int *param_1,byte *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  byte *pbVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  byte *pbVar12;
  bool bVar13;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar6 = param_3;
  puStack_c = &LAB_0047e7c0;
  local_10 = ExceptionList;
  local_8 = 0;
  pbVar8 = param_2;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    pbVar8 = *(byte **)param_2;
  }
  uVar7 = 0;
  uVar11 = 0x811c9dc5;
  if (*(uint *)(param_2 + 0x10) != 0) {
    do {
      pbVar12 = pbVar8 + uVar7;
      uVar7 = uVar7 + 1;
      uVar11 = (*pbVar12 ^ uVar11) * 0x1000193;
    } while (uVar7 < *(uint *)(param_2 + 0x10));
  }
  piVar9 = (int *)((int)this + 4);
  iVar10 = (*(uint *)((int)this + 0x18) & uVar11) * 8;
  iVar1 = *(int *)(*(int *)((int)this + 0xc) + iVar10);
  if (iVar1 == *piVar9) {
    iVar2 = *piVar9;
  }
  else {
    iVar2 = **(int **)(*(int *)((int)this + 0xc) + 4 + iVar10);
  }
joined_r0x0044f4b2:
  do {
    if (iVar2 == iVar1) {
      param_2 = (byte *)param_3;
      iVar1 = *param_3;
      ExceptionList = &local_10;
      if (iVar2 != iVar1) {
        ExceptionList = &local_10;
        *(int *)param_3[1] = iVar1;
        **(int **)(iVar1 + 4) = iVar2;
        **(undefined4 **)(iVar2 + 4) = param_3;
        iVar3 = *(int *)(iVar2 + 4);
        *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(iVar1 + 4);
        *(int *)(iVar1 + 4) = param_3[1];
        param_3[1] = iVar3;
      }
      piVar9 = (int *)(iVar10 + *(int *)((int)this + 0xc));
      if (*piVar9 == *(int *)((int)this + 4)) {
        *piVar9 = (int)param_3;
        *(int **)(*(int *)((int)this + 0xc) + 4 + iVar10) = param_3;
      }
      else if (*piVar9 == iVar2) {
        *piVar9 = (int)param_3;
      }
      else {
        piVar4 = *(int **)piVar9[1];
        piVar9[1] = (int)piVar4;
        if (piVar4 != param_3) {
          iVar10 = iVar10 + *(int *)((int)this + 0xc);
          *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(*(int *)(iVar10 + 4) + 4);
        }
      }
      local_8 = 2;
      FUN_004508c0(this);
      *param_1 = (int)piVar6;
      *(undefined1 *)(param_1 + 1) = 1;
      ExceptionList = local_10;
      return;
    }
    iVar2 = *(int *)(iVar2 + 4);
    pbVar8 = (byte *)(iVar2 + 8);
    if (0xf < *(uint *)(iVar2 + 0x1c)) {
      pbVar8 = *(byte **)pbVar8;
    }
    pbVar12 = param_2;
    if (0xf < *(uint *)(param_2 + 0x14)) {
      pbVar12 = *(byte **)param_2;
    }
    uVar7 = *(uint *)(iVar2 + 0x18);
    uVar11 = uVar7;
    if (*(uint *)(param_2 + 0x10) < uVar7) {
      uVar11 = *(uint *)(param_2 + 0x10);
    }
    if (uVar11 != 0) {
      while (uVar5 = uVar11 - 4, 3 < uVar11) {
        if (*(int *)pbVar12 != *(int *)pbVar8) goto LAB_0044f516;
        pbVar12 = pbVar12 + 4;
        pbVar8 = pbVar8 + 4;
        uVar11 = uVar5;
      }
      if (uVar5 == 0xfffffffc) {
LAB_0044f54a:
        uVar11 = 0;
      }
      else {
LAB_0044f516:
        bVar13 = *pbVar12 < *pbVar8;
        if ((*pbVar12 == *pbVar8) &&
           ((uVar5 == 0xfffffffd ||
            ((bVar13 = pbVar12[1] < pbVar8[1], pbVar12[1] == pbVar8[1] &&
             ((uVar5 == 0xfffffffe ||
              ((bVar13 = pbVar12[2] < pbVar8[2], pbVar12[2] == pbVar8[2] &&
               ((uVar5 == 0xffffffff || (bVar13 = pbVar12[3] < pbVar8[3], pbVar12[3] == pbVar8[3])))
               ))))))))) goto LAB_0044f54a;
        uVar11 = -(uint)bVar13 | 1;
      }
      if (uVar11 != 0) goto joined_r0x0044f4b2;
    }
    if ((uVar7 <= *(uint *)(param_2 + 0x10)) && (*(uint *)(param_2 + 0x10) <= uVar7)) {
      ExceptionList = &local_10;
      FUN_00450d60(piVar9,(int *)&param_2,param_3);
      *param_1 = iVar2;
      *(undefined1 *)(param_1 + 1) = 0;
      ExceptionList = local_10;
      return;
    }
  } while( true );
}


