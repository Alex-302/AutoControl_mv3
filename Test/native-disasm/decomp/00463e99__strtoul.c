// _strtoul @ 00463e99 size=44 callers=6

/* Library Function - Single Match
    _strtoul
   
   Library: Visual Studio 2015 Release */

ulong __cdecl _strtoul(char *_Str,char **_EndPtr,int _Radix)

{
  ulong uVar1;
  undefined4 auStack_18 [2];
  int iStack_10;
  undefined4 uStack_c;
  
  uStack_c = 0;
  iStack_10 = _Radix;
  make_c_string_character_source<>(auStack_18,_Str,_EndPtr);
  uVar1 = __crt_strtox::parse_integer<unsigned_long,__crt_strtox::c_string_character_source<char>_>
                    (0);
  return uVar1;
}


