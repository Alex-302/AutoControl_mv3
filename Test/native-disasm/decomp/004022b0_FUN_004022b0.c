// FUN_004022b0 @ 004022b0 size=58 callers=2

void * __thiscall FUN_004022b0(void *this,undefined4 param_1)

{
  undefined4 local_8;
  undefined1 local_4;
  
  local_8 = param_1;
  local_4 = 1;
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy(&local_8,(undefined4 *)((int)this + 4));
  return this;
}


