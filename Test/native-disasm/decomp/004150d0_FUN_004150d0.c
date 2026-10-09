// FUN_004150d0 @ 004150d0 size=203 callers=1

undefined4 __thiscall FUN_004150d0(void *this,int *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a2de;
  local_10 = ExceptionList;
  puVar1 = (undefined4 *)((int)this + 0x10);
  if (((*(int *)((int)this + 0x10) == 0) || (*param_1 != *(int *)((int)this + 0x48))) ||
     (param_1[1] != *(int *)((int)this + 0x4c))) {
    ExceptionList = &local_10;
    *(int *)((int)this + 0x48) = *param_1;
    *(int *)((int)this + 0x4c) = param_1[1];
    puVar4 = FUN_0040b650(&local_14,this,(int *)((int)this + 0x48));
    local_8 = 0;
    puVar4 = FUN_00441b70(&param_1,puVar4);
    if (puVar1 != puVar4) {
      uVar2 = *puVar4;
      *puVar4 = 0;
      piVar3 = (int *)*puVar1;
      *puVar1 = uVar2;
      if (piVar3 != (int *)0x0) {
        FUN_004151a0(piVar3);
        FUN_0045a6a4(piVar3);
      }
    }
    piVar3 = param_1;
    if (param_1 != (int *)0x0) {
      FUN_004151a0(param_1);
      FUN_0045a6a4(piVar3);
    }
    local_8 = 1;
    if (local_14 != (int *)0x0) {
      (**(code **)(*local_14 + 8))(local_14);
    }
  }
  ExceptionList = local_10;
  return *puVar1;
}


