// ___acrt_initialize_signal_handlers @ 0046de43 size=59 callers=0

/* Library Function - Single Match
    ___acrt_initialize_signal_handlers
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_initialize_signal_handlers(char **param_1)

{
  __crt_state_management::dual_state_global<char**>::initialize
            ((dual_state_global<char**> *)&DAT_0049fb10,param_1);
  __crt_state_management::dual_state_global<char**>::initialize
            ((dual_state_global<char**> *)&DAT_0049fb14,param_1);
  __crt_state_management::dual_state_global<char**>::initialize
            ((dual_state_global<char**> *)&DAT_0049fb18,param_1);
  __crt_state_management::dual_state_global<char**>::initialize
            ((dual_state_global<char**> *)&DAT_0049fb1c,param_1);
  return;
}


