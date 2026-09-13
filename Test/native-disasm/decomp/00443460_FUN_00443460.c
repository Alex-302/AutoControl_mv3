// FUN_00443460 @ 00443460 size=573 callers=2

void __thiscall FUN_00443460(void *this,int *param_1,byte *param_2,int *param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  uint *puVar6;
  uint uVar7;
  int *_Memory;
  byte *pbVar8;
  undefined1 *puVar9;
  uint uVar10;
  int iVar11;
  float fVar12;
  int local_1c;
  void *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  _Memory = param_3;
  puStack_c = &LAB_0047e210;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = &stack0xffffffd4;
  pbVar1 = (byte *)((int)this + 0xc);
  uVar10 = ((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 &
           *(uint *)((int)this + 0x18);
  iVar2 = *(int *)(*(int *)((int)this + 0xc) + uVar10 * 8);
  if (iVar2 == *(int *)((int)this + 4)) {
    iVar11 = *(int *)((int)this + 4);
  }
  else {
    iVar11 = **(int **)(*(int *)((int)this + 0xc) + 4 + uVar10 * 8);
  }
  local_18 = this;
  if (iVar11 != iVar2) {
    do {
      iVar11 = *(int *)(iVar11 + 4);
      if (*(short *)param_2 == *(short *)(iVar11 + 8)) {
        ExceptionList = &local_10;
        *(int *)param_3[1] = *param_3;
        *(int *)(*param_3 + 4) = param_3[1];
        *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
        pvVar4 = (void *)param_3[3];
        param_2 = pbVar1;
        puVar9 = &stack0xffffffd4;
        if (pvVar4 != (void *)0x0) {
          FUN_00402430(pvVar4,param_3[5] - (int)pvVar4 >> 1,2);
          _Memory[3] = 0;
          _Memory[4] = 0;
          _Memory[5] = 0;
          puVar9 = local_14;
        }
        local_14 = puVar9;
        FID_conflict__free(_Memory);
        *param_1 = iVar11;
        *(undefined1 *)(param_1 + 1) = 0;
        ExceptionList = local_10;
        return;
      }
    } while (iVar11 != iVar2);
  }
  iVar2 = *param_3;
  ExceptionList = &local_10;
  if (iVar11 != iVar2) {
    ExceptionList = &local_10;
    *(int *)param_3[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar11;
    **(undefined4 **)(iVar11 + 4) = param_3;
    iVar3 = *(int *)(iVar11 + 4);
    *(undefined4 *)(iVar11 + 4) = *(undefined4 *)(iVar2 + 4);
    *(int *)(iVar2 + 4) = param_3[1];
    param_3[1] = iVar3;
  }
  local_1c = *(int *)pbVar1;
  param_2 = (byte *)((int)this + 0xc);
  if (*(int *)(local_1c + uVar10 * 8) == *(int *)((int)this + 4)) {
    *(int **)(local_1c + uVar10 * 8) = param_3;
    *(int **)(*(int *)param_2 + 4 + uVar10 * 8) = param_3;
  }
  else if (*(int *)(local_1c + uVar10 * 8) == iVar11) {
    *(int **)(local_1c + uVar10 * 8) = param_3;
  }
  else {
    piVar5 = (int *)**(int **)(local_1c + 4 + uVar10 * 8);
    *(int **)(local_1c + 4 + uVar10 * 8) = piVar5;
    if (piVar5 != param_3) {
      *(undefined4 *)(*(int *)param_2 + 4 + uVar10 * 8) =
           *(undefined4 *)(*(int *)(*(int *)param_2 + 4 + uVar10 * 8) + 4);
    }
  }
  local_8 = 2;
  uVar10 = *(uint *)((int)this + 0x1c);
  fVar12 = (float)((double)*(int *)((int)this + 8) +
                  (double)(&DAT_0048f2d0)[-(*(int *)((int)this + 8) >> 0x1f)]) /
           (float)((double)(int)uVar10 + (double)(&DAT_0048f2d0)[-((int)uVar10 >> 0x1f)]);
  if (*(float *)this <= fVar12 && fVar12 != *(float *)this) {
    if (uVar10 < 0x200) {
      uVar10 = uVar10 << 3;
    }
    else if (uVar10 < 0x1fffffff) {
      uVar10 = uVar10 * 2;
    }
    uVar7 = uVar10 * 2;
    local_14 = &stack0xffffffd4;
    if ((uint)(*(int *)((int)this + 0x14) - *(int *)param_2 >> 2) < uVar7) {
      if (0x3fffffff < uVar7) {
        param_2 = pbVar1;
        local_14 = &stack0xffffffd4;
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("vector<T> too long");
      }
      pbVar8 = param_2;
      param_2 = pbVar1;
      local_14 = &stack0xffffffd4;
      FUN_0043e4f0(pbVar8,uVar7);
    }
    pbVar1 = *(byte **)((int)local_18 + 4);
    *(int *)(param_2 + 4) = *(int *)param_2;
    puVar6 = *(uint **)param_2;
    pbVar8 = param_2;
    param_2 = pbVar1;
    FUN_0043fa20(pbVar8,&local_1c,puVar6,uVar7,&param_2);
    *(uint *)((int)local_18 + 0x18) = uVar10 - 1;
    *(uint *)((int)local_18 + 0x1c) = uVar10;
    FUN_0043c970(local_18);
  }
  *param_1 = (int)_Memory;
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  return;
}


