// unget @ 00463135 size=40 callers=12

/* Library Function - Single Match
    public: void __thiscall __crt_strtox::c_string_character_source<char>::unget(char)
   
   Library: Visual Studio 2015 Release */

void __thiscall
__crt_strtox::c_string_character_source<char>::unget
          (c_string_character_source<char> *this,char param_1)

{
  int *piVar1;
  
  *(int *)this = *(int *)this + -1;
  if ((param_1 != '\0') && (**(char **)this != param_1)) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  return;
}


