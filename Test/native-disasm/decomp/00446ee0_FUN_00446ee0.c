// FUN_00446ee0 @ 00446ee0 size=349 callers=2

void __thiscall FUN_00446ee0(void *this,int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar4 = param_3;
  puStack_c = &LAB_0047e480;
  local_10 = ExceptionList;
  local_8 = 0;
  piVar1 = (int *)((int)this + 4);
  pbVar5 = (byte *)((*(uint *)((int)this + 0x18) &
                    ((((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 ^
                     (uint)param_2[2]) * 0x1000193 ^ (uint)param_2[3]) * 0x1000193) * 8);
  iVar2 = *(int *)(pbVar5 + *(int *)((int)this + 0xc));
  if (iVar2 == *piVar1) {
    iVar7 = *piVar1;
  }
  else {
    iVar7 = **(int **)(pbVar5 + *(int *)((int)this + 0xc) + 4);
  }
  if (iVar7 != iVar2) {
    do {
      iVar7 = *(int *)(iVar7 + 4);
      if (*(int *)param_2 == *(int *)(iVar7 + 8)) {
        ExceptionList = &local_10;
        param_2 = pbVar5;
        FUN_00448c60(piVar1,(int *)&param_2,param_3);
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
  pbVar6 = pbVar5 + *(int *)((int)this + 0xc);
  if (*(int *)pbVar6 == *(int *)((int)this + 4)) {
    *(int **)pbVar6 = param_3;
    *(int **)(pbVar5 + *(int *)((int)this + 0xc) + 4) = param_3;
  }
  else if (*(int *)pbVar6 == iVar7) {
    *(int **)pbVar6 = param_3;
  }
  else {
    piVar1 = (int *)**(int **)(pbVar6 + 4);
    *(int **)(pbVar6 + 4) = piVar1;
    if (piVar1 != param_3) {
      *(undefined4 *)(pbVar5 + *(int *)((int)this + 0xc) + 4) =
           *(undefined4 *)(*(int *)(pbVar5 + *(int *)((int)this + 0xc) + 4) + 4);
    }
  }
  local_8 = 2;
  param_2 = pbVar5;
  FUN_00448680(this);
  *param_1 = (int)piVar4;
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  return;
}


