// feholdexcept @ 00476520 size=79 callers=1

/* Library Function - Single Match
    _feholdexcept
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl feholdexcept(uint *param_1)

{
  int iVar1;
  uint local_c;
  uint local_8;
  
  local_c = 0;
  local_8 = 0;
  iVar1 = fegetenv(&local_c);
  if (iVar1 == 0) {
    param_1[1] = local_8;
    *param_1 = local_c;
    local_c = local_c | 0x1f;
    iVar1 = fesetenv(&local_c);
    if (iVar1 == 0) {
      __clearfp();
      return 0;
    }
  }
  return 1;
}


