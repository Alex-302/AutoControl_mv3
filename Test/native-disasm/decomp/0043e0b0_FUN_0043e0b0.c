// FUN_0043e0b0 @ 0043e0b0 size=195 callers=28

void * __thiscall FUN_0043e0b0(void *this,undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;
  code *pcVar2;
  bool bVar3;
  uint uVar4;
  void *pvVar5;
  uint uVar6;
  longlong lVar7;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047deac;
  pvStack_10 = ExceptionList;
  uVar6 = 0;
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
  if (*(int *)(*(int *)(*(int *)this + 4) + 0xc + (int)this) == 0) {
    if ((-1 < param_3) && ((0 < param_3 || (param_2 != 0)))) {
      local_8 = 2;
      lVar7 = (**(code **)(**(int **)(*(int *)(*(int *)this + 4) + 0x38 + (int)this) + 0x24))
                        (param_1,param_2,param_3);
      if (lVar7 != CONCAT44(param_3,param_2)) {
        pvVar5 = (void *)FUN_0043e1a3();
        return pvVar5;
      }
    }
  }
  else {
    uVar6 = 4;
  }
  local_8 = 1;
  pvVar5 = (void *)(*(int *)(*(int *)this + 4) + (int)this);
  if (uVar6 != 0) {
    uVar6 = *(uint *)((int)pvVar5 + 0xc) | uVar6;
    uVar4 = uVar6 | 4;
    if (*(int *)((int)pvVar5 + 0x38) != 0) {
      uVar4 = uVar6;
    }
    FUN_00402f00(pvVar5,uVar4,'\0');
  }
  local_8 = 4;
  bVar3 = thunk_FUN_0045c732();
  if (!bVar3) {
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


