// siglookup @ 0046de04 size=40 callers=1

/* Library Function - Single Match
    struct __crt_signal_action_t * __cdecl siglookup(int,struct __crt_signal_action_t * const)
   
   Library: Visual Studio 2015 Release */

__crt_signal_action_t * __cdecl siglookup(int param_1,__crt_signal_action_t *param_2)

{
  __crt_signal_action_t *p_Var1;
  
  p_Var1 = param_2 + DAT_00485c40 * 0xc;
  while( true ) {
    if (param_2 == p_Var1) {
      return (__crt_signal_action_t *)0x0;
    }
    if (*(int *)(param_2 + 4) == param_1) break;
    param_2 = param_2 + 0xc;
  }
  return param_2;
}


