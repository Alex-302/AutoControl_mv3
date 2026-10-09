// FUN_004337d0 @ 004337d0 size=104 callers=6

void * __fastcall FUN_004337d0(int *param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *puVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  pvVar3 = ExceptionList;
  ExceptionList = &local_10;
  if (*param_1 != 0) {
    LOCK();
    piVar1 = (int *)(*param_1 + 0x20);
    iVar2 = *piVar1;
    pvVar3 = (void *)*piVar1;
    ExceptionList = &local_10;
    *piVar1 = iVar2 + -1;
    UNLOCK();
    if (iVar2 + -1 == 0) {
      pvVar3 = (void *)FUN_004033e0((undefined4 *)*param_1,(undefined4 *)0x0);
    }
  }
  *param_1 = 0;
  local_8 = 0;
  if ((int *)param_1[4] != (int *)0x0) {
    puVar4 = (undefined4 *)(**(code **)(*(int *)param_1[4] + 8))();
    pvVar3 = (void *)0x0;
    if (puVar4 != (undefined4 *)0x0) {
      pvVar3 = (void *)(**(code **)*puVar4)(1);
    }
  }
  ExceptionList = local_10;
  return pvVar3;
}


