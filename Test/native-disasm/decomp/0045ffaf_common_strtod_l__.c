// common_strtod_l<> @ 0045ffaf size=139 callers=1

/* Library Function - Multiple Matches With Same Base Name
    double __cdecl common_strtod_l<double,char>(char const * const,char * * const,struct
   __crt_locale_pointers * const)
    double __cdecl common_strtod_l<double,wchar_t>(wchar_t const * const,wchar_t * * const,struct
   __crt_locale_pointers * const)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

float10 __cdecl common_strtod_l<>(int param_1,int *param_2,__crt_locale_pointers *param_3)

{
  int *piVar1;
  SLD_STATUS SVar2;
  float10 fVar3;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int local_20;
  undefined1 local_1c [8];
  char local_14;
  double local_10;
  
  if (param_2 != (int *)0x0) {
    *param_2 = param_1;
  }
  if (param_1 == 0) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    fVar3 = (float10)0;
  }
  else {
    uStack_30 = 0x45ffe8;
    _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_20,param_3);
    local_10 = 0.0;
    make_c_string_character_source<>(&uStack_34,param_1,param_2);
    SVar2 = __crt_strtox::parse_floating_point<__crt_strtox::c_string_character_source<char>,double>
                      (local_1c);
    if ((SVar2 == 3) || (SVar2 == 2)) {
      piVar1 = __errno();
      *piVar1 = 0x22;
    }
    fVar3 = (float10)local_10;
    if (local_14 != '\0') {
      *(uint *)(local_20 + 0x350) = *(uint *)(local_20 + 0x350) & 0xfffffffd;
    }
  }
  return fVar3;
}


