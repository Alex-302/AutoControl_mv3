// FUN_00402e00 @ 00402e00 size=45 callers=1

void * __thiscall FUN_00402e00(void *this,byte param_1)

{
  *(undefined ***)this = std::exception::vftable;
  ___std_exception_destroy((undefined4 *)((int)this + 4));
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


