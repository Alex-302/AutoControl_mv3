// FUN_004565f0 @ 004565f0 size=316 callers=3

bool __fastcall FUN_004565f0(int *param_1)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  char *pcVar4;
  
  iVar1 = param_1[0x13];
  if (iVar1 != 0x5c) {
    if (iVar1 != 0x5b) {
      if ((iVar1 != 0x5d) && (iVar1 != -1)) {
        param_1[0x11] = (int)(char)param_1[0x12];
        FUN_0044dfd0(param_1);
        return true;
      }
      return false;
    }
    FUN_0044dfd0(param_1);
    iVar1 = param_1[0x13];
    if (((iVar1 != 0x3a) && (iVar1 != 0x3d)) && (iVar1 != 0x2e)) {
      param_1[0x11] = 0x5b;
      return true;
    }
    FUN_0044dfd0(param_1);
    FUN_00456f80(param_1,iVar1);
    return true;
  }
  pcVar4 = (char *)*param_1;
  if (pcVar4 != (char *)param_1[2]) {
    if (((*pcVar4 == '\\') && (pcVar4 = pcVar4 + 1, pcVar4 != (char *)param_1[2])) &&
       ((((param_1[0x14] & 8U) == 0 && ((*pcVar4 == '(' || (*pcVar4 == ')')))) ||
        (((param_1[0x14] & 0x10U) == 0 && ((*pcVar4 == '{' || (*pcVar4 == '}')))))))) {
      *param_1 = (int)pcVar4;
    }
    *param_1 = *param_1 + 1;
  }
  FUN_00449160(param_1);
  if ((param_1[0x14] & 0x200000U) != 0) {
    bVar2 = FUN_004570d0(param_1);
    return bVar2;
  }
  if ((param_1[0x14] & 0x10000U) != 0) {
    cVar3 = FUN_00455650(param_1,(char)param_1[0x12]);
    if (cVar3 != '\0') goto LAB_004566a3;
  }
  if ((param_1[0x14] & 0x8000U) != 0) {
    if ((char)param_1[0x12] == 'a') {
      param_1[0x11] = 7;
      FUN_0044dfd0(param_1);
      return true;
    }
    if ((char)param_1[0x12] == 'b') {
      param_1[0x11] = 8;
LAB_004566a3:
      FUN_0044dfd0(param_1);
      return true;
    }
  }
  param_1[0x11] = 0x5c;
  return true;
}


