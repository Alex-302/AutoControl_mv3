// FUN_00402490 @ 00402490 size=72 callers=2

void * __thiscall FUN_00402490(void *this,undefined4 *param_1)

{
  undefined4 *local_8;
  undefined1 local_4;
  
  if (0xf < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  local_4 = 1;
  local_8 = param_1;
  ___std_exception_copy(&local_8,(undefined4 *)((int)this + 4));
  *(undefined ***)this = &PTR_FUN_0048eee8;
  return this;
}


