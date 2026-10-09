// parse_floating_point_possible_nan_is_snan<char,__crt_strtox::c_string_character_source<char>_> @ 004606ec size=60 callers=1

/* Library Function - Single Match
    bool __cdecl __crt_strtox::parse_floating_point_possible_nan_is_snan<char,class
   __crt_strtox::c_string_character_source<char> >(char &,class
   __crt_strtox::c_string_character_source<char> &)
   
   Library: Visual Studio 2015 Release */

bool __cdecl
__crt_strtox::
parse_floating_point_possible_nan_is_snan<char,__crt_strtox::c_string_character_source<char>_>
          (char *param_1,c_string_character_source<char> *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while ((*param_1 == (&DAT_0048518c)[iVar2] || (*param_1 == (&DAT_00485194)[iVar2]))) {
    cVar1 = **(char **)param_2;
    iVar2 = iVar2 + 1;
    *(char **)param_2 = *(char **)param_2 + 1;
    *param_1 = cVar1;
    if (iVar2 == 5) {
      return true;
    }
  }
  return false;
}


