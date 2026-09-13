// FUN_0042c270 @ 0042c270 size=295 callers=1

undefined1 * __cdecl FUN_0042c270(undefined1 *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  char *extraout_ECX;
  uint uVar3;
  undefined **local_64;
  undefined1 *local_60;
  char **local_5c;
  undefined ***local_40;
  char local_3c [16];
  char local_2c [8];
  undefined8 local_24;
  char *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047ccf9;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = 0;
  cVar1 = *param_2;
  if (((cVar1 == '\x05') || (cVar1 == '\x06')) || (cVar1 == '\a')) {
    ExceptionList = &local_10;
    pcVar2 = FUN_00434940(local_3c,param_2);
    local_8 = 1;
    uVar3 = 1;
  }
  else {
    local_2c[0] = '\0';
    local_24 = 0;
    ExceptionList = &local_10;
    FUN_00450f50(local_2c,0);
    local_8 = 2;
    uVar3 = 2;
    pcVar2 = extraout_ECX;
  }
  local_14 = uVar3;
  FUN_00453810(pcVar2,(uint *)&param_2);
  local_18 = param_2;
  if ((uVar3 & 2) != 0) {
    uVar3 = uVar3 & 0xfffffffd;
    local_14 = uVar3;
    FUN_00434820(local_2c);
  }
  if ((uVar3 & 1) != 0) {
    uVar3 = uVar3 & 0xfffffffe;
    local_14 = uVar3;
    FUN_00434820(local_3c);
  }
  local_8 = 3;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  local_5c = &local_18;
  local_64 = &PTR_LAB_0048e870;
  local_14 = uVar3 | 4;
  local_40 = &local_64;
  local_60 = param_1;
  local_8 = 4;
  FUN_0040f7a0(DAT_004a23dc,(int *)local_40);
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])(local_40 != &local_64);
  }
  ExceptionList = local_10;
  return param_1;
}


