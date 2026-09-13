// ___BuildCatchObjectHelper @ 0045c368 size=290 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___BuildCatchObjectHelper
   
   Library: Visual Studio 2015 Release */

char __cdecl ___BuildCatchObjectHelper(int param_1,uint *param_2,uint *param_3,byte *param_4)

{
  code *pcVar1;
  uint uVar2;
  uint *puVar3;
  
  pcVar1 = DAT_0049f49c;
  if (((param_3[1] == 0) || (*(char *)(param_3[1] + 8) == '\0')) ||
     ((param_3[2] == 0 && (-1 < (int)*param_3)))) {
    return '\0';
  }
  uVar2 = *param_3;
  if (-1 < (int)uVar2) {
    param_2 = (uint *)((int)param_2 + param_3[2] + 0xc);
  }
  if ((((char)uVar2 < '\0') && ((*param_4 & 0x10) != 0)) && (DAT_0049f49c != (code *)0x0)) {
    guard_check_icall();
    uVar2 = (*pcVar1)();
  }
  else {
    if ((uVar2 & 8) == 0) {
      if ((*param_4 & 1) == 0) {
        if (*(int *)(param_4 + 0x18) == 0) {
          if ((*(int *)(param_1 + 0x18) != 0) && (param_2 != (uint *)0x0)) {
            uVar2 = *(uint *)(param_4 + 0x14);
            puVar3 = (uint *)___AdjustPointer(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
            FUN_0045b0e0(param_2,puVar3,uVar2);
            return '\0';
          }
        }
        else if ((*(int *)(param_1 + 0x18) != 0) && (param_2 != (uint *)0x0)) {
          return ((*param_4 & 4) != 0) + '\x01';
        }
        goto LAB_0045c3d3;
      }
      if ((*(int *)(param_1 + 0x18) == 0) || (param_2 == (uint *)0x0)) goto LAB_0045c3d3;
      FUN_0045b0e0(param_2,*(uint **)(param_1 + 0x18),*(uint *)(param_4 + 0x14));
      if (*(int *)(param_4 + 0x14) != 4) {
        return '\0';
      }
      if (*param_2 == 0) {
        return '\0';
      }
      uVar2 = *param_2;
      goto LAB_0045c423;
    }
    uVar2 = *(uint *)(param_1 + 0x18);
  }
  if ((uVar2 == 0) || (param_2 == (uint *)0x0)) {
LAB_0045c3d3:
                    /* WARNING: Subroutine does not return */
    FUN_00464131();
  }
  *param_2 = uVar2;
LAB_0045c423:
  uVar2 = ___AdjustPointer(uVar2,(int *)(param_4 + 8));
  *param_2 = uVar2;
  return '\0';
}


