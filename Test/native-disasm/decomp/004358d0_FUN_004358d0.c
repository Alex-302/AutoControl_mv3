// FUN_004358d0 @ 004358d0 size=114 callers=1

int * __thiscall FUN_004358d0(void *this,byte param_1)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  piVar1 = (int *)((int)this + -0x18);
  ExceptionList = &local_10;
  *(undefined ***)(*(int *)(*(int *)((int)this + -0x18) + 4) + -0x18 + (int)this) =
       &PTR_LAB_0048ec6c;
  *(int *)(*(int *)(*piVar1 + 4) + -0x1c + (int)this) = *(int *)(*piVar1 + 4) + -0x18;
  local_8 = 0;
  *(undefined ***)this = &PTR_FUN_0048e580;
  std::ios_base::_Ios_base_dtor(this);
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(piVar1);
  }
  ExceptionList = local_10;
  return piVar1;
}


