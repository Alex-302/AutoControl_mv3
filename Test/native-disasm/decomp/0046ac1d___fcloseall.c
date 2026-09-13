// __fcloseall @ 0046ac1d size=151 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __fcloseall
   
   Library: Visual Studio 2015 Release */

int __cdecl __fcloseall(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_20;
  
  local_20 = 0;
  ___acrt_lock(8);
  for (iVar2 = 3; iVar2 != DAT_0049f558; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(DAT_0049f55c + iVar2 * 4);
    if (iVar1 != 0) {
      if ((*(uint *)(iVar1 + 0xc) >> 0xd & 1) != 0) {
        iVar1 = _fclose(*(FILE **)(DAT_0049f55c + iVar2 * 4));
        if (iVar1 != -1) {
          local_20 = local_20 + 1;
        }
      }
      DeleteCriticalSection((LPCRITICAL_SECTION)(*(int *)(DAT_0049f55c + iVar2 * 4) + 0x20));
      FID_conflict__free(*(void **)(DAT_0049f55c + iVar2 * 4));
      *(undefined4 *)(DAT_0049f55c + iVar2 * 4) = 0;
    }
  }
  FUN_0046acb4();
  return local_20;
}


