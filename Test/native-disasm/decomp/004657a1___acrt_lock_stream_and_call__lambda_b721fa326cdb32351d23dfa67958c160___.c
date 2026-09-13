// __acrt_lock_stream_and_call<<lambda_b721fa326cdb32351d23dfa67958c160>_> @ 004657a1 size=40 callers=1

/* Library Function - Single Match
    int __cdecl __acrt_lock_stream_and_call<class <lambda_b721fa326cdb32351d23dfa67958c160> >(struct
   _iobuf * const,class <lambda_b721fa326cdb32351d23dfa67958c160> &&)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_lock_stream_and_call<<lambda_b721fa326cdb32351d23dfa67958c160>_>
          (_iobuf *param_1,<lambda_b721fa326cdb32351d23dfa67958c160> *param_2)

{
  int iVar1;
  _iobuf *local_10;
  _iobuf *local_c;
  __crt_seh_guarded_call<int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  iVar1 = __crt_seh_guarded_call<int>::
          operator()<<lambda_d92cfe8357b99225085016881b624cb0>,<lambda_b721fa326cdb32351d23dfa67958c160>&,<lambda_42d75b0848218ec137fa420c8ba9fdf9>_>
                    (&local_5,(<lambda_d92cfe8357b99225085016881b624cb0> *)&local_10,param_2,
                     (<lambda_42d75b0848218ec137fa420c8ba9fdf9> *)&local_c);
  return iVar1;
}


