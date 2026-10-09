// _wcspbrk @ 00471c5d size=69 callers=1

/* Library Function - Single Match
    _wcspbrk
   
   Library: Visual Studio 2015 Release */

wchar_t * __cdecl _wcspbrk(wchar_t *_Str,wchar_t *_Control)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  
  if (*_Str != L'\0') {
    do {
      if (*_Control != L'\0') {
        pwVar1 = _Control;
        wVar2 = *_Control;
        do {
          if (wVar2 == *_Str) {
            return _Str;
          }
          pwVar1 = pwVar1 + 1;
          wVar2 = *pwVar1;
        } while (wVar2 != L'\0');
      }
      _Str = _Str + 1;
    } while (*_Str != L'\0');
  }
  return (wchar_t *)0x0;
}


