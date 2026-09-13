// FUN_0040bdb0 @ 0040bdb0 size=49 callers=2

undefined4 __fastcall FUN_0040bdb0(int *param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  piVar1 = (int *)*param_1;
  local_14 = 0;
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x38))(piVar1,*param_2,param_2[1],param_2[2],param_2[3],&local_14);
  }
  return uStack_c;
}


