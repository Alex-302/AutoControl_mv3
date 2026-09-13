// FUN_00402d50 @ 00402d50 size=174 callers=3

void * __thiscall FUN_00402d50(void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint *extraout_EDX;
  uint in_stack_ffffffc0;
  void *pvVar1;
  undefined4 *local_20;
  undefined1 local_1c;
  void *local_18 [5];
  uint local_4;
  
  pvVar1 = (void *)(in_stack_ffffffc0 & 0xffffff00);
  local_20 = this;
  FUN_0043ade0(&stack0xffffffc0,param_1,0,0xffffffff);
  local_20 = (undefined4 *)FUN_00402c90((undefined1 *)local_18,extraout_EDX,param_2,param_3,pvVar1);
  if (0xf < (uint)local_20[5]) {
    local_20 = (undefined4 *)*local_20;
  }
  *(undefined ***)this = std::exception::vftable;
  *(undefined8 *)((int)this + 4) = 0;
  local_1c = 1;
  ___std_exception_copy(&local_20,(undefined4 *)((int)this + 4));
  *(undefined ***)this = std::runtime_error::vftable;
  if (0xf < local_4) {
    FUN_00402430(local_18[0],local_4 + 1,1);
  }
  *(undefined4 *)((int)this + 0xc) = param_2;
  *(undefined4 *)((int)this + 0x10) = param_3;
  *(undefined ***)this = &PTR_FUN_0048f208;
  return this;
}


