// FUN_004429e0 @ 004429e0 size=132 callers=2

undefined4 * __fastcall FUN_004429e0(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e199;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = operator_new(0xc);
  local_8 = 1;
  if (this != (undefined4 *)0x0) {
    iVar1 = param_1[1];
    iVar2 = *param_1;
    *this = 0;
    this[1] = 0;
    this[2] = 0;
    FUN_00450400(this,iVar2,iVar1);
  }
  ExceptionList = local_10;
  return this;
}


