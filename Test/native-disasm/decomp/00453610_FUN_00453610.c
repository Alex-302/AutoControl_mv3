// FUN_00453610 @ 00453610 size=155 callers=14

void __fastcall FUN_00453610(char *param_1,char *param_2)

{
  uint *puVar1;
  undefined1 local_54 [24];
  undefined1 local_3c [24];
  undefined **local_24;
  undefined8 local_20;
  undefined4 *local_18;
  undefined1 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e8e0;
  local_10 = ExceptionList;
  if (*param_1 != '\x04') {
    ExceptionList = &local_10;
    puVar1 = (uint *)FUN_00438430(param_1,local_3c);
    local_8 = 0;
    local_18 = (undefined4 *)FUN_00442600(local_54,(uint *)"type must be boolean, but is ",puVar1);
    local_8 = CONCAT31(local_8._1_3_,1);
    if (0xf < (uint)local_18[5]) {
      local_18 = (undefined4 *)*local_18;
    }
    local_24 = std::exception::vftable;
    local_20 = 0;
    local_14 = 1;
    ___std_exception_copy(&local_18,(undefined4 *)&local_20);
    local_24 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_24,&DAT_0049a03c);
  }
  *param_2 = param_1[8];
  return;
}


