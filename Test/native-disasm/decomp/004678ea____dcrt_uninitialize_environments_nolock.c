// ___dcrt_uninitialize_environments_nolock @ 004678ea size=55 callers=1

/* Library Function - Single Match
    ___dcrt_uninitialize_environments_nolock
   
   Library: Visual Studio 2015 Release */

void ___dcrt_uninitialize_environments_nolock(void)

{
  uninitialize<>(&DAT_0049f7c0,uninitialize_environment_internal<>);
  uninitialize<>(&DAT_0049f7c4,uninitialize_environment_internal<>);
  free_environment<>(DAT_0049f7cc);
  free_environment<>(DAT_0049f7c8);
  return;
}


