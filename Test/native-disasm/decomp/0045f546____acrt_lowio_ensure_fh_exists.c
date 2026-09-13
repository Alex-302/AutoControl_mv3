// ___acrt_lowio_ensure_fh_exists @ 0045f546 size=140 callers=2

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___acrt_lowio_ensure_fh_exists
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_lowio_ensure_fh_exists(uint param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  if (param_1 < 0x2000) {
    uVar4 = 0;
    ___acrt_lock(7);
    iVar5 = 0;
    iVar3 = DAT_0049faf8;
    while (iVar3 <= (int)param_1) {
      if ((&DAT_0049f8f8)[iVar5] == 0) {
        puVar2 = ___acrt_lowio_create_handle_array();
        (&DAT_0049f8f8)[iVar5] = puVar2;
        if (puVar2 == (undefined4 *)0x0) {
          uVar4 = 0xc;
          break;
        }
        iVar3 = DAT_0049faf8 + 0x40;
        DAT_0049faf8 = iVar3;
      }
      iVar5 = iVar5 + 1;
    }
    FUN_0045f5d5();
  }
  else {
    piVar1 = __errno();
    uVar4 = 9;
    *piVar1 = 9;
    FUN_00465fa2();
  }
  return uVar4;
}


