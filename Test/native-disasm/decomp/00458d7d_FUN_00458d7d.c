// FUN_00458d7d @ 00458d7d size=45 callers=1

void * __thiscall FUN_00458d7d(void *this,byte param_1)

{
  *(undefined ***)this = std::exception::vftable;
  ___std_exception_destroy((undefined4 *)((int)this + 4));
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


