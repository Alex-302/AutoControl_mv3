// common_exit @ 004679ee size=261 callers=3

/* WARNING: Function: __SEH_prolog4_GS replaced with injection: SEH_prolog4 */
/* Library Function - Single Match
    void __cdecl common_exit(int,enum _crt_exit_cleanup_mode,enum _crt_exit_return_mode)
   
   Library: Visual Studio 2015 Release */

void __cdecl common_exit(int param_1,_crt_exit_cleanup_mode param_2,_crt_exit_return_mode param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  undefined4 *local_18;
  
  if ((param_3 == 0) && (uVar3 = ___scrt_is_managed_app(), (char)uVar3 != '\0')) {
    try_cor_exit_process(param_1);
  }
  ___acrt_lock(2);
  if (DAT_0049f7d8 != '\0') goto LAB_00467ac5;
  LOCK();
  DAT_0049f7d0 = 1;
  UNLOCK();
  if (param_2 == 0) {
    bVar2 = (byte)DAT_0049d070 & 0x1f;
    bVar1 = 0x20 - bVar2 & 0x1f;
    if (DAT_0049f7d4 != ((0U >> bVar1 | 0 << 0x20 - bVar1) ^ DAT_0049d070)) {
      uVar3 = DAT_0049d070 ^ DAT_0049f7d4;
      (*(code *)PTR_guard_check_icall_004805b0)(0,0,0);
      (*(code *)(uVar3 >> bVar2 | uVar3 << 0x20 - bVar2))();
    }
LAB_00467a8a:
    __execute_onexit_table();
  }
  else if (param_2 == 1) goto LAB_00467a8a;
  if (param_2 == 0) {
    __initterm((undefined4 *)&DAT_004806a8,(undefined4 *)&DAT_004806b8);
  }
  __initterm((undefined4 *)&DAT_004806bc,(undefined4 *)&DAT_004806c0);
  if (param_3 == 0) {
    DAT_0049f7d8 = '\x01';
  }
LAB_00467ac5:
  FUN_00467af8();
  if (param_3 != 0) {
    FUN_00477799();
    return;
  }
  exit_or_terminate_process(param_1);
  atexit_exception_filter(*(ulong *)*local_18);
  return;
}


