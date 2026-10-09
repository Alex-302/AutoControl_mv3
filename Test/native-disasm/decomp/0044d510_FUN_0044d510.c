// FUN_0044d510 @ 0044d510 size=77 callers=1

void * __thiscall FUN_0044d510(void *this,void *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e6d1;
  local_10 = ExceptionList;
  local_8 = 0;
  if (param_1 != (void *)0x0) {
    ExceptionList = &local_10;
    FUN_00456100(param_1,(int *)((int)this + 8));
  }
  ExceptionList = local_10;
  return param_1;
}


