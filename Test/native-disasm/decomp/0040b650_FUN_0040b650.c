// FUN_0040b650 @ 0040b650 size=166 callers=4

undefined4 * __fastcall FUN_0040b650(undefined4 *param_1,int *param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  _union_2683 local_38;
  undefined4 *local_28;
  undefined4 local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_00479e29;
  local_1c = ExceptionList;
  local_38._0_4_ = 0;
  local_38.decVal.Hi32 = 0;
  local_38._8_4_ = (undefined4 *)0x0;
  local_38._12_4_ = 0;
  ExceptionList = &local_1c;
  *param_1 = 0;
  local_14 = 0;
  piVar1 = (int *)*param_2;
  local_24 = 1;
  local_28 = param_1;
  puVar2 = &stack0xfffffffc;
  if (piVar1 != (int *)0x0) {
    iVar3 = (**(code **)(*piVar1 + 0x60))(piVar1,*param_3,param_3[1],&local_38);
    puVar2 = puStack_20;
    if ((iVar3 == 0) && (local_38.n2.vt == 9)) {
      (*(code *)**(undefined4 **)local_38._8_4_)(local_38._8_4_,&DAT_0048ec70,param_1);
      puVar2 = puStack_20;
    }
  }
  puStack_20 = puVar2;
  VariantClear((VARIANTARG *)&local_38.n2);
  ExceptionList = local_1c;
  return param_1;
}


