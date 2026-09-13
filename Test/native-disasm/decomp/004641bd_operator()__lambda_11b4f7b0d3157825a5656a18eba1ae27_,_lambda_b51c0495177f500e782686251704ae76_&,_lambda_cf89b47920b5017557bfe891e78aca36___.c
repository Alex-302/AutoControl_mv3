// operator()<<lambda_11b4f7b0d3157825a5656a18eba1ae27>,<lambda_b51c0495177f500e782686251704ae76>&,<lambda_cf89b47920b5017557bfe891e78aca36>_> @ 004641bd size=66 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: unsigned int __thiscall __crt_seh_guarded_call<unsigned int>::operator()<class
   <lambda_11b4f7b0d3157825a5656a18eba1ae27>,class <lambda_b51c0495177f500e782686251704ae76> &,class
   <lambda_cf89b47920b5017557bfe891e78aca36> >(class <lambda_11b4f7b0d3157825a5656a18eba1ae27>
   &&,class <lambda_b51c0495177f500e782686251704ae76> &,class
   <lambda_cf89b47920b5017557bfe891e78aca36> &&)
   
   Library: Visual Studio 2015 Release */

uint __thiscall
__crt_seh_guarded_call<unsigned_int>::
operator()<<lambda_11b4f7b0d3157825a5656a18eba1ae27>,<lambda_b51c0495177f500e782686251704ae76>&,<lambda_cf89b47920b5017557bfe891e78aca36>_>
          (__crt_seh_guarded_call<unsigned_int> *this,
          <lambda_11b4f7b0d3157825a5656a18eba1ae27> *param_1,
          <lambda_b51c0495177f500e782686251704ae76> *param_2,
          <lambda_cf89b47920b5017557bfe891e78aca36> *param_3)

{
  uint uVar1;
  
  __lock_file(*(FILE **)param_1);
  uVar1 = <lambda_b51c0495177f500e782686251704ae76>::operator()(param_2);
  FUN_00464202();
  return uVar1;
}


