// FUN_00435950 @ 00435950 size=85 callers=1

void * __thiscall FUN_00435950(void *this,byte param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  *(undefined ***)this = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(this);
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  ExceptionList = local_10;
  return this;
}


