// FUN_00449160 @ 00449160 size=261 callers=19

void __fastcall FUN_00449160(int *param_1)

{
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  if ((char *)*param_1 == (char *)param_1[2]) {
    param_1[0x13] = -1;
    *(undefined1 *)(param_1 + 0x12) = 0xff;
  }
  else {
    cVar1 = *(char *)*param_1;
    *(char *)(param_1 + 0x12) = cVar1;
    puVar2 = FUN_0045c740((uint *)&DAT_0048ecb4,cVar1);
    if (puVar2 == (uint *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (int)(char)param_1[0x12];
    }
    param_1[0x13] = iVar3;
  }
  switch((char)param_1[0x12]) {
  case '\n':
    if ((*(byte *)(param_1 + 0x14) & 4) == 0) {
      return;
    }
    if (param_1[4] != 0) {
      return;
    }
    param_1[0x13] = 0x7c;
    return;
  default:
    goto switchD_004491b3_caseD_b;
  case '$':
    if ((param_1[0x14] & 0x2000000U) == 0) {
      return;
    }
    if ((char *)(*param_1 + 1) == (char *)param_1[2]) {
      return;
    }
    if (*(char *)(*param_1 + 1) == '\n') {
      return;
    }
    param_1[0x13] = 0;
    return;
  case '(':
  case ')':
    bVar5 = (*(byte *)(param_1 + 0x14) & 8) == 0;
    break;
  case '*':
    if ((param_1[0x14] & 0x4000000U) == 0) {
      return;
    }
    uVar4 = FUN_0044e210((int)(param_1 + 9));
    if ((char)uVar4 == '\0') {
      return;
    }
    param_1[0x13] = 0;
    return;
  case '+':
  case '?':
    bVar5 = (*(byte *)(param_1 + 0x14) & 1) == 0;
    break;
  case '\\':
    uVar4 = FUN_0044df90(param_1);
    if ((char)uVar4 == '\0') {
      return;
    }
    cVar1 = *(char *)(*param_1 + 1);
    *(char *)(param_1 + 0x12) = cVar1;
    param_1[0x13] = (int)cVar1;
    return;
  case '^':
    if ((param_1[0x14] & 0x2000000U) == 0) {
      return;
    }
    uVar4 = FUN_0044e210((int)(param_1 + 9));
    bVar5 = (char)uVar4 == '\0';
    break;
  case '{':
  case '}':
    bVar5 = (*(byte *)(param_1 + 0x14) & 0x10) == 0;
    break;
  case '|':
    bVar5 = (*(byte *)(param_1 + 0x14) & 2) == 0;
  }
  if (bVar5) {
    param_1[0x13] = 0;
  }
switchD_004491b3_caseD_b:
  return;
}


