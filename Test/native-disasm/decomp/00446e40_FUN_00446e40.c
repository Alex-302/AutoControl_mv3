// FUN_00446e40 @ 00446e40 size=147 callers=2

int __thiscall FUN_00446e40(void *this,undefined4 param_1,undefined4 param_2)

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
  FUN_0044a060(local_6c,(int)this + 4,param_1,param_2);
  local_8 = 0;
  iVar3 = FUN_0044a140(local_6c);
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


