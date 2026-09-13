// FUN_0044b120 @ 0044b120 size=103 callers=1

void * __thiscall FUN_0044b120(void *this,int *param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e658;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  uVar1 = FUN_00449130();
  *(undefined4 *)this = uVar1;
  local_8 = 1;
  FUN_004504c0(this,param_1,param_1);
  ExceptionList = local_10;
  return this;
}


