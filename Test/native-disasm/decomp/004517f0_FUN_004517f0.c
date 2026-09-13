// FUN_004517f0 @ 004517f0 size=292 callers=2

void __fastcall FUN_004517f0(int *param_1)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar4 = -1;
  iVar5 = param_1[0x13];
  if (iVar5 == 0x2a) goto LAB_0045180a;
  if (iVar5 == 0x2b) {
    iVar3 = 1;
    goto LAB_0045180a;
  }
  if (iVar5 == 0x3f) {
    iVar4 = 1;
    goto LAB_0045180a;
  }
  if (iVar5 != 0x7b) {
    return;
  }
  FUN_0044dfd0(param_1);
  iVar3 = FUN_004553d0(param_1,10,0x7fffffff);
  if (iVar3 == 0x7fffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(7);
  }
  iVar3 = param_1[0x11];
  iVar5 = iVar3;
  if (param_1[0x13] == 0x2c) {
    FUN_0044dfd0(param_1);
    if (param_1[0x13] != 0x7d) {
      bVar1 = FUN_00453ab0(param_1);
      if (!bVar1) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(7);
      }
      iVar5 = param_1[0x11];
      goto LAB_004518d6;
    }
  }
  else {
LAB_004518d6:
    iVar4 = iVar5;
    if (param_1[0x13] != 0x7d) goto LAB_0045190d;
  }
  if ((iVar4 == -1) || (iVar3 <= iVar4)) {
LAB_0045180a:
    *(uint *)(param_1[10] + 8) = *(uint *)(param_1[10] + 8) | 4;
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
    if (((param_1[0x14] & 0x400U) != 0) && (param_1[0x13] == 0x3f)) {
      FUN_0044dfd0(param_1);
      FUN_00453f50(param_1 + 9,iVar3,iVar4,'\0');
      return;
    }
    FUN_00453f50(param_1 + 9,iVar3,iVar4,'\x01');
    return;
  }
LAB_0045190d:
                    /* WARNING: Subroutine does not return */
  FUN_00458f04(7);
}


