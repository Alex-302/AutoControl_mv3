// FUN_00442db0 @ 00442db0 size=188 callers=5

undefined4 __fastcall FUN_00442db0(int *param_1,int param_2)

{
  uint *puVar1;
  undefined1 local_6c [24];
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
  puStack_c = &LAB_0047e1c8;
  local_10 = ExceptionList;
  if ((uint)(param_1[1] - *param_1) < param_2 + 2U) {
    ExceptionList = &local_10;
    puVar1 = (uint *)FUN_00403360(local_3c,1);
    local_8 = 0;
    puVar1 = (uint *)FUN_00442600(local_54,(uint *)"cannot read ",puVar1);
    local_8._0_1_ = 1;
    local_18 = (undefined4 *)FUN_004412a0(local_6c,puVar1,(uint *)" bytes from vector");
    local_8 = CONCAT31(local_8._1_3_,2);
    if (0xf < (uint)local_18[5]) {
      local_18 = (undefined4 *)*local_18;
    }
    local_24 = std::exception::vftable;
    local_20 = 0;
    local_14 = 1;
    ___std_exception_copy(&local_18,(undefined4 *)&local_20);
    local_24 = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_24,&DAT_00499ebc);
  }
  return CONCAT31((int3)(param_2 + 2U >> 8),*(undefined1 *)(*param_1 + 1 + param_2));
}


