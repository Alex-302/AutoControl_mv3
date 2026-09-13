// common_vsprintf<__crt_stdio_output::standard_base,char> @ 004644d9 size=380 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    int __cdecl common_vsprintf<class __crt_stdio_output::standard_base,char>(unsigned __int64,char
   * const,unsigned int,char const * const,struct __crt_locale_pointers * const,char * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
common_vsprintf<__crt_stdio_output::standard_base,char>
          (__uint64 param_1,char *param_2,uint param_3,char *param_4,__crt_locale_pointers *param_5,
          char *param_6)

{
  char ***pppcVar1;
  int *piVar2;
  uint uVar3;
  int local_488;
  undefined1 local_484 [8];
  char local_47c;
  uint local_478;
  char ***local_474;
  uint local_470;
  uint local_46c;
  undefined4 local_468;
  char ***local_464;
  output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
  local_460 [64];
  formatting_buffer local_420 [1048];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_464 = (char ***)param_2;
  if ((param_4 == (char *)0x0) || ((param_3 != 0 && (param_2 == (char *)0x0)))) {
    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_00465fa2();
    return -1;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_488,param_5);
  pppcVar1 = local_464;
  local_478 = (uint)param_1 & 2;
  local_474 = local_464;
  local_470 = param_3;
  local_46c = 0;
  if (((param_1 & 2) != 0) || (local_468 = 0, local_464 == (char ***)0x0)) {
    local_468 = 1;
  }
  local_464 = (char ***)&local_474;
  output_processor<>(local_460,&local_464,(uint)param_1,param_1._4_4_,param_4,local_484,param_6);
  uVar3 = __crt_stdio_output::
          output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
          ::process(local_460);
  if (pppcVar1 == (char ***)0x0) goto LAB_00464605;
  if ((param_1 & 1) == 0) {
    if (local_478 == 0) {
      if (param_3 == 0) goto LAB_0046463d;
      if (local_46c == param_3) {
        uVar3 = 0xfffffffe;
LAB_0046464f:
        *(char *)((int)pppcVar1 + (param_3 - 1)) = '\0';
        goto LAB_00464605;
      }
    }
    else {
      if (param_3 == 0) goto LAB_00464605;
      if ((int)uVar3 < 0) {
        *(char *)pppcVar1 = '\0';
        goto LAB_00464605;
      }
      if (local_46c == param_3) goto LAB_0046464f;
    }
LAB_00464602:
    *(char *)((int)pppcVar1 + local_46c) = '\0';
  }
  else {
    if ((param_3 != 0) || (uVar3 == 0)) {
      if (local_46c != param_3) goto LAB_00464602;
      if (((int)uVar3 < 0) || (uVar3 <= param_3)) goto LAB_00464605;
    }
LAB_0046463d:
    uVar3 = 0xffffffff;
  }
LAB_00464605:
  __crt_stdio_output::formatting_buffer::~formatting_buffer(local_420);
  if (local_47c != '\0') {
    *(uint *)(local_488 + 0x350) = *(uint *)(local_488 + 0x350) & 0xfffffffd;
  }
  return uVar3;
}


