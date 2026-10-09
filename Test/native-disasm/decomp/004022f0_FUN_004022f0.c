// FUN_004022f0 @ 004022f0 size=42 callers=6

void * __thiscall FUN_004022f0(void *this,int param_1)

{
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy((undefined4 *)(param_1 + 4),(undefined4 *)((int)this + 4));
  return this;
}


