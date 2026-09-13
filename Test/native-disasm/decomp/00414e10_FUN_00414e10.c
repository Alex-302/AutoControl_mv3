// FUN_00414e10 @ 00414e10 size=66 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_00414e10(int *param_1)

{
  int *piVar1;
  undefined4 local_14;
  undefined4 uStack_10;
  int iStack_c;
  undefined4 uStack_8;
  
  if (param_1[0xc] == -1) {
    piVar1 = (int *)*param_1;
    local_14 = 0;
    uStack_10 = 0;
    iStack_c = 0;
    uStack_8 = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x38))
                (piVar1,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_14);
    }
    param_1[0xc] = iStack_c;
  }
  return param_1 + 0xc;
}


