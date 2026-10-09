// FUN_004030f0 @ 004030f0 size=159 callers=1

void __fastcall FUN_004030f0(void *param_1)

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
  *(undefined4 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 8) = 0;
  *(undefined4 *)((int)param_1 + 0x10) = 0;
  *(undefined4 *)((int)param_1 + 0x14) = 0x201;
  *(undefined4 *)((int)param_1 + 0x18) = 6;
  *(undefined4 *)((int)param_1 + 0x1c) = 0;
  *(undefined4 *)((int)param_1 + 0x20) = 0;
  *(undefined4 *)((int)param_1 + 0x24) = 0;
  *(undefined4 *)((int)param_1 + 0x28) = 0;
  *(undefined4 *)((int)param_1 + 0x2c) = 0;
  FUN_00402f00(param_1,0,'\0');
  pvVar1 = operator_new(8);
  local_8 = 0;
  p_Var2 = std::locale::_Init(true);
  *(_Locimp **)((int)pvVar1 + 4) = p_Var2;
  *(void **)((int)param_1 + 0x30) = pvVar1;
  ExceptionList = local_10;
  return;
}


