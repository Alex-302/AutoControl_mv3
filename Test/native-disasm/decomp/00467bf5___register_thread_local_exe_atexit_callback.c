// __register_thread_local_exe_atexit_callback @ 00467bf5 size=56 callers=1

/* WARNING: Function: __SEH_prolog4_GS replaced with injection: SEH_prolog4 */
/* Library Function - Single Match
    __register_thread_local_exe_atexit_callback
   
   Library: Visual Studio 2015 Release */

void __cdecl __register_thread_local_exe_atexit_callback(uint param_1)

{
  code *pcVar1;
  byte bVar2;
  __acrt_ptd *p_Var3;
  
  bVar2 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
  if (DAT_0049f7d4 == ((0U >> bVar2 | 0 << 0x20 - bVar2) ^ DAT_0049d070)) {
    DAT_0049f7d4 = __crt_fast_encode_pointer<>(param_1);
    return;
  }
  p_Var3 = FUN_0046aa74();
  pcVar1 = *(code **)(p_Var3 + 0xc);
  if (pcVar1 != (code *)0x0) {
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*pcVar1)();
  }
                    /* WARNING: Subroutine does not return */
  _abort();
}


