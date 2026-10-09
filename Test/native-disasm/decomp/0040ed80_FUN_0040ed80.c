// FUN_0040ed80 @ 0040ed80 size=206 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_0040ed80(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 local_28;
  undefined4 uStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0047a41a;
  local_10 = ExceptionList;
  local_8 = 0;
  iVar2 = 0;
  ExceptionList = &local_10;
  while( true ) {
    piVar1 = FUN_0040b930(&local_18,(int *)&param_1,6);
    local_8._0_1_ = 1;
    if (param_1 != (int *)0x0) {
      (**(code **)(*param_1 + 8))(param_1);
    }
    param_1 = (int *)*piVar1;
    *piVar1 = 0;
    local_11 = param_1 != (int *)0x0;
    local_8._0_1_ = 2;
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))(local_18);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    if (local_11 == '\0') break;
    local_28 = 0;
    uStack_24 = 0;
    iStack_20 = 0;
    uStack_1c = 0;
    if (param_1 != (int *)0x0) {
      (**(code **)(*param_1 + 0x34))
                (param_1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_28);
    }
    if (iStack_20 == 0x25) {
      iVar2 = iVar2 + 1;
    }
  }
  local_8 = 3;
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 8))(param_1);
  }
  ExceptionList = local_10;
  return iVar2;
}


