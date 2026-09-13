// common_get_or_create_environment_nolock<char> @ 00467668 size=47 callers=2

/* Library Function - Single Match
    char * * __cdecl common_get_or_create_environment_nolock<char>(void)
   
   Library: Visual Studio 2015 Release */

char ** __cdecl common_get_or_create_environment_nolock<char>(void)

{
  int iVar1;
  
  if (DAT_0049f7c0 != (char **)0x0) {
    return DAT_0049f7c0;
  }
  if ((DAT_0049f7c4 != 0) && (iVar1 = common_initialize_environment_nolock<char>(), iVar1 == 0)) {
    iVar1 = initialize_environment_by_cloning_nolock<char>();
    return (char **)(~-(uint)(iVar1 != 0) & (uint)DAT_0049f7c0);
  }
  return (char **)0x0;
}


