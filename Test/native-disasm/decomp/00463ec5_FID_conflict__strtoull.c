// FID_conflict:_strtoull @ 00463ec5 size=44 callers=1

/* Library Function - Multiple Matches With Different Base Names
    __strtoui64
    _strtoull
    _strtoumax
   
   Library: Visual Studio 2015 Release */

ulonglong __cdecl FID_conflict__strtoull(char *_String,char **_EndPtr,int _Radix)

{
  __uint64 _Var1;
  undefined4 auStack_18 [2];
  int iStack_10;
  undefined4 uStack_c;
  
  uStack_c = 0;
  iStack_10 = _Radix;
  make_c_string_character_source<>(auStack_18,_String,_EndPtr);
  _Var1 = __crt_strtox::
          parse_integer<unsigned___int64,__crt_strtox::c_string_character_source<char>_>(0);
  return _Var1;
}


