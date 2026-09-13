// FUN_00441760 @ 00441760 size=168 callers=1

void * __thiscall FUN_00441760(void *this,undefined4 *param_1)

{
  int *piVar1;
  _Locimp *p_Var2;
  _Facet_base *p_Var3;
  undefined4 *puVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047d9bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  local_8 = 0;
  p_Var2 = std::locale::_Init(true);
  *(_Locimp **)((int)this + 0x10) = p_Var2;
  local_8 = 1;
  p_Var3 = FUN_004436c0((void *)((int)this + 0xc));
  *(_Facet_base **)((int)this + 4) = p_Var3;
  p_Var3 = FUN_00440660((int)this + 0xc);
  *(_Facet_base **)((int)this + 8) = p_Var3;
  local_8 = 2;
  puVar4 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar4 = (undefined4 *)*param_1;
  }
  piVar1 = param_1 + 4;
  if (0xf < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  FUN_00446e40(this,param_1,*piVar1 + (int)puVar4);
  ExceptionList = local_10;
  return this;
}


