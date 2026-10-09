// _setlocale @ 00466653 size=337 callers=3

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _setlocale
   
   Library: Visual Studio 2015 Release */

char * __cdecl _setlocale(int _Category,char *_Locale)

{
  int iVar1;
  pthreadlocinfo ptVar2;
  wchar_t *pwVar3;
  errno_t eVar4;
  wchar_t *_Memory;
  localeinfo_struct local_30;
  __acrt_ptd *local_28;
  wchar_t *local_24;
  size_t local_20 [5];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00499b10;
  uStack_c = 0x46665f;
  pwVar3 = FUN_004665b6(_Category,_Locale);
  if (pwVar3 != (wchar_t *)0x0) {
    local_28 = FUN_0046aa74();
    local_30.locinfo = *(pthreadlocinfo *)(local_28 + 0x4c);
    local_30.mbcinfo = *(pthreadmbcinfo *)(local_28 + 0x48);
    local_20[0] = 0;
    eVar4 = __wcstombs_s_l(local_20,(char *)0x0,0,pwVar3,0,&local_30);
    if (eVar4 != 0) {
      if ((eVar4 == 0x16) || (eVar4 == 0x22)) goto LAB_004666ba;
      if (eVar4 != 0) {
        return (char *)0x0;
      }
    }
    _Memory = __malloc_base(local_20[0] + 4);
    if (_Memory != (wchar_t *)0x0) {
      local_24 = _Memory + 2;
      eVar4 = __wcstombs_s_l((size_t *)0x0,(char *)local_24,local_20[0],pwVar3,0xffffffff,&local_30)
      ;
      ptVar2 = local_30.locinfo;
      if (eVar4 != 0) {
        if ((eVar4 == 0x16) || (eVar4 == 0x22)) {
LAB_004666ba:
                    /* WARNING: Subroutine does not return */
          __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        if (eVar4 != 0) {
          FID_conflict__free(_Memory);
          return (char *)0x0;
        }
      }
      ___acrt_lock(4);
      local_8 = (undefined *)0x0;
      pwVar3 = ptVar2->lc_category[_Category + 1].wlocale;
      if (pwVar3 != (wchar_t *)0x0) {
        LOCK();
        iVar1 = *(int *)pwVar3;
        *(int *)pwVar3 = iVar1 + -1;
        UNLOCK();
        if (iVar1 + -1 == 0) {
          FID_conflict__free(ptVar2->lc_category[_Category + 1].wlocale);
          ptVar2->lc_category[_Category + 1].wlocale = (wchar_t *)0x0;
        }
      }
      if (((((byte)local_28[0x350] & 2) == 0) && (((byte)DAT_0049d3f8 & 1) == 0)) &&
         (pwVar3 = ptVar2->lc_category[_Category + 1].wlocale, pwVar3 != (wchar_t *)0x0)) {
        LOCK();
        iVar1 = *(int *)pwVar3;
        *(int *)pwVar3 = *(int *)pwVar3 + -1;
        UNLOCK();
        if (iVar1 == 1) {
          FID_conflict__free(ptVar2->lc_category[_Category + 1].wlocale);
          ptVar2->lc_category[_Category + 1].wlocale = (wchar_t *)0x0;
        }
      }
      pwVar3 = local_24;
      *(uint *)_Memory = ptVar2->lc_time_cp;
      ptVar2->lc_category[_Category + 1].wlocale = _Memory;
      ptVar2->lc_category[_Category].wrefcount = (int *)local_24;
      local_8 = (undefined *)0xfffffffe;
      FUN_004667a7();
      return (char *)pwVar3;
    }
  }
  return (char *)0x0;
}


