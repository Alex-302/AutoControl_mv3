// _Locimp_dtor @ 00458ac8 size=117 callers=1

/* WARNING: Function: __EH_prolog3 replaced with injection: EH_prolog3 */
/* WARNING: Function: __EH_epilog3 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    private: static void __cdecl std::locale::_Locimp::_Locimp_dtor(class std::locale::_Locimp *)
   
   Library: Visual Studio 2015 Release */

void __cdecl std::locale::_Locimp::_Locimp_dtor(_Locimp *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  _Lockit local_18 [4];
  int *local_14;
  undefined4 local_8;
  undefined4 uStack_4;
  
  uStack_4 = 8;
  local_8 = 0x458ad4;
  _Lockit::_Lockit(local_18,0);
  local_8 = 0;
  iVar2 = *(int *)(param_1 + 0xc);
  while (iVar2 != 0) {
    iVar2 = iVar2 + -1;
    local_14 = *(int **)(*(int *)(param_1 + 8) + iVar2 * 4);
    if (local_14 != (int *)0x0) {
      pcVar1 = *(code **)(*local_14 + 8);
      guard_check_icall();
      local_14 = (int *)(*pcVar1)();
      if (local_14 != (int *)0x0) {
        uVar3 = 1;
        pcVar1 = *(code **)*local_14;
        guard_check_icall();
        (*pcVar1)(uVar3);
      }
    }
  }
  FID_conflict__free(*(void **)(param_1 + 8));
  FUN_0045884d((int *)local_18);
  return;
}


