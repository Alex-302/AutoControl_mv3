// FUN_0046aa74 @ 0046aa74 size=131 callers=35

__acrt_ptd * FUN_0046aa74(void)

{
  DWORD dwErrCode;
  __acrt_ptd *_Memory;
  int iVar1;
  
  dwErrCode = GetLastError();
  if ((DAT_0049d228 != 0xffffffff) &&
     (_Memory = (__acrt_ptd *)___acrt_FlsGetValue_4(DAT_0049d228), _Memory != (__acrt_ptd *)0x0)) {
LAB_0046aadf:
    SetLastError(dwErrCode);
    return _Memory;
  }
  _Memory = __calloc_base(1,0x364);
  if ((_Memory == (__acrt_ptd *)0x0) ||
     (iVar1 = ___acrt_FlsSetValue_8(DAT_0049d228,_Memory), iVar1 == 0)) {
    FID_conflict__free(_Memory);
  }
  else {
    construct_ptd(_Memory,(__crt_locale_data **)&DAT_0049fafc);
    FID_conflict__free((void *)0x0);
    if (_Memory != (__acrt_ptd *)0x0) goto LAB_0046aadf;
  }
  SetLastError(dwErrCode);
                    /* WARNING: Subroutine does not return */
  _abort();
}


