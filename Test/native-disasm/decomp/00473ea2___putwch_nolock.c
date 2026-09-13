// __putwch_nolock @ 00473ea2 size=69 callers=2

/* Library Function - Single Match
    __putwch_nolock
   
   Library: Visual Studio 2015 Release */

wint_t __cdecl __putwch_nolock(wchar_t _WCh)

{
  BOOL BVar1;
  DWORD local_8;
  
  if (DAT_0049d9b0 == (HANDLE)0xfffffffe) {
    ___dcrt_lowio_initialize_console_output();
  }
  if ((DAT_0049d9b0 == (HANDLE)0xffffffff) ||
     (BVar1 = WriteConsoleW(DAT_0049d9b0,&_WCh,1,&local_8,(LPVOID)0x0), BVar1 == 0)) {
    _WCh = L'\xffff';
  }
  return _WCh;
}


