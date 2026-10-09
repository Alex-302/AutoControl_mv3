// ___FrameUnwindToState @ 0045c4db size=164 callers=3

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___FrameUnwindToState
   
   Library: Visual Studio 2015 Release */

void __cdecl ___FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_3 + 4) < 0x81) {
    iVar2 = (int)*(char *)(param_1 + 8);
  }
  else {
    iVar2 = *(int *)(param_1 + 8);
  }
  iVar1 = ___vcrt_getptd();
  *(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + 1;
  while (iVar1 = iVar2, iVar1 != param_4) {
    if ((iVar1 < 0) || (*(int *)(param_3 + 4) <= iVar1)) goto LAB_0045c56a;
    iVar2 = *(int *)(*(int *)(param_3 + 8) + iVar1 * 8);
    if (*(int *)(*(int *)(param_3 + 8) + 4 + iVar1 * 8) != 0) {
      *(int *)(param_1 + 8) = iVar2;
      __CallSettingFrame_12(*(undefined4 *)(*(int *)(param_3 + 8) + 4 + iVar1 * 8),param_1,0x103);
    }
  }
  FUN_0045c58f();
  if (iVar1 == param_4) {
    *(int *)(param_1 + 8) = iVar1;
    return;
  }
LAB_0045c56a:
                    /* WARNING: Subroutine does not return */
  FUN_00464131();
}


