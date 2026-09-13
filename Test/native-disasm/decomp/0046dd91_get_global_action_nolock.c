// get_global_action_nolock @ 0046dd91 size=66 callers=1

/* Library Function - Single Match
    void (__cdecl** __cdecl get_global_action_nolock(int))(int)
   
   Library: Visual Studio 2015 Release */

_func_void_int ** __cdecl get_global_action_nolock(int param_1)

{
  if (param_1 == 2) {
    return (_func_void_int **)&DAT_0049fb10;
  }
  if (param_1 != 6) {
    if (param_1 == 0xf) {
      return (_func_void_int **)&DAT_0049fb1c;
    }
    if (param_1 == 0x15) {
      return (_func_void_int **)&DAT_0049fb14;
    }
    if (param_1 != 0x16) {
      return (_func_void_int **)0x0;
    }
  }
  return (_func_void_int **)&DAT_0049fb18;
}


