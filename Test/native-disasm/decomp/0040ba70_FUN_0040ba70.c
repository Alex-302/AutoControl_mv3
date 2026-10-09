// FUN_0040ba70 @ 0040ba70 size=253 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0040ba70(undefined4 *param_1,int param_2,int *param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_30;
  undefined4 uStack_2c;
  int iStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  int *local_1c;
  int local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00479e96;
  local_20 = 0;
  local_8 = 0;
  iVar2 = 0;
  local_14 = param_1;
  local_18 = param_2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  while (param_3 != (int *)0x0) {
    local_30 = 0;
    uStack_2c = 0;
    iStack_28 = 0;
    uStack_24 = 0;
    if (param_3 != (int *)0x0) {
      (**(code **)(*param_3 + 0x34))
                (param_3,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_30);
    }
    if (iStack_28 == local_18) {
      *local_14 = param_3;
      ExceptionList = local_10;
      return local_14;
    }
    if (iVar2 == param_4) break;
    puVar1 = FUN_0040b9e0(&local_1c,(int *)&param_3);
    local_8._0_1_ = 3;
    if (param_3 != (int *)0x0) {
      (**(code **)(*param_3 + 8))(param_3);
    }
    param_3 = (int *)*puVar1;
    *puVar1 = 0;
    local_8._0_1_ = 4;
    if (local_1c != (int *)0x0) {
      (**(code **)(*local_1c + 8))(local_1c);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    iVar2 = iVar2 + 1;
  }
  puVar1 = local_14;
  *local_14 = 0;
  local_8 = 5;
  if (param_3 != (int *)0x0) {
    (**(code **)(*param_3 + 8))(param_3);
  }
  ExceptionList = local_10;
  return puVar1;
}


