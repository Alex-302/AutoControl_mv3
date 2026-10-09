// __acrt_lock_stream_and_call<<lambda_b51c0495177f500e782686251704ae76>_> @ 0046420e size=40 callers=1

/* Library Function - Single Match
    unsigned int __cdecl __acrt_lock_stream_and_call<class <lambda_b51c0495177f500e782686251704ae76>
   >(struct _iobuf * const,class <lambda_b51c0495177f500e782686251704ae76> &&)
   
   Library: Visual Studio 2015 Release */

uint __cdecl
__acrt_lock_stream_and_call<<lambda_b51c0495177f500e782686251704ae76>_>
          (_iobuf *param_1,<lambda_b51c0495177f500e782686251704ae76> *param_2)

{
  uint uVar1;
  _iobuf *local_10;
  _iobuf *local_c;
  __crt_seh_guarded_call<unsigned_int> local_5;
  
  local_c = param_1;
  local_10 = param_1;
  uVar1 = __crt_seh_guarded_call<unsigned_int>::
          operator()<<lambda_11b4f7b0d3157825a5656a18eba1ae27>,<lambda_b51c0495177f500e782686251704ae76>&,<lambda_cf89b47920b5017557bfe891e78aca36>_>
                    (&local_5,(<lambda_11b4f7b0d3157825a5656a18eba1ae27> *)&local_10,param_2,
                     (<lambda_cf89b47920b5017557bfe891e78aca36> *)&local_c);
  return uVar1;
}


