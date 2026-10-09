// FUN_00449310 @ 00449310 size=282 callers=4

void __fastcall FUN_00449310(int *param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 *puVar4;
  char *pcVar5;
  undefined4 *puVar6;
  
  iVar1 = param_1[10];
  cVar3 = FUN_0044e020(param_1);
  if (cVar3 == '\0') {
    if (param_1[0x13] != 0x7c) {
      return;
    }
    puVar4 = FUN_0044e3a0(param_1 + 9,8);
    FUN_004494b0(param_1 + 9,(int)puVar4);
  }
  puVar4 = FUN_0044e250(param_1 + 9,iVar1);
  iVar2 = param_1[0x13];
  while (iVar2 == 0x7c) {
    pcVar5 = (char *)*param_1;
    if (pcVar5 != (char *)param_1[2]) {
      if (((*pcVar5 == '\\') && (pcVar5 = pcVar5 + 1, pcVar5 != (char *)param_1[2])) &&
         ((((param_1[0x14] & 8U) == 0 && ((*pcVar5 == '(' || (*pcVar5 == ')')))) ||
          (((param_1[0x14] & 0x10U) == 0 && ((*pcVar5 == '{' || (*pcVar5 == '}')))))))) {
        *param_1 = (int)pcVar5;
      }
      *param_1 = *param_1 + 1;
    }
    FUN_00449160(param_1);
    cVar3 = FUN_0044e020(param_1);
    if (cVar3 == '\0') {
      puVar6 = operator_new(0x14);
      puVar6[4] = 0;
      *puVar6 = &PTR_LAB_0048ecb0;
      puVar6[1] = 8;
      puVar6[2] = 0;
      puVar6[3] = 0;
      puVar6[4] = param_1[10];
      if (*(int *)(param_1[10] + 0xc) != 0) {
        puVar6[3] = *(int *)(param_1[10] + 0xc);
        *(undefined4 **)(*(int *)(param_1[10] + 0xc) + 0x10) = puVar6;
      }
      *(undefined4 **)(param_1[10] + 0xc) = puVar6;
      param_1[10] = (int)puVar6;
      FUN_004494b0(param_1 + 9,(int)puVar6);
    }
    FUN_0044e310(param_1 + 9,iVar1,(int)puVar4);
    iVar2 = param_1[0x13];
  }
  return;
}


