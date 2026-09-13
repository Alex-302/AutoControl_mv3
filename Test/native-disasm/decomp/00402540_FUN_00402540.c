// FUN_00402540 @ 00402540 size=72 callers=2

void * __thiscall FUN_00402540(void *this,undefined4 *param_1)

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
  *(undefined ***)this = std::out_of_range::vftable;
  return this;
}


