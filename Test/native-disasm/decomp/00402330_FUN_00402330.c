// FUN_00402330 @ 00402330 size=45 callers=7

void * __thiscall FUN_00402330(void *this,byte param_1)

{
  *(undefined ***)this = std::exception::vftable;
  ___std_exception_destroy((undefined4 *)((int)this + 4));
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


