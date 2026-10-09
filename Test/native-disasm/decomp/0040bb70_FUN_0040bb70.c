// FUN_0040bb70 @ 0040bb70 size=326 callers=5

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall
FUN_0040bb70(undefined4 *param_1,undefined4 *param_2,int param_3,int param_4,uint param_5)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 local_50;
  undefined4 uStack_4c;
  int iStack_48;
  undefined4 uStack_44;
  undefined4 *local_3c;
  int *local_38;
  undefined4 *local_34;
  int local_30;
  uint local_2c;
  int *local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_00479ec6;
  local_1c = ExceptionList;
  piVar1 = (int *)0x0;
  local_2c = 0;
  local_28 = (int *)0x0;
  uVar3 = 0;
  local_14._0_1_ = 0;
  local_14._1_3_ = 0;
  local_30 = 0;
  ExceptionList = &local_1c;
  local_3c = param_2;
  local_34 = param_1;
  do {
    if (uVar3 < param_5) {
      puVar2 = FUN_0040b880(&local_38,local_3c,uVar3);
      local_2c = local_2c | 1;
      local_14._0_1_ = 1;
      if (local_28 != (int *)0x0) {
        (**(code **)(*local_28 + 8))(local_28);
      }
      local_14._0_1_ = 0;
      piVar1 = (int *)*puVar2;
      *puVar2 = 0;
      local_21 = '\x01';
      local_28 = piVar1;
      if (piVar1 == (int *)0x0) goto LAB_0040bc0c;
    }
    else {
LAB_0040bc0c:
      local_21 = '\0';
    }
    if ((local_2c & 1) != 0) {
      local_2c = local_2c & 0xfffffffe;
      local_14._0_1_ = 2;
      if (local_38 != (int *)0x0) {
        (**(code **)(*local_38 + 8))(local_38);
        piVar1 = local_28;
      }
      local_14._0_1_ = 0;
    }
    puVar2 = local_34;
    if (local_21 == '\0') {
      *local_34 = 0;
      local_14 = 5;
      if (piVar1 == (int *)0x0) {
        ExceptionList = local_1c;
        return local_34;
      }
      (**(code **)(*piVar1 + 8))(piVar1);
      ExceptionList = local_1c;
      return puVar2;
    }
    local_50 = 0;
    uStack_4c = 0;
    iStack_48 = 0;
    uStack_44 = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x34))
                (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_50);
      piVar1 = local_28;
    }
    if ((iStack_48 == param_3) && (local_30 = local_30 + 1, local_30 == param_4)) {
      *local_34 = piVar1;
      ExceptionList = local_1c;
      return local_34;
    }
    uVar3 = uVar3 + 1;
  } while( true );
}


