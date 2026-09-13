// FUN_00402590 @ 00402590 size=64 callers=3

void * __thiscall FUN_00402590(void *this,undefined4 param_1)

{
  undefined4 local_8;
  undefined1 local_4;
  
  local_8 = param_1;
  local_4 = 1;
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy(&local_8,(undefined4 *)((int)this + 4));
  *(undefined ***)this = std::out_of_range::vftable;
  return this;
}


