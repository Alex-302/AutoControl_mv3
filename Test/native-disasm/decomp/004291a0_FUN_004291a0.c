// FUN_004291a0 @ 004291a0 size=474 callers=1

undefined1 * __cdecl FUN_004291a0(undefined1 *param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  void *local_3c [4];
  undefined4 local_2c;
  uint local_28;
  char local_24 [8];
  undefined8 local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c88e;
  local_10 = ExceptionList;
  local_14 = 0;
  local_28 = 0xf;
  local_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_3c,(uint *)"ignInjInp",9);
  pcVar2 = param_2;
  if (*param_2 == '\x01') {
    FUN_004437f0(*(void **)(param_2 + 8),(int *)&local_1c,(byte *)local_3c);
    iVar1 = FUN_00447a70((int *)local_1c,local_1c._4_4_);
  }
  else {
    iVar1 = 0;
  }
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  if (iVar1 == 0) goto LAB_00429350;
  pcVar2 = (char *)FUN_00440e70(pcVar2,(uint *)"ignInjInp");
  param_2 = "kbd";
  local_8 = 0;
  local_24[0] = '\0';
  local_1c = 0;
  FUN_00451340(local_24,&param_2);
  uVar3 = FUN_004441e0(pcVar2,local_24);
  FUN_00434820(local_24);
  if ((char)uVar3 == '\0') {
    param_2 = "all";
    local_8 = 1;
    local_1c = 0;
    local_24[0] = (char)uVar3;
    FUN_00451340(local_24,&param_2);
    uVar3 = FUN_004441e0(pcVar2,local_24);
    FUN_00434820(local_24);
    DAT_004a2425 = 0;
    if ((char)uVar3 != '\0') goto LAB_004292c2;
  }
  else {
LAB_004292c2:
    DAT_004a2425 = 1;
  }
  param_2 = "mse";
  local_8 = 2;
  local_24[0] = '\0';
  local_1c = 0;
  FUN_00451340(local_24,&param_2);
  uVar3 = FUN_004441e0(pcVar2,local_24);
  FUN_00434820(local_24);
  if ((char)uVar3 == '\0') {
    param_2 = "all";
    local_8 = 3;
    local_1c = 0;
    local_24[0] = (char)uVar3;
    FUN_00451340(local_24,&param_2);
    uVar3 = FUN_004441e0(pcVar2,local_24);
    FUN_00434820(local_24);
    DAT_004a2424 = 0;
    if ((char)uVar3 == '\0') goto LAB_00429350;
  }
  DAT_004a2424 = 1;
LAB_00429350:
  local_8 = 4;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


