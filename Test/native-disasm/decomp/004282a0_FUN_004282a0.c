// FUN_004282a0 @ 004282a0 size=110 callers=1

void __fastcall FUN_004282a0(undefined4 param_1,undefined1 param_2)

{
  undefined **local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined ***local_20;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  local_40 = local_14;
  local_3c = local_18;
  local_20 = &local_44;
  local_44 = &PTR_LAB_0048e5cc;
  local_8 = 0;
  ExceptionList = &local_10;
  local_18[0] = param_2;
  local_14[0] = (undefined1)param_1;
  FUN_00427e50((int)local_20);
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])(local_20 != &local_44);
  }
  ExceptionList = local_10;
  return;
}


