// common_tcsncpy_s<char> @ 00475447 size=177 callers=1

/* Library Function - Single Match
    int __cdecl common_tcsncpy_s<char>(char * const,unsigned int,char const * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_tcsncpy_s<char>(char *param_1,uint param_2,char *param_3,uint param_4)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  
  if (param_4 == 0) {
    if (param_1 == (char *)0x0) {
      if (param_2 == 0) {
        return 0;
      }
    }
    else {
LAB_00475469:
      if (param_2 != 0) {
        if (param_4 == 0) {
          *param_1 = '\0';
          return 0;
        }
        if (param_3 != (char *)0x0) {
          uVar3 = param_4;
          uVar4 = param_2;
          pcVar5 = param_1;
          if (param_4 == 0xffffffff) {
            do {
              cVar1 = pcVar5[(int)param_3 - (int)param_1];
              *pcVar5 = cVar1;
              pcVar5 = pcVar5 + 1;
              if (cVar1 == '\0') break;
              uVar4 = uVar4 - 1;
            } while (uVar4 != 0);
          }
          else {
            do {
              cVar1 = pcVar5[(int)param_3 - (int)param_1];
              *pcVar5 = cVar1;
              pcVar5 = pcVar5 + 1;
              if ((cVar1 == '\0') || (uVar4 = uVar4 - 1, uVar4 == 0)) break;
              uVar3 = uVar3 - 1;
            } while (uVar3 != 0);
            if (uVar3 == 0) {
              *pcVar5 = '\0';
            }
          }
          if (uVar4 != 0) {
            return 0;
          }
          if (param_4 == 0xffffffff) {
            param_1[param_2 - 1] = '\0';
            return 0x50;
          }
          *param_1 = '\0';
          piVar2 = __errno();
          iVar6 = 0x22;
          goto LAB_00475489;
        }
        *param_1 = '\0';
      }
    }
  }
  else if (param_1 != (char *)0x0) goto LAB_00475469;
  piVar2 = __errno();
  iVar6 = 0x16;
LAB_00475489:
  *piVar2 = iVar6;
  FUN_00465fa2();
  return iVar6;
}


