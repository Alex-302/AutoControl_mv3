// FUN_0047ee60 @ 0047ee60 size=115 callers=1

void * FUN_0047ee60(void)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *puVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  pvVar3 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_004a275c != (undefined4 *)0x0) {
    LOCK();
    piVar1 = DAT_004a275c + 8;
    iVar2 = *piVar1;
    pvVar3 = (void *)*piVar1;
    ExceptionList = &local_10;
    *piVar1 = iVar2 + -1;
    UNLOCK();
    if (iVar2 + -1 == 0) {
      pvVar3 = (void *)FUN_004033e0(DAT_004a275c,(undefined4 *)0x0);
    }
  }
  DAT_004a275c = (undefined4 *)0x0;
  local_8 = 0;
  if (DAT_004a276c != (int *)0x0) {
    puVar4 = (undefined4 *)(**(code **)(*DAT_004a276c + 8))();
    pvVar3 = (void *)0x0;
    if (puVar4 != (undefined4 *)0x0) {
      pvVar3 = (void *)(**(code **)*puVar4)(1);
    }
  }
  ExceptionList = local_10;
  return pvVar3;
}


