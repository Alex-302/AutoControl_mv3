// __scrt_common_main_seh @ 00459f4a size=306 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    int __cdecl __scrt_common_main_seh(void)
   
   Library: Visual Studio 2015 Release */

int __cdecl __scrt_common_main_seh(void)

{
  code *pcVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  uint *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  uVar3 = ___scrt_initialize_crt(1);
  if ((char)uVar3 != '\0') {
    bVar2 = false;
    uVar3 = ___scrt_acquire_startup_lock();
    if (DAT_0049f138 != 1) {
      if (DAT_0049f138 == 0) {
        DAT_0049f138 = 1;
        iVar4 = __initterm_e((undefined4 *)&DAT_00480678,(undefined4 *)&DAT_0048069c);
        if (iVar4 != 0) {
          return 0xff;
        }
        __initterm((undefined4 *)&DAT_004805b4,(undefined4 *)&DAT_00480674);
        DAT_0049f138 = 2;
      }
      else {
        bVar2 = true;
      }
      ___scrt_release_startup_lock((char)uVar3);
      piVar5 = (int *)FUN_0045a9ba();
      if ((*piVar5 != 0) &&
         (uVar3 = ___scrt_is_nonwritable_in_current_image((int)piVar5), (char)uVar3 != '\0')) {
        uVar10 = 0;
        uVar9 = 2;
        uVar3 = 0;
        pcVar1 = (code *)*piVar5;
        guard_check_icall();
        (*pcVar1)(uVar3,uVar9,uVar10);
      }
      puVar6 = (uint *)FUN_0045a9c0();
      if ((*puVar6 != 0) &&
         (uVar3 = ___scrt_is_nonwritable_in_current_image((int)puVar6), (char)uVar3 != '\0')) {
        __register_thread_local_exe_atexit_callback(*puVar6);
      }
      piVar5 = FUN_00467c62();
      puVar7 = (undefined4 *)FUN_00467c5c();
      FID_conflict___get_initial_narrow_environment();
      iVar4 = FUN_00431280((RAWINPUTDEVICE *)*puVar7,*piVar5);
      uVar8 = ___scrt_is_managed_app();
      if ((char)uVar8 != '\0') {
        if (!bVar2) {
          __cexit();
        }
        ___scrt_uninitialize_crt('\x01','\0');
        return iVar4;
      }
                    /* WARNING: Subroutine does not return */
      _exit(iVar4);
    }
  }
                    /* WARNING: Subroutine does not return */
  ___scrt_fastfail();
}


