// FUN_00443020 @ 00443020 size=254 callers=5

undefined8 __fastcall FUN_00443020(int *param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  undefined4 *puVar3;
  undefined1 local_70 [24];
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined **local_28;
  undefined8 local_24;
  undefined1 local_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  undefined1 uStack_15;
  undefined1 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e1f8;
  local_10 = ExceptionList;
  iVar1 = *param_1;
  if ((uint)(param_1[1] - iVar1) < param_2 + 9U) {
    ExceptionList = &local_10;
    puVar2 = (uint *)FUN_00403360(local_40,8);
    local_8 = 0;
    puVar2 = (uint *)FUN_00442600(local_58,(uint *)"cannot read ",puVar2);
    local_8._0_1_ = 1;
    puVar3 = (undefined4 *)FUN_004412a0(local_70,puVar2,(uint *)" bytes from vector");
    local_8 = CONCAT31(local_8._1_3_,2);
    if (0xf < (uint)puVar3[5]) {
      puVar3 = (undefined4 *)*puVar3;
    }
    local_18 = SUB41(puVar3,0);
    uStack_17 = (undefined1)((uint)puVar3 >> 8);
    uStack_16 = (undefined1)((uint)puVar3 >> 0x10);
    uStack_15 = (undefined1)((uint)puVar3 >> 0x18);
    local_28 = std::exception::vftable;
    local_24 = 0;
    local_14 = 1;
    ___std_exception_copy((undefined4 *)&local_18,(undefined4 *)&local_24);
    local_28 = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_28,&DAT_00499ebc);
  }
  return CONCAT17(*(undefined1 *)(iVar1 + 1 + param_2),
                  CONCAT16(*(undefined1 *)(iVar1 + 2 + param_2),
                           CONCAT15(*(undefined1 *)(iVar1 + 3 + param_2),
                                    CONCAT14(*(undefined1 *)(iVar1 + 4 + param_2),
                                             CONCAT13(*(undefined1 *)(iVar1 + 5 + param_2),
                                                      CONCAT12(*(undefined1 *)(iVar1 + 6 + param_2),
                                                               CONCAT11(*(undefined1 *)
                                                                         (iVar1 + 7 + param_2),
                                                                        *(undefined1 *)
                                                                         (iVar1 + 8 + param_2)))))))
                 );
}


