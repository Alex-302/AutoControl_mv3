// FUN_0043bde0 @ 0043bde0 size=97 callers=1

void * __thiscall FUN_0043bde0(void *this,byte param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0043b250((int)this);
  local_8 = 0;
  *(undefined ***)this = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(this);
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4((void *)((int)this + -0x68));
  }
  ExceptionList = local_10;
  return (void *)((int)this + -0x68);
}


