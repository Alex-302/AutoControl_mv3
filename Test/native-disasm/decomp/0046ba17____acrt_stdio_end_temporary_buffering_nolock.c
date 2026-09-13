// ___acrt_stdio_end_temporary_buffering_nolock @ 0046ba17 size=57 callers=1

/* Library Function - Single Match
    ___acrt_stdio_end_temporary_buffering_nolock
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_stdio_end_temporary_buffering_nolock(char param_1,FILE *param_2)

{
  int *piVar1;
  
  if ((param_1 != '\0') && (piVar1 = &param_2->_flag, ((uint)*piVar1 >> 9 & 1) != 0)) {
    ___acrt_stdio_flush_nolock(param_2);
    LOCK();
    *piVar1 = *piVar1 & 0xfffffd7f;
    UNLOCK();
    param_2->_bufsiz = 0;
    param_2->_cnt = 0;
    param_2->_ptr = (char *)0x0;
  }
  return;
}


