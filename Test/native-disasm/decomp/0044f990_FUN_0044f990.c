// FUN_0044f990 @ 0044f990 size=456 callers=2

void __thiscall FUN_0044f990(void *this,int *param_1,ushort *param_2,int *param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  ushort *puVar12;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar5 = param_3;
  puStack_c = &LAB_0047e7f0;
  local_10 = ExceptionList;
  local_8 = 0;
  puVar7 = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    puVar7 = *(ushort **)param_2;
  }
  uVar6 = 0;
  uVar11 = 0x811c9dc5;
  if (*(int *)(param_2 + 8) * 2 != 0) {
    do {
      pbVar1 = (byte *)((int)puVar7 + uVar6);
      uVar6 = uVar6 + 1;
      uVar11 = (*pbVar1 ^ uVar11) * 0x1000193;
    } while (uVar6 < (uint)(*(int *)(param_2 + 8) * 2));
  }
  piVar9 = (int *)((int)this + 4);
  iVar10 = (*(uint *)((int)this + 0x18) & uVar11) * 8;
  iVar2 = *(int *)(*(int *)((int)this + 0xc) + iVar10);
  if (iVar2 == *piVar9) {
    iVar3 = *piVar9;
  }
  else {
    iVar3 = **(int **)(*(int *)((int)this + 0xc) + 4 + iVar10);
  }
  do {
    if (iVar3 == iVar2) {
      param_2 = (ushort *)param_3;
      iVar2 = *param_3;
      ExceptionList = &local_10;
      if (iVar3 != iVar2) {
        ExceptionList = &local_10;
        *(int *)param_3[1] = iVar2;
        **(int **)(iVar2 + 4) = iVar3;
        **(undefined4 **)(iVar3 + 4) = param_3;
        iVar8 = *(int *)(iVar3 + 4);
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar2 + 4);
        *(int *)(iVar2 + 4) = param_3[1];
        param_3[1] = iVar8;
      }
      piVar9 = (int *)(iVar10 + *(int *)((int)this + 0xc));
      if (*piVar9 == *(int *)((int)this + 4)) {
        *piVar9 = (int)param_3;
        *(int **)(*(int *)((int)this + 0xc) + 4 + iVar10) = param_3;
      }
      else if (*piVar9 == iVar3) {
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
      FUN_00450b30(this);
      *param_1 = (int)piVar5;
      *(undefined1 *)(param_1 + 1) = 1;
      ExceptionList = local_10;
      return;
    }
    iVar3 = *(int *)(iVar3 + 4);
    puVar7 = (ushort *)(iVar3 + 8);
    if (7 < *(uint *)(iVar3 + 0x1c)) {
      puVar7 = *(ushort **)puVar7;
    }
    puVar12 = param_2;
    if (7 < *(uint *)(param_2 + 10)) {
      puVar12 = *(ushort **)param_2;
    }
    uVar6 = *(uint *)(iVar3 + 0x18);
    if (*(uint *)(param_2 + 8) < uVar6) {
      uVar6 = *(uint *)(param_2 + 8);
    }
    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
      if (*puVar12 != *puVar7) {
        iVar8 = (-(uint)(*puVar12 < *puVar7) & 0xfffffffe) + 1;
        goto LAB_0044fa61;
      }
      puVar12 = puVar12 + 1;
      puVar7 = puVar7 + 1;
    }
    iVar8 = 0;
LAB_0044fa61:
    if (iVar8 == 0) {
      uVar6 = *(uint *)(iVar3 + 0x18);
      if ((uVar6 <= *(uint *)(param_2 + 8)) && (*(uint *)(param_2 + 8) <= uVar6)) {
        ExceptionList = &local_10;
        FUN_0043e7b0(piVar9,(int *)&param_2,param_3);
        *param_1 = iVar3;
        *(undefined1 *)(param_1 + 1) = 0;
        ExceptionList = local_10;
        return;
      }
    }
  } while( true );
}


