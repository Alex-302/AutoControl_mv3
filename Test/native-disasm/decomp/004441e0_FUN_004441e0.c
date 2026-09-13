// FUN_004441e0 @ 004441e0 size=335 callers=12

uint __fastcall FUN_004441e0(char *param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  int *piVar3;
  undefined4 in_EAX;
  uint uVar4;
  undefined4 uVar5;
  undefined3 extraout_var;
  bool bVar6;
  bool bVar7;
  double in_XMM0_Qa;
  
  bVar1 = *param_1;
  bVar2 = *param_2;
  uVar4 = CONCAT31((int3)((uint)in_EAX >> 8),bVar2);
  if (bVar1 == bVar2) {
    uVar4 = (uint)bVar1;
    switch(uVar4) {
    case 0:
      return 1;
    case 1:
      if ((*(undefined4 **)(param_1 + 8))[1] != (*(undefined4 **)(param_2 + 8))[1]) {
        return 0;
      }
      piVar3 = (int *)**(undefined4 **)(param_1 + 8);
      uVar5 = FUN_00456a10((int *)*piVar3,piVar3,*(int **)**(undefined4 **)(param_2 + 8));
      if ((char)uVar5 != '\0') {
        return 1;
      }
      return 0;
    case 2:
      uVar4 = FUN_00448230(*(int **)(param_1 + 8),*(int **)(param_2 + 8));
      return uVar4;
    case 3:
      bVar7 = FUN_00440c30(*(byte **)(param_1 + 8),*(byte **)(param_2 + 8));
      return CONCAT31(extraout_var,bVar7);
    case 4:
      return (uint)(param_1[8] == param_2[8]);
    case 5:
    case 6:
      goto switchD_004441ff_caseD_5;
    case 7:
      if (*(double *)(param_1 + 8) != *(double *)(param_2 + 8)) {
        return 0;
      }
      return 1;
    default:
      goto switchD_004441ff_default;
    }
  }
  if (bVar1 == 5) {
    if (bVar2 == 7) {
      FUN_00477f40();
      if (in_XMM0_Qa != *(double *)(param_2 + 8)) {
        return 0;
      }
      return 1;
    }
    bVar7 = bVar2 == 6;
LAB_004442ae:
    if (!bVar7) {
switchD_004441ff_default:
      return uVar4 & 0xffffff00;
    }
switchD_004441ff_caseD_5:
    if ((*(int *)(param_1 + 8) == *(int *)(param_2 + 8)) &&
       (*(int *)(param_1 + 0xc) == *(int *)(param_2 + 0xc))) {
      return 1;
    }
  }
  else {
    if (bVar1 == 7) {
      if (bVar2 == 5) {
        FUN_00477f40();
      }
      else {
        if (bVar2 != 6) goto switchD_004441ff_default;
        FUN_00477f00();
      }
      bVar6 = NAN(*(double *)(param_1 + 8)) || NAN(in_XMM0_Qa);
      bVar7 = *(double *)(param_1 + 8) == in_XMM0_Qa;
    }
    else {
      if (bVar1 != 6) goto switchD_004441ff_default;
      if (bVar2 != 7) {
        bVar7 = bVar2 == 5;
        goto LAB_004442ae;
      }
      FUN_00477f00();
      bVar6 = NAN(in_XMM0_Qa) || NAN(*(double *)(param_2 + 8));
      bVar7 = in_XMM0_Qa == *(double *)(param_2 + 8);
    }
    if (bVar6 != bVar7) {
      return 1;
    }
  }
  return 0;
}


