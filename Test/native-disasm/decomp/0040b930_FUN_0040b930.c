// FUN_0040b930 @ 0040b930 size=176 callers=7

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0040b930(undefined4 *param_1,int *param_2,undefined4 param_3)

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
  ExceptionList = &local_1c;
  *param_1 = 0;
  local_14 = 0;
  piVar1 = (int *)*param_2;
  local_24 = 1;
  local_38._0_4_ = 0;
  local_38.decVal.Hi32 = 0;
  local_38._8_4_ = (undefined4 *)0x0;
  local_38._12_4_ = 0;
  local_28 = param_1;
  puVar2 = &stack0xfffffffc;
  if (piVar1 != (int *)0x0) {
    iVar3 = (**(code **)(*piVar1 + 0x5c))
                      (piVar1,param_3,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,
                       &local_38);
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


