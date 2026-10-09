// FUN_0040bcc0 @ 0040bcc0 size=225 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall
FUN_0040bcc0(undefined4 *param_1,int param_2,int *param_3,undefined4 param_4)

{
  void **ppvVar1;
  undefined4 *puVar2;
  undefined4 local_40;
  undefined4 uStack_3c;
  int iStack_38;
  undefined4 uStack_34;
  undefined4 local_2c;
  undefined4 *local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  int local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_00479ef3;
  local_2c = 0;
  local_14 = 0;
  ppvVar1 = &local_1c;
  local_28 = param_1;
  local_1c = ExceptionList;
  while (ExceptionList = ppvVar1, param_3 != (int *)0x0) {
    local_40 = 0;
    uStack_3c = 0;
    iStack_38 = 0;
    uStack_34 = 0;
    if (param_3 != (int *)0x0) {
      (**(code **)(*param_3 + 0x34))
                (param_3,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_40);
    }
    if (iStack_38 == param_2) break;
    puVar2 = FUN_0040b930(&local_24,(int *)&param_3,param_4);
    local_14._0_1_ = 1;
    if (param_3 != (int *)0x0) {
      (**(code **)(*param_3 + 8))(param_3);
    }
    param_3 = (int *)*puVar2;
    *puVar2 = 0;
    local_14._0_1_ = 2;
    if (local_24 != (int *)0x0) {
      (**(code **)(*local_24 + 8))(local_24);
    }
    local_14 = (uint)local_14._1_3_ << 8;
    ppvVar1 = ExceptionList;
  }
  *local_28 = param_3;
  ExceptionList = local_1c;
  return local_28;
}


