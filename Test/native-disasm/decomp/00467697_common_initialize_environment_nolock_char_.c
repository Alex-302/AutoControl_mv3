// common_initialize_environment_nolock<char> @ 00467697 size=89 callers=2

/* Library Function - Single Match
    int __cdecl common_initialize_environment_nolock<char>(void)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_initialize_environment_nolock<char>(void)

{
  LPSTR _Memory;
  char **ppcVar1;
  int iVar2;
  
  if (DAT_0049f7c0 != 0) {
    return 0;
  }
  ___acrt_initialize_multibyte();
  _Memory = ___dcrt_get_narrow_environment_from_os();
  if (_Memory == (LPSTR)0x0) {
    iVar2 = -1;
  }
  else {
    ppcVar1 = (char **)FUN_004676f0(_Memory);
    if (ppcVar1 == (char **)0x0) {
      iVar2 = -1;
    }
    else {
      DAT_0049f7cc = ppcVar1;
      __crt_state_management::dual_state_global<char**>::initialize
                ((dual_state_global<char**> *)&DAT_0049f7c0,ppcVar1);
      iVar2 = 0;
    }
    FID_conflict__free((void *)0x0);
  }
  FID_conflict__free(_Memory);
  return iVar2;
}


