// FUN_00402500 @ 00402500 size=64 callers=2

void * __thiscall FUN_00402500(void *this,undefined4 param_1)

{
  undefined4 local_8;
  undefined1 local_4;
  
  local_8 = param_1;
  local_4 = 1;
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy(&local_8,(undefined4 *)((int)this + 4));
  *(undefined ***)this = std::invalid_argument::vftable;
  return this;
}


