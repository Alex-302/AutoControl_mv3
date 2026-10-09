// FUN_00435790 @ 00435790 size=48 callers=0

void * __thiscall FUN_00435790(void *this,int param_1)

{
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy((undefined4 *)(param_1 + 4),(undefined4 *)((int)this + 4));
  *(undefined ***)this = std::logic_error::vftable;
  return this;
}


