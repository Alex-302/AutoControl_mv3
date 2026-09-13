// is_wide_character_specifier<char> @ 004646f3 size=64 callers=3

/* Library Function - Single Match
    bool __cdecl __crt_stdio_output::is_wide_character_specifier<char>(unsigned __int64,char,enum
   __crt_stdio_output::length_modifier)
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

bool __cdecl
__crt_stdio_output::is_wide_character_specifier<char>
          (__uint64 param_1,char param_2,length_modifier param_3)

{
  bool bVar1;
  
  if (param_3 != 2) {
    if ((param_3 == 3) || (param_3 == 0xc)) {
      return true;
    }
    if (param_3 != 0xd) {
      if ((param_2 == 'c') || (param_2 == 's')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      return !bVar1;
    }
  }
  return false;
}


