// FUN_0043e220 @ 0043e220 size=234 callers=18

void * __thiscall FUN_0043e220(void *this,byte param_1)

{
  int *piVar1;
  code *pcVar2;
  byte *pbVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  void *pvVar7;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dedc;
  pvStack_10 = ExceptionList;
  piVar1 = *(int **)(*(int *)(*(int *)this + 4) + 0x38 + (int)this);
  ExceptionList = &pvStack_10;
  if ((piVar1 != (int *)0x0) &&
     (pcVar2 = *(code **)(*piVar1 + 4), ExceptionList = &pvStack_10, pcVar2 != guard_check_icall)) {
    ExceptionList = &pvStack_10;
    (*pcVar2)();
  }
  local_8 = 0;
  if (((*(int *)(*(int *)(*(int *)this + 4) + 0xc + (int)this) == 0) &&
      (piVar1 = *(int **)(*(int *)(*(int *)this + 4) + 0x3c + (int)this), piVar1 != (int *)0x0)) &&
     (piVar1 != this)) {
    FUN_00440030(piVar1);
  }
  local_8 = 1;
  if (*(int *)(*(int *)(*(int *)this + 4) + 0xc + (int)this) == 0) {
    local_8 = 2;
    piVar1 = *(int **)(*(int *)(*(int *)this + 4) + 0x38 + (int)this);
    if (*(int *)piVar1[8] != 0) {
      iVar5 = *(int *)piVar1[0xc];
      if (0 < iVar5) {
        *(int *)piVar1[0xc] = iVar5 + -1;
        pbVar3 = *(byte **)piVar1[8];
        *(byte **)piVar1[8] = pbVar3 + 1;
        uVar6 = 4;
        *pbVar3 = param_1;
        if (param_1 != 0xffffffff) {
          uVar6 = 0;
        }
        pvVar7 = (void *)FUN_0043e33a(uVar6);
        return pvVar7;
      }
    }
    iVar5 = (**(code **)(*piVar1 + 0xc))(param_1);
    uVar6 = 4;
    if (iVar5 != -1) {
      uVar6 = 0;
    }
    pvVar7 = (void *)FUN_0043e33a(uVar6);
    return pvVar7;
  }
  pvVar7 = (void *)(*(int *)(*(int *)this + 4) + (int)this);
  FUN_00402f00(pvVar7,*(uint *)((int)pvVar7 + 0xc) | 4,'\0');
  local_8 = 4;
  bVar4 = thunk_FUN_0045c732();
  if (!bVar4) {
    FUN_00440100(this);
  }
  local_8 = CONCAT31(local_8._1_3_,5);
  piVar1 = *(int **)(*(int *)(*(int *)this + 4) + 0x38 + (int)this);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    (*pcVar2)();
  }
  ExceptionList = pvStack_10;
  return this;
}


