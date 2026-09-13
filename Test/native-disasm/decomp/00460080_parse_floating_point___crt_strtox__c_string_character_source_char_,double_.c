// parse_floating_point<__crt_strtox::c_string_character_source<char>,double> @ 00460080 size=118 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::parse_floating_point<class
   __crt_strtox::c_string_character_source<char>,double>(struct __crt_locale_pointers * const,class
   __crt_strtox::c_string_character_source<char>,double * const)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::parse_floating_point<__crt_strtox::c_string_character_source<char>,double>
          (__crt_locale_pointers *param_1,undefined4 param_2,undefined4 *param_3,double *param_4)

{
  double *pdVar1;
  int *piVar2;
  SLD_STATUS SVar3;
  floating_point_parse_result fVar4;
  floating_point_string local_314 [780];
  uint local_8;
  
  pdVar1 = param_4;
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if ((param_4 == (double *)0x0) || (param_1 == (__crt_locale_pointers *)0x0)) {
    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_00465fa2();
    SVar3 = 1;
  }
  else {
    fVar4 = parse_floating_point_from_source<__crt_strtox::c_string_character_source<char>_>
                      (param_1,(c_string_character_source<char> *)&param_2,local_314);
    SVar3 = parse_floating_point_write_result<double>(fVar4,local_314,pdVar1);
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = param_2;
  }
  return SVar3;
}


