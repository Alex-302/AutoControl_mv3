// FUN_00443b50 @ 00443b50 size=48 callers=0

void * __thiscall FUN_00443b50(void *this,int param_1)

{
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  ___std_exception_copy((undefined4 *)(param_1 + 4),(undefined4 *)((int)this + 4));
  *(undefined ***)this = std::bad_cast::vftable;
  return this;
}


