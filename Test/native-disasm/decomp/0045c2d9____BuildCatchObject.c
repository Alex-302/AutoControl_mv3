// ___BuildCatchObject @ 0045c2d9 size=130 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___BuildCatchObject
   
   Library: Visual Studio 2015 Release */

void __cdecl ___BuildCatchObject(int param_1,uint *param_2,uint *param_3,byte *param_4)

{
  char cVar1;
  undefined3 extraout_var;
  uint *puVar2;
  
  puVar2 = param_2;
  if (-1 < (int)*param_3) {
    puVar2 = (uint *)((int)param_2 + param_3[2] + 0xc);
  }
  cVar1 = ___BuildCatchObjectHelper(param_1,param_2,param_3,param_4);
  if (CONCAT31(extraout_var,cVar1) == 1) {
    ___AdjustPointer(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
    FID_conflict__CallMemberFunction2(puVar2,*(undefined **)(param_4 + 0x18));
  }
  else if (CONCAT31(extraout_var,cVar1) == 2) {
    ___AdjustPointer(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
    FID_conflict__CallMemberFunction2(puVar2,*(undefined **)(param_4 + 0x18));
  }
  return;
}


