// ___DestructExceptionObject @ 0045b9cd size=131 callers=5

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___DestructExceptionObject
   
   Library: Visual Studio 2015 Release */

void __cdecl ___DestructExceptionObject(int *param_1)

{
  byte *pbVar1;
  code *pcVar2;
  int *piVar3;
  
  if ((((param_1 != (int *)0x0) && (*param_1 == -0x1f928c9d)) && (param_1[4] == 3)) &&
     ((((param_1[5] == 0x19930520 || (param_1[5] == 0x19930521)) || (param_1[5] == 0x19930522)) &&
      (pbVar1 = (byte *)param_1[7], pbVar1 != (byte *)0x0)))) {
    if (*(undefined **)(pbVar1 + 4) == (undefined *)0x0) {
      if (((*pbVar1 & 0x10) != 0) && (piVar3 = *(int **)param_1[6], piVar3 != (int *)0x0)) {
        pcVar2 = *(code **)(*piVar3 + 8);
        guard_check_icall();
        (*pcVar2)(piVar3);
      }
    }
    else {
      FID_conflict__CallMemberFunction2(param_1[6],*(undefined **)(pbVar1 + 4));
    }
  }
  return;
}


