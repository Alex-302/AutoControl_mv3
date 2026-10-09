// parse_command_line<char> @ 00467493 size=373 callers=2

/* Library Function - Single Match
    void __cdecl parse_command_line<char>(char *,char * *,char *,unsigned int *,unsigned int *)
   
   Library: Visual Studio 2015 Release */

void __cdecl
parse_command_line<char>(char *param_1,char **param_2,char *param_3,uint *param_4,uint *param_5)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  char *pcVar6;
  char *pcVar7;
  
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (char **)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  bVar5 = false;
  do {
    if (*param_1 == '\"') {
      bVar5 = !bVar5;
      cVar2 = '\"';
      pcVar6 = param_1 + 1;
    }
    else {
      *param_5 = *param_5 + 1;
      if (param_3 != (char *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      cVar2 = *param_1;
      pcVar6 = param_1 + 1;
      iVar4 = __ismbblead((int)cVar2);
      if (iVar4 != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (char *)0x0) {
          *param_3 = *pcVar6;
          param_3 = param_3 + 1;
        }
        pcVar6 = param_1 + 2;
      }
      if (cVar2 == '\0') {
        pcVar6 = pcVar6 + -1;
        goto LAB_00467523;
      }
    }
    param_1 = pcVar6;
  } while ((bVar5) || ((cVar2 != ' ' && (cVar2 != '\t'))));
  if (param_3 != (char *)0x0) {
    param_3[-1] = '\0';
  }
LAB_00467523:
  bVar5 = false;
  while (pcVar7 = pcVar6, *pcVar6 != '\0') {
    for (; (*pcVar7 == ' ' || (*pcVar7 == '\t')); pcVar7 = pcVar7 + 1) {
    }
    if (*pcVar7 == '\0') break;
    if (param_2 != (char **)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar1 = true;
      uVar3 = 0;
      for (; *pcVar7 == '\\'; pcVar7 = pcVar7 + 1) {
        uVar3 = uVar3 + 1;
      }
      pcVar6 = pcVar7;
      if (*pcVar7 == '\"') {
        if (((uVar3 & 1) == 0) && ((!bVar5 || (pcVar6 = pcVar7 + 1, *pcVar6 != '\"')))) {
          bVar1 = false;
          bVar5 = !bVar5;
          pcVar6 = pcVar7;
        }
        uVar3 = uVar3 >> 1;
      }
      while (uVar3 != 0) {
        uVar3 = uVar3 - 1;
        if (param_3 != (char *)0x0) {
          *param_3 = '\\';
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      cVar2 = *pcVar6;
      if ((cVar2 == '\0') || ((!bVar5 && ((cVar2 == ' ' || (cVar2 == '\t')))))) break;
      if (bVar1) {
        if (param_3 != (char *)0x0) {
          *param_3 = cVar2;
          param_3 = param_3 + 1;
        }
        iVar4 = __ismbblead((int)*pcVar6);
        if (iVar4 != 0) {
          pcVar6 = pcVar6 + 1;
          *param_5 = *param_5 + 1;
          if (param_3 != (char *)0x0) {
            *param_3 = *pcVar6;
            param_3 = param_3 + 1;
          }
        }
        *param_5 = *param_5 + 1;
      }
      pcVar7 = pcVar6 + 1;
    }
    if (param_3 != (char *)0x0) {
      *param_3 = '\0';
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (param_2 != (char **)0x0) {
    *param_2 = (char *)0x0;
  }
  *param_4 = *param_4 + 1;
  return;
}


