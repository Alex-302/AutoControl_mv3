// _strtol @ 00463e41 size=44 callers=7

/* Library Function - Single Match
    _strtol
   
   Library: Visual Studio 2015 Release */

long __cdecl _strtol(char *_Str,char **_EndPtr,int _Radix)

{
  ulong uVar1;
  undefined4 auStack_18 [2];
  int iStack_10;
  undefined4 uStack_c;
  
  uStack_c = 1;
  iStack_10 = _Radix;
  make_c_string_character_source<>(auStack_18,_Str,_EndPtr);
  uVar1 = __crt_strtox::parse_integer<unsigned_long,__crt_strtox::c_string_character_source<char>_>
                    (0);
  return uVar1;
}


