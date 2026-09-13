// FUN_0044e020 @ 0044e020 size=491 callers=2

undefined1 __fastcall FUN_0044e020(int *param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  
  uVar4 = 0;
  iVar1 = param_1[0x13];
  do {
    if (iVar1 == -1) {
      return uVar4;
    }
    iVar1 = param_1[0x13];
    if (iVar1 == 0x7c) {
      return uVar4;
    }
    if (iVar1 == 0x29) {
      if (param_1[4] != 0) {
        return uVar4;
      }
      if ((param_1[0x14] & 0x10000000U) == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(5);
      }
    }
    if (iVar1 == 0x2e) {
      FUN_0044e3a0(param_1 + 9,5);
      pcVar2 = (char *)*param_1;
      if (pcVar2 != (char *)param_1[2]) {
        if (((*pcVar2 == '\\') && (pcVar2 = pcVar2 + 1, pcVar2 != (char *)param_1[2])) &&
           ((((param_1[0x14] & 8U) == 0 && ((*pcVar2 == '(' || (*pcVar2 == ')')))) ||
            (((param_1[0x14] & 0x10U) == 0 && ((*pcVar2 == '{' || (*pcVar2 == '}')))))))) {
          *param_1 = (int)pcVar2;
        }
        *param_1 = *param_1 + 1;
      }
      FUN_00449160(param_1);
LAB_0044e1d6:
      FUN_004517f0(param_1);
    }
    else if (iVar1 == 0x5c) {
      FUN_0044dfd0(param_1);
      if (((param_1[0x14] & 0x80U) == 0) || ((char)param_1[0x12] != 'b')) {
        if (((param_1[0x14] & 0x80U) == 0) || ((char)param_1[0x12] != 'B')) {
          FUN_00451670(param_1);
          goto LAB_0044e1d6;
        }
        FUN_0044e3a0(param_1 + 9,4);
        *(uint *)(param_1[10] + 8) = *(uint *)(param_1[10] + 8) ^ 1;
        FUN_0044dfd0(param_1);
      }
      else {
        FUN_0044e3a0(param_1 + 9,4);
        FUN_0044dfd0(param_1);
      }
    }
    else {
      if (iVar1 == 0x5b) {
        FUN_0044dfd0(param_1);
        FUN_004515e0(param_1);
        FUN_00451580(param_1,0x5d,4);
        goto LAB_0044e1d6;
      }
      if (iVar1 == 0x28) {
        FUN_0044dfd0(param_1);
        uVar3 = FUN_00451730(param_1);
        FUN_00451580(param_1,0x29,5);
        if ((char)uVar3 != '\0') goto LAB_0044e1d6;
      }
      else if (iVar1 == 0x5e) {
        FUN_0044e3a0(param_1 + 9,2);
        FUN_0044dfd0(param_1);
      }
      else {
        if (iVar1 != 0x24) {
          if ((((iVar1 == 0x2a) || (iVar1 == 0x2b)) || (iVar1 == 0x3f)) || (iVar1 == 0x7b)) {
                    /* WARNING: Subroutine does not return */
            FUN_00458f04(10);
          }
          if ((iVar1 == 0x7d) && ((param_1[0x14] & 0x10000000U) == 0)) {
                    /* WARNING: Subroutine does not return */
            FUN_00458f04(6);
          }
          if ((iVar1 == 0x5d) && ((param_1[0x14] & 0x10000000U) == 0)) {
                    /* WARNING: Subroutine does not return */
            FUN_00458f04(4);
          }
          FUN_00451920(param_1 + 9,(uint)*(byte *)(param_1 + 0x12));
          FUN_0044dfd0(param_1);
          goto LAB_0044e1d6;
        }
        FUN_0044e3a0(param_1 + 9,3);
        FUN_0044dfd0(param_1);
      }
    }
    iVar1 = param_1[0x13];
    uVar4 = 1;
  } while( true );
}


