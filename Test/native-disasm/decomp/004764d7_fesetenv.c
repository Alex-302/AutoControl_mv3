// fesetenv @ 004764d7 size=73 callers=2

/* Library Function - Single Match
    _fesetenv
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl fesetenv(uint *param_1)

{
  undefined4 uVar1;
  uint local_c;
  uint local_8;
  
  local_c = 0;
  local_8 = 0;
  __setfpcontrolword(*param_1);
  __setfpstatusword(param_1[1]);
  fegetenv(&local_c);
  if ((*param_1 == local_c) && (param_1[1] == local_8)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


