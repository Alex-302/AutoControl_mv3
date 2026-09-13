// is_overflow_condition<unsigned___int64> @ 0046324b size=67 callers=1

/* Library Function - Single Match
    bool __cdecl __crt_strtox::is_overflow_condition<unsigned __int64>(unsigned int,unsigned
   __int64)
   
   Library: Visual Studio 2015 Release */

bool __cdecl __crt_strtox::is_overflow_condition<unsigned___int64>(uint param_1,__uint64 param_2)

{
  int in_stack_00000008;
  
  if (((param_1 & 4) == 0) &&
     (((param_1 & 1) == 0 ||
      (((((param_1 & 2) == 0 || ((uint)param_2 < 0x80000000)) ||
        (((uint)param_2 < 0x80000001 && (in_stack_00000008 == 0)))) &&
       ((((param_1 & 2) != 0 || ((uint)param_2 < 0x7fffffff)) || ((uint)param_2 < 0x80000000))))))))
  {
    return false;
  }
  return true;
}


