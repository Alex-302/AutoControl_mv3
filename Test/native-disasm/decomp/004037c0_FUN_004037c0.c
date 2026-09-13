// FUN_004037c0 @ 004037c0 size=123 callers=1

undefined8 __fastcall FUN_004037c0(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  size_t sVar5;
  char *pcVar6;
  undefined8 uVar7;
  
  if (*param_2 == '\0') {
    sVar5 = 0;
    pcVar4 = param_1;
  }
  else {
    pcVar4 = param_2 + 1;
    pcVar6 = param_2;
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    sVar5 = (int)pcVar6 - (int)pcVar4;
  }
  iVar2 = FUN_0043a9f0(param_1,param_2,pcVar4,sVar5);
  uVar3 = iVar2 + 1;
  if (*(uint *)(param_1 + 0x10) < uVar3) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  *(uint *)(param_1 + 0x10) = uVar3;
  pcVar4 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pcVar4 = *(char **)param_1;
  }
  pcVar4[uVar3] = '\0';
  if (*param_2 == '\0') {
    iVar2 = 0;
  }
  else {
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar2 = (int)pcVar4 - (int)(param_2 + 1);
  }
  uVar3 = FUN_0043aa60(param_1,param_2,iVar2,iVar2);
  uVar7 = FUN_004354d0(param_1,0,uVar3);
  return uVar7;
}


