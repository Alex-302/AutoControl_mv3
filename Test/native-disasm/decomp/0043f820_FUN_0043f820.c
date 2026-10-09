// FUN_0043f820 @ 0043f820 size=171 callers=1

undefined4 * __fastcall FUN_0043f820(undefined4 *param_1)

{
  void *pvVar1;
  _Locimp *p_Var2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_0048e3e8;
  pvVar1 = operator_new(8);
  local_8 = 0;
  p_Var2 = std::locale::_Init(true);
  *(_Locimp **)((int)pvVar1 + 4) = p_Var2;
  param_1[0xd] = pvVar1;
  param_1[3] = param_1 + 1;
  param_1[4] = param_1 + 2;
  param_1[7] = param_1 + 5;
  param_1[8] = param_1 + 6;
  param_1[0xb] = param_1 + 9;
  param_1[0xc] = param_1 + 10;
  param_1[2] = 0;
  *(undefined4 *)param_1[8] = 0;
  *(undefined4 *)param_1[0xc] = 0;
  *(undefined4 *)param_1[3] = 0;
  *(undefined4 *)param_1[7] = 0;
  *(undefined4 *)param_1[0xb] = 0;
  ExceptionList = local_10;
  return param_1;
}


