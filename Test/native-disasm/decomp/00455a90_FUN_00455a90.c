// FUN_00455a90 @ 00455a90 size=229 callers=1

void __fastcall FUN_00455a90(char *param_1,int *param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  undefined1 local_88 [24];
  undefined1 local_70 [24];
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined **local_28;
  undefined8 local_24;
  int local_1c;
  undefined4 *local_18;
  undefined1 local_14;
  undefined3 uStack_13;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ead3;
  local_10 = ExceptionList;
  if (*param_1 == '\0') {
    ExceptionList = &local_10;
    puVar1 = (uint *)FUN_00438430(param_1,local_40);
    local_8 = 0;
    local_18 = (undefined4 *)FUN_00442600(local_58,(uint *)"type must be array, but is ",puVar1);
    local_8 = CONCAT31(local_8._1_3_,1);
    if (0xf < (uint)local_18[5]) {
      local_18 = (undefined4 *)*local_18;
    }
    local_28 = std::exception::vftable;
    local_24 = 0;
    _local_14 = CONCAT31(uStack_13,1);
    ___std_exception_copy(&local_18,(undefined4 *)&local_24);
    local_28 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_28,&DAT_0049a03c);
  }
  if (*param_1 != '\x02') {
    ExceptionList = &local_10;
    puVar1 = (uint *)FUN_00438430(param_1,local_70);
    local_8 = 2;
    puVar2 = (undefined4 *)FUN_00442600(local_88,(uint *)"type must be array, but is ",puVar1);
    local_8 = CONCAT31(local_8._1_3_,3);
    FUN_00402490(&local_1c,puVar2);
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_1c,&DAT_0049a03c);
  }
  ExceptionList = &local_10;
  FUN_00456840(param_1,param_2);
  ExceptionList = local_10;
  return;
}


