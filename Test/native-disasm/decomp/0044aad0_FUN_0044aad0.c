// FUN_0044aad0 @ 0044aad0 size=361 callers=10

void __thiscall FUN_0044aad0(void *this,int *param_1,byte *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e640;
  local_10 = ExceptionList;
  local_8 = 0;
  uVar5 = *(uint *)((int)this + 0x18) &
          ((((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 ^ (uint)param_2[2])
           * 0x1000193 ^ (uint)param_2[3]) * 0x1000193;
  iVar2 = *(int *)(*(int *)((int)this + 0xc) + uVar5 * 8);
  iVar1 = uVar5 * 8;
  if (iVar2 == *(int *)((int)this + 4)) {
    iVar7 = *(int *)((int)this + 4);
  }
  else {
    iVar7 = **(int **)(*(int *)((int)this + 0xc) + 4 + iVar1);
  }
  if (iVar7 != iVar2) {
    do {
      iVar7 = *(int *)(iVar7 + 4);
      if (*(int *)param_2 == *(int *)(iVar7 + 8)) {
        ExceptionList = &local_10;
        *(int *)param_3[1] = *param_3;
        *(int *)(*param_3 + 4) = param_3[1];
        *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
        FID_conflict__free(param_3);
        *param_1 = iVar7;
        *(undefined1 *)(param_1 + 1) = 0;
        ExceptionList = local_10;
        return;
      }
    } while (iVar7 != iVar2);
  }
  iVar2 = *param_3;
  ExceptionList = &local_10;
  if (iVar7 != iVar2) {
    ExceptionList = &local_10;
    *(int *)param_3[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar7;
    **(undefined4 **)(iVar7 + 4) = param_3;
    iVar3 = *(int *)(iVar7 + 4);
    *(undefined4 *)(iVar7 + 4) = *(undefined4 *)(iVar2 + 4);
    *(int *)(iVar2 + 4) = param_3[1];
    param_3[1] = iVar3;
  }
  piVar6 = (int *)(*(int *)((int)this + 0xc) + iVar1);
  if (*piVar6 == *(int *)((int)this + 4)) {
    *piVar6 = (int)param_3;
    *(int **)(*(int *)((int)this + 0xc) + 4 + iVar1) = param_3;
  }
  else if (*piVar6 == iVar7) {
    *piVar6 = (int)param_3;
  }
  else {
    piVar4 = *(int **)piVar6[1];
    piVar6[1] = (int)piVar4;
    if (piVar4 != param_3) {
      *(undefined4 *)(*(int *)((int)this + 0xc) + 4 + iVar1) =
           *(undefined4 *)(*(int *)(*(int *)((int)this + 0xc) + 4 + iVar1) + 4);
    }
  }
  local_8 = 2;
  FUN_0044d830(this);
  *param_1 = (int)param_3;
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  return;
}


