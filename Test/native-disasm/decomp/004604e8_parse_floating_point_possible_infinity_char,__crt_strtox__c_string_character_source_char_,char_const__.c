// parse_floating_point_possible_infinity<char,__crt_strtox::c_string_character_source<char>,char_const*> @ 004604e8 size=173 callers=1

/* Library Function - Single Match
    enum __crt_strtox::floating_point_parse_result __cdecl
   __crt_strtox::parse_floating_point_possible_infinity<char,class
   __crt_strtox::c_string_character_source<char>,char const *>(char &,class
   __crt_strtox::c_string_character_source<char> &,char const *)
   
   Library: Visual Studio 2015 Release */

floating_point_parse_result __cdecl
__crt_strtox::
parse_floating_point_possible_infinity<char,__crt_strtox::c_string_character_source<char>,char_const*>
          (char *param_1,c_string_character_source<char> *param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  c_string_character_source<char> *local_10;
  char *local_c;
  char **local_8;
  
  local_8 = &param_3;
  iVar4 = 0;
  local_10 = param_2;
  local_c = param_1;
  iVar3 = 0;
  while ((*param_1 == (&DAT_0048516c)[iVar3] || (*param_1 == (&DAT_00485170)[iVar3]))) {
    cVar1 = **(char **)param_2;
    iVar3 = iVar3 + 1;
    *(char **)param_2 = *(char **)param_2 + 1;
    *param_1 = cVar1;
    if (iVar3 == 3) {
      c_string_character_source<char>::unget(param_2,cVar1);
      param_3 = *(char **)param_2;
      cVar1 = *param_3;
      *(char **)param_2 = param_3 + 1;
      *param_1 = cVar1;
      while ((*param_1 == "INITY"[iVar4] || (*param_1 == "inity"[iVar4]))) {
        cVar1 = **(char **)param_2;
        iVar4 = iVar4 + 1;
        *(char **)param_2 = *(char **)param_2 + 1;
        *param_1 = cVar1;
        if (iVar4 == 5) {
          c_string_character_source<char>::unget(param_2,cVar1);
          return 3;
        }
      }
      bVar2 = <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                        ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_10);
      return (uint)!bVar2 * 4 + 3;
    }
  }
  <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
            ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_10);
  return 7;
}


