// FUN_00443ec0 @ 00443ec0 size=173 callers=1

undefined4 __cdecl FUN_00443ec0(int *param_1,void *param_2)

{
  undefined4 *puVar1;
  char *pcVar2;
  _Collvec _Var3;
  _Locinfo local_60 [52];
  undefined4 local_2c [6];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e248;
  local_10 = ExceptionList;
  local_14 = 0;
  if ((param_1 != (int *)0x0) && (*param_1 == 0)) {
    ExceptionList = &local_10;
    puVar1 = operator_new(0x10);
    local_8 = 0;
    pcVar2 = FUN_00402840(param_2,(undefined1 *)local_2c);
    local_8 = CONCAT31(local_8._1_3_,1);
    local_14 = 1;
    if (0xf < *(uint *)(pcVar2 + 0x14)) {
      pcVar2 = *(char **)pcVar2;
    }
    FUN_004025d0(local_60,pcVar2);
    puVar1[1] = 0;
    *puVar1 = std::collate<char>::vftable;
    _Var3 = __Getcoll();
    *(_Collvec *)(puVar1 + 2) = _Var3;
    *param_1 = (int)puVar1;
    FUN_004026a0(local_60);
    FUN_004061c0(local_2c);
  }
  ExceptionList = local_10;
  return 1;
}


