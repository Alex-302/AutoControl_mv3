// FUN_004555f0 @ 004555f0 size=89 callers=1

undefined4 __fastcall FUN_004555f0(int param_1)

{
  uint uVar1;
  char *pcVar2;
  undefined4 uVar3;
  int *extraout_ECX;
  
  uVar1 = FUN_00456450(param_1);
  if ((char)uVar1 == '\0') {
    return uVar1 & 0xffffff00;
  }
  extraout_ECX[0x11] = (int)(char)extraout_ECX[0x12];
  pcVar2 = (char *)*extraout_ECX;
  if (pcVar2 != (char *)extraout_ECX[2]) {
    if (((*pcVar2 == '\\') && (pcVar2 = pcVar2 + 1, pcVar2 != (char *)extraout_ECX[2])) &&
       ((((extraout_ECX[0x14] & 8U) == 0 && ((*pcVar2 == '(' || (*pcVar2 == ')')))) ||
        (((extraout_ECX[0x14] & 0x10U) == 0 && ((*pcVar2 == '{' || (*pcVar2 == '}')))))))) {
      *extraout_ECX = (int)pcVar2;
    }
    *extraout_ECX = *extraout_ECX + 1;
  }
  uVar3 = FUN_00449160(extraout_ECX);
  return CONCAT31((int3)((uint)uVar3 >> 8),1);
}


