// FUN_00414dc0 @ 00414dc0 size=66 callers=7

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_00414dc0(int *param_1)

{
  int *piVar1;
  undefined4 local_14;
  undefined4 uStack_10;
  int iStack_c;
  undefined4 uStack_8;
  
  if (param_1[0xb] == 0) {
    piVar1 = (int *)*param_1;
    local_14 = 0;
    uStack_10 = 0;
    iStack_c = 0;
    uStack_8 = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x34))
                (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_14);
    }
    param_1[0xb] = iStack_c;
  }
  return param_1 + 0xb;
}


