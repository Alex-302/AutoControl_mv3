// FUN_004405c0 @ 004405c0 size=147 callers=1

char * __fastcall FUN_004405c0(void *param_1)

{
  int iVar1;
  _Facet_base *p_Var2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined1 local_1c [4];
  int *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047df8e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_004030a0(param_1,(int)local_1c);
  local_8 = 0;
  p_Var2 = FUN_00440660(iVar1);
  local_8 = 1;
  if (local_18 != (int *)0x0) {
    puVar3 = (undefined4 *)(**(code **)(*local_18 + 8))();
    if (puVar3 != (undefined4 *)0x0) {
      (**(code **)*puVar3)(1);
    }
  }
  local_8 = 0xffffffff;
  if (*(undefined ***)p_Var2 == std::ctype<char>::vftable) {
    ExceptionList = local_10;
    return "usy";
  }
  pcVar4 = (char *)(*(code *)(*(undefined ***)p_Var2)[8])(0x20);
  ExceptionList = local_10;
  return pcVar4;
}


