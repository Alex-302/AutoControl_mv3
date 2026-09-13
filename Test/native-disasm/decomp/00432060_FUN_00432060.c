// FUN_00432060 @ 00432060 size=143 callers=1

undefined4 FUN_00432060(int *param_1,int *param_2,undefined4 *param_3)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  bool bVar4;
  
  if (param_3 == (undefined4 *)0x0) {
    return 0x80004003;
  }
  piVar2 = &DAT_00483d04;
  uVar3 = 0xc;
  piVar1 = param_2;
  while (*piVar1 == *piVar2) {
    piVar1 = piVar1 + 1;
    piVar2 = piVar2 + 1;
    bVar4 = uVar3 < 4;
    uVar3 = uVar3 - 4;
    if (bVar4) goto LAB_004320b2;
  }
  piVar1 = &DAT_0048ef38;
  uVar3 = 0xc;
  do {
    if (*param_2 != *piVar1) {
      *param_3 = 0;
      return 0x80004002;
    }
    param_2 = param_2 + 1;
    piVar1 = piVar1 + 1;
    bVar4 = 3 < uVar3;
    uVar3 = uVar3 - 4;
  } while (bVar4);
LAB_004320b2:
  if (*(code **)(*param_1 + 4) != (code *)&LAB_00431fc0) {
    (**(code **)(*param_1 + 4))(param_1);
    *param_3 = param_1;
    return 0;
  }
  param_1[1] = param_1[1] + 1;
  *param_3 = param_1;
  return 0;
}


