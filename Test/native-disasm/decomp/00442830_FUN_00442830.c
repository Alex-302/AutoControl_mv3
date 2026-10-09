// FUN_00442830 @ 00442830 size=267 callers=1

undefined4 * __thiscall
FUN_00442830(void *this,undefined4 *param_1,undefined4 *param_2,void *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  char *this_00;
  uint in_stack_00000020;
  void *local_3c [2];
  int local_34 [2];
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e168;
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
      puVar1 = (undefined4 *)
               FUN_00432d50(*(void **)((int)this + 8),(int *)&param_2,(byte *)local_3c);
      local_20 = *puVar1;
    }
    if (0xf < local_28) {
      FUN_00402430(local_3c[0],local_28 + 1,1);
    }
    FUN_004340a0(this,local_34);
    uVar2 = FUN_004383a0(&local_24,local_34);
    if ((char)uVar2 == '\0') {
      puVar1 = param_1;
      this_00 = FUN_00433bc0(&local_24);
      FUN_00440d90(this_00,puVar1);
      goto LAB_00442911;
    }
  }
  param_1[5] = 0xf;
  param_1[4] = 0;
  *(undefined1 *)param_1 = 0;
  FUN_0043b1c0(param_1,(uint *)&param_3);
LAB_00442911:
  if (0xf < in_stack_00000020) {
    FUN_00402430(param_3,in_stack_00000020 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}


