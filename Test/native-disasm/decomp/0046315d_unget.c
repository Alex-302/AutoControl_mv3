// unget @ 0046315d size=44 callers=2

/* Library Function - Single Match
    public: void __thiscall __crt_strtox::c_string_character_source<wchar_t>::unget(wchar_t)
   
   Library: Visual Studio 2015 Release */

void __thiscall
__crt_strtox::c_string_character_source<wchar_t>::unget
          (c_string_character_source<wchar_t> *this,wchar_t param_1)

{
  int *piVar1;
  
  *(int *)this = *(int *)this + -2;
  if ((param_1 != L'\0') && (**(wchar_t **)this != param_1)) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  return;
}


