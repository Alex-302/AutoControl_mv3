// FUN_00442790 @ 00442790 size=149 callers=1

int __thiscall FUN_00442790(void *this,undefined4 param_1,undefined4 param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_6c [5];
  void *local_58;
  int local_50;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e148;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00447460(local_6c,(int)this + 4,param_1,param_2,param_3);
  local_8 = 0;
  iVar3 = FUN_00447590(local_6c);
  if (iVar3 != 0) {
    LOCK();
    *(int *)(iVar3 + 0x20) = *(int *)(iVar3 + 0x20) + 1;
    UNLOCK();
  }
  iVar4 = iVar3;
  if (*(int *)this != 0) {
    LOCK();
    piVar1 = (int *)(*(int *)this + 0x20);
    iVar2 = *piVar1;
    iVar4 = *piVar1;
    *piVar1 = iVar2 + -1;
    UNLOCK();
    if (iVar2 + -1 == 0) {
      iVar4 = FUN_004033e0(*(undefined4 **)this,(undefined4 *)0x0);
    }
  }
  *(int *)this = iVar3;
  if (local_58 != (void *)0x0) {
    iVar4 = FUN_00402430(local_58,local_50 - (int)local_58 >> 2,4);
  }
  ExceptionList = local_10;
  return iVar4;
}


