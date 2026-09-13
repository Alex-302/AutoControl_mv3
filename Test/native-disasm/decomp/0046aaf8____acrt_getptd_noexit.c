// ___acrt_getptd_noexit @ 0046aaf8 size=133 callers=6

/* Library Function - Single Match
    ___acrt_getptd_noexit
   
   Library: Visual Studio 2015 Release */

__acrt_ptd * ___acrt_getptd_noexit(void)

{
  DWORD dwErrCode;
  __acrt_ptd *_Memory;
  int iVar1;
  
  dwErrCode = GetLastError();
  if ((DAT_0049d228 != 0xffffffff) &&
     (_Memory = (__acrt_ptd *)___acrt_FlsGetValue_4(DAT_0049d228), _Memory != (__acrt_ptd *)0x0)) {
LAB_0046ab6e:
    SetLastError(dwErrCode);
    return _Memory;
  }
  _Memory = __calloc_base(1,0x364);
  if (_Memory == (__acrt_ptd *)0x0) {
    _Memory = (__acrt_ptd *)0x0;
  }
  else {
    iVar1 = ___acrt_FlsSetValue_8(DAT_0049d228,_Memory);
    if (iVar1 != 0) {
      construct_ptd(_Memory,(__crt_locale_data **)&DAT_0049fafc);
      FID_conflict__free((void *)0x0);
      if (_Memory != (__acrt_ptd *)0x0) goto LAB_0046ab6e;
      goto LAB_0046ab65;
    }
  }
  FID_conflict__free(_Memory);
LAB_0046ab65:
  SetLastError(dwErrCode);
  return (__acrt_ptd *)0x0;
}


