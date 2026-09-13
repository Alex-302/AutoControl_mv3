// __wtol @ 004694b7 size=42 callers=2

/* Library Function - Single Match
    __wtol
   
   Library: Visual Studio 2015 Release */

long __cdecl __wtol(wchar_t *_Str)

{
  ulong uVar1;
  undefined4 auStack_18 [2];
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_c = 1;
  uStack_10 = 10;
  make_c_string_character_source<>(auStack_18,_Str,(undefined4 *)0x0);
  uVar1 = __crt_strtox::
          parse_integer<unsigned_long,__crt_strtox::c_string_character_source<wchar_t>_>(0);
  return uVar1;
}


