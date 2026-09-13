// FUN_00442200 @ 00442200 size=289 callers=1

char * __thiscall
FUN_00442200(void *this,char *param_1,undefined4 *param_2,char param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  char *pcVar4;
  void *local_3c [2];
  int local_34 [2];
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined8 local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e108;
  local_10 = ExceptionList;
  local_14 = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  if (*(char *)this == '\x01') {
    local_28 = 0xf;
    local_2c = 0;
    local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
    ExceptionList = &local_10;
    FUN_0043ade0(local_3c,param_2,0,0xffffffff);
    FUN_004340a0(this,&local_24);
    if (*(char *)this == '\x01') {
      puVar2 = (undefined4 *)
               FUN_00432d50(*(void **)((int)this + 8),(int *)&param_2,(byte *)local_3c);
      local_20 = *puVar2;
    }
    if (0xf < local_28) {
      FUN_00402430(local_3c[0],local_28 + 1,1);
    }
    FUN_004340a0(this,local_34);
    uVar3 = FUN_004383a0(&local_24,local_34);
    if ((char)uVar3 == '\0') {
      pcVar4 = FUN_00433bc0(&local_24);
      FUN_00434940(param_1,pcVar4);
      FUN_00434820(&param_3);
      ExceptionList = local_10;
      return param_1;
    }
  }
  uVar1 = param_6;
  uVar3 = param_5;
  local_1c = 0;
  *param_1 = param_3;
  param_5 = 0;
  *(undefined4 *)(param_1 + 8) = uVar3;
  param_6 = 0;
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  param_3 = '\0';
  FUN_00434820(&param_3);
  ExceptionList = local_10;
  return param_1;
}


