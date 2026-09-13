// FUN_00440aa0 @ 00440aa0 size=272 callers=1

int * __thiscall
FUN_00440aa0(void *this,int *param_1,undefined4 *param_2,void *param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  char *this_00;
  int *piVar3;
  void *local_40 [2];
  int local_38 [2];
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047dfc8;
  local_10 = ExceptionList;
  local_18 = 0;
  local_8 = 0;
  if (*(char *)this == '\x01') {
    local_2c = 0xf;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
    ExceptionList = &local_10;
    FUN_0043ade0(local_40,param_2,0,0xffffffff);
    FUN_004340a0(this,&local_28);
    if (*(char *)this == '\x01') {
      puVar1 = (undefined4 *)
               FUN_00432d50(*(void **)((int)this + 8),(int *)&param_2,(byte *)local_40);
      local_24 = *puVar1;
    }
    if (0xf < local_2c) {
      FUN_00402430(local_40[0],local_2c + 1,1);
    }
    FUN_004340a0(this,local_38);
    uVar2 = FUN_004383a0(&local_28,local_38);
    if ((char)uVar2 == '\0') {
      piVar3 = param_1;
      this_00 = FUN_00433bc0(&local_28);
      FUN_004466d0(this_00,piVar3);
      if (param_3 != (void *)0x0) {
        FUN_00402430(param_3,param_5 - (int)param_3,1);
      }
      ExceptionList = local_10;
      return param_1;
    }
  }
  *param_1 = (int)param_3;
  param_1[1] = param_4;
  param_1[2] = param_5;
  ExceptionList = local_10;
  return param_1;
}


