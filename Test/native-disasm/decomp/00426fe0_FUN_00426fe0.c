// FUN_00426fe0 @ 00426fe0 size=200 callers=1

void * __cdecl FUN_00426fe0(void *param_1,undefined4 param_2)

{
  undefined **local_44;
  void *local_40;
  undefined4 local_3c;
  undefined ***local_20;
  void *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047c5e1;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  local_8 = 0;
  local_14 = 1;
  local_1c = param_1;
  local_18 = param_2;
  if (DAT_004a23d6 != '\0') {
    FUN_004270b0(&local_1c);
    ExceptionList = local_10;
    return param_1;
  }
  local_3c = param_2;
  local_20 = &local_44;
  local_44 = &PTR_LAB_0048eae0;
  local_40 = param_1;
  local_8 = 1;
  FUN_0040f7a0(DAT_004a23dc,(int *)local_20);
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])(local_20 != &local_44);
  }
  ExceptionList = local_10;
  return param_1;
}


