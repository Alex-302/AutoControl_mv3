// _Setgloballocale @ 00458bcf size=40 callers=1

/* Library Function - Single Match
    private: static void __cdecl std::locale::_Setgloballocale(void *)
   
   Library: Visual Studio 2015 Release */

void __cdecl std::locale::_Setgloballocale(void *param_1)

{
  if (DAT_0049ef55 == '\0') {
    DAT_0049ef55 = '\x01';
    _Atexit(tidy_global);
  }
  DAT_0049ef30 = param_1;
  return;
}


