// is_overflow_condition<unsigned_long> @ 00463218 size=51 callers=2

/* Library Function - Single Match
    bool __cdecl __crt_strtox::is_overflow_condition<unsigned long>(unsigned int,unsigned long)
   
   Library: Visual Studio 2015 Release */

bool __cdecl __crt_strtox::is_overflow_condition<unsigned_long>(uint param_1,ulong param_2)

{
  if (((param_1 & 4) == 0) &&
     (((param_1 & 1) == 0 ||
      ((((param_1 & 2) == 0 || (param_2 < 0x80000001)) &&
       (((param_1 & 2) != 0 || (param_2 < 0x80000000)))))))) {
    return false;
  }
  return true;
}


