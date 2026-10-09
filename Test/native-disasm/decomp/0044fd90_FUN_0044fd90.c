// FUN_0044fd90 @ 0044fd90 size=539 callers=2

undefined4 * __thiscall
FUN_0044fd90(void *this,undefined4 *param_1,int *param_2,byte *param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 uVar5;
  undefined4 local_1c;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e820;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = &stack0xffffffd4;
  if (*(int *)((int)this + 4) == 0) {
    ExceptionList = &local_10;
    local_14 = &stack0xffffffd4;
    FUN_0044a8f0(this,param_1,'\x01',*(undefined4 **)this,this,param_4);
    ExceptionList = local_10;
    return param_1;
  }
  piVar1 = *(int **)this;
  if (param_2 == (int *)*piVar1) {
    ExceptionList = &local_10;
    local_14 = &stack0xffffffd4;
    uVar3 = FUN_00438340(param_3,(byte *)(param_2 + 4));
    uVar5 = extraout_ECX;
    if ((char)uVar3 != '\0') {
      FUN_0044a8f0(this,param_1,'\x01',param_2,extraout_ECX,param_4);
      ExceptionList = local_10;
      return param_1;
    }
  }
  else if (param_2 == piVar1) {
    puVar4 = (undefined4 *)piVar1[2];
    ExceptionList = &local_10;
    local_14 = &stack0xffffffd4;
    uVar3 = FUN_00438340((byte *)(puVar4 + 4),param_3);
    uVar5 = extraout_ECX_00;
    if ((char)uVar3 != '\0') {
      FUN_0044a8f0(this,param_1,'\0',puVar4,extraout_ECX_00,param_4);
      ExceptionList = local_10;
      return param_1;
    }
  }
  else {
    ExceptionList = &local_10;
    uVar3 = FUN_00438340(param_3,(byte *)(param_2 + 4));
    if ((char)uVar3 != '\0') {
      local_18 = param_2;
      FUN_00448e20((int *)&local_18);
      piVar2 = local_18;
      uVar3 = FUN_00438340((byte *)(local_18 + 4),param_3);
      if ((char)uVar3 != '\0') {
        if (*(char *)(piVar2[2] + 0xd) == '\0') {
          FUN_0044a8f0(this,param_1,'\x01',param_2,extraout_ECX_01,param_4);
          ExceptionList = local_10;
          return param_1;
        }
        FUN_0044a8f0(this,param_1,'\0',piVar2,extraout_ECX_01,param_4);
        ExceptionList = local_10;
        return param_1;
      }
    }
    uVar3 = FUN_00438340((byte *)(param_2 + 4),param_3);
    uVar5 = extraout_ECX_02;
    if ((char)uVar3 != '\0') {
      local_18 = param_2;
      FUN_0043ed80((int *)&local_18);
      piVar2 = local_18;
      uVar5 = extraout_ECX_03;
      if ((local_18 == piVar1) ||
         (uVar3 = FUN_00438340(param_3,(byte *)(local_18 + 4)), uVar5 = extraout_ECX_04,
         (char)uVar3 != '\0')) {
        if (*(char *)(param_2[2] + 0xd) == '\0') {
          FUN_0044a8f0(this,param_1,'\x01',piVar2,uVar5,param_4);
          ExceptionList = local_10;
          return param_1;
        }
        FUN_0044a8f0(this,param_1,'\0',param_2,uVar5,param_4);
        ExceptionList = local_10;
        return param_1;
      }
    }
  }
  local_8 = 0xffffffff;
  puVar4 = (undefined4 *)FUN_00447780(this,&local_1c,uVar5,param_3,param_4);
  *param_1 = *puVar4;
  ExceptionList = local_10;
  return param_1;
}


