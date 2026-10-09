// parse_floating_point_possible_nan<char,__crt_strtox::c_string_character_source<char>,char_const*> @ 00460595 size=283 callers=1

/* Library Function - Single Match
    enum __crt_strtox::floating_point_parse_result __cdecl
   __crt_strtox::parse_floating_point_possible_nan<char,class
   __crt_strtox::c_string_character_source<char>,char const *>(char &,class
   __crt_strtox::c_string_character_source<char> &,char const *)
   
   Library: Visual Studio 2015 Release */

floating_point_parse_result __cdecl
__crt_strtox::
parse_floating_point_possible_nan<char,__crt_strtox::c_string_character_source<char>,char_const*>
          (char *param_1,c_string_character_source<char> *param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  floating_point_parse_result fVar3;
  int iVar4;
  c_string_character_source<char> *local_10;
  char *local_c;
  char **local_8;
  
  local_8 = &param_3;
  iVar4 = 0;
  local_10 = param_2;
  local_c = param_1;
  do {
    if ((*param_1 != (&DAT_00485184)[iVar4]) && (*param_1 != (&DAT_00485188)[iVar4])) {
      <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_10);
      return 7;
    }
    cVar1 = **(char **)param_2;
    iVar4 = iVar4 + 1;
    *(char **)param_2 = *(char **)param_2 + 1;
    *param_1 = cVar1;
  } while (iVar4 != 3);
  c_string_character_source<char>::unget(param_2,cVar1);
  param_3 = *(char **)param_2;
  cVar1 = *param_3;
  *(char **)param_2 = param_3 + 1;
  *param_1 = cVar1;
  if (cVar1 == '(') {
    cVar1 = **(char **)param_2;
    *(char **)param_2 = *(char **)param_2 + 1;
    *param_1 = cVar1;
    bVar2 = parse_floating_point_possible_nan_is_snan<char,__crt_strtox::c_string_character_source<char>_>
                      (param_1,param_2);
    if (bVar2) {
      fVar3 = 5;
    }
    else {
      bVar2 = parse_floating_point_possible_nan_is_ind<char,__crt_strtox::c_string_character_source<char>_>
                        (param_1,param_2);
      if (!bVar2) {
        if (*param_1 != ')') {
          do {
            if (*param_1 == '\0') break;
            iVar4 = (int)*param_1;
            if ((((9 < iVar4 - 0x30U) && (0x19 < iVar4 - 0x61U)) && (0x19 < iVar4 - 0x41U)) &&
               (iVar4 != 0x5f)) goto LAB_0046068f;
            cVar1 = **(char **)param_2;
            *(char **)param_2 = *(char **)param_2 + 1;
            *param_1 = cVar1;
          } while (cVar1 != ')');
          if (*param_1 != ')') {
LAB_0046068f:
            bVar2 = <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                              ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_10);
            return (-(uint)bVar2 & 0xfffffffd) + 7;
          }
        }
        return 4;
      }
      fVar3 = 6;
    }
    c_string_character_source<char>::unget(param_2,*param_1);
  }
  else {
    bVar2 = <lambda_3a2f1c4b88a94fdfdc7bccff06592946>::operator()
                      ((<lambda_3a2f1c4b88a94fdfdc7bccff06592946> *)&local_10);
    fVar3 = (-(uint)bVar2 & 0xfffffffd) + 7;
  }
  return fVar3;
}


