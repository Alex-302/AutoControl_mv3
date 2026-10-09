// FUN_00466962 @ 00466962 size=96 callers=2

wchar_t * __cdecl FUN_00466962(wchar_t *param_1)

{
  rsize_t _SizeInWords;
  wchar_t wVar1;
  wchar_t *pwVar2;
  errno_t eVar3;
  
  if (param_1 == (wchar_t *)0x0) {
    return (wchar_t *)0x0;
  }
  pwVar2 = param_1;
  do {
    wVar1 = *pwVar2;
    pwVar2 = pwVar2 + 1;
  } while (wVar1 != L'\0');
  _SizeInWords = ((int)pwVar2 - (int)(param_1 + 1) >> 1) + 1;
  pwVar2 = (wchar_t *)FUN_004665ab(_SizeInWords * 2);
  if ((pwVar2 != (wchar_t *)0x0) && (eVar3 = _wcscpy_s(pwVar2,_SizeInWords,param_1), eVar3 != 0)) {
                    /* WARNING: Subroutine does not return */
    __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
  }
  return pwVar2;
}


