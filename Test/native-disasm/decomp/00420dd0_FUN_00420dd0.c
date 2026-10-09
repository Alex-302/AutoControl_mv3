// FUN_00420dd0 @ 00420dd0 size=150 callers=1

void __fastcall FUN_00420dd0(ushort *param_1)

{
  ushort uVar1;
  undefined **local_38;
  undefined1 local_34;
  undefined ***local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aba8;
  local_10 = ExceptionList;
  uVar1 = *param_1;
  ExceptionList = &local_10;
  if (uVar1 != 0) {
    ExceptionList = &local_10;
    DAT_004a26b4 = GetTickCount();
    FUN_00413390((uint)uVar1,'\x01');
  }
  local_34 = DAT_0049fc44;
  local_14 = &local_38;
  local_38 = &PTR_LAB_0048ed80;
  local_8 = 0;
  FUN_0040f6b0(DAT_004a23dc,(int *)local_14,0);
  if (local_14 != (undefined ***)0x0) {
    (*(code *)(*local_14)[4])(local_14 != &local_38);
  }
  DAT_0049fc44 = 0;
  ExceptionList = local_10;
  return;
}


