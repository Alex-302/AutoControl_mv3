// _raise @ 0046de87 size=490 callers=1

/* WARNING: Function: __SEH_prolog4_GS replaced with injection: SEH_prolog4 */
/* Library Function - Single Match
    _raise
   
   Library: Visual Studio 2015 Release */

int __cdecl _raise(int _SigNum)

{
  bool bVar1;
  bool bVar2;
  __crt_signal_action_t *p_Var3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  __acrt_ptd *p_Var7;
  char extraout_CL;
  char cVar8;
  byte bVar9;
  int iVar10;
  _func_void_int *p_Var11;
  __acrt_ptd *p_Var12;
  undefined4 local_38;
  int local_34;
  
  p_Var12 = (__acrt_ptd *)0x0;
  local_38 = 0;
  bVar2 = true;
  if (8 < _SigNum) {
    if (_SigNum == 0xb) goto LAB_0046dee1;
    if ((_SigNum == 0xf) || ((0x14 < _SigNum && (_SigNum < 0x17)))) goto LAB_0046ded6;
LAB_0046df0c:
    piVar4 = __errno();
    *piVar4 = 0x16;
    FUN_00465fa2();
    goto LAB_0046e089;
  }
  if (_SigNum == 8) {
LAB_0046dee1:
    p_Var12 = ___acrt_getptd_noexit();
    if (p_Var12 == (__acrt_ptd *)0x0) goto LAB_0046e089;
    p_Var3 = siglookup(_SigNum,*(__crt_signal_action_t **)p_Var12);
    if (p_Var3 == (__crt_signal_action_t *)0x0) goto LAB_0046df0c;
    p_Var3 = p_Var3 + 8;
    cVar8 = '\0';
    bVar2 = false;
  }
  else {
    if (_SigNum != 2) {
      if (_SigNum == 4) goto LAB_0046dee1;
      if (_SigNum != 6) goto LAB_0046df0c;
    }
LAB_0046ded6:
    p_Var3 = (__crt_signal_action_t *)get_global_action_nolock(_SigNum);
    cVar8 = extraout_CL;
  }
  local_34 = 0;
  bVar1 = false;
  if (cVar8 != '\0') {
    ___acrt_lock(3);
    bVar1 = bVar2;
  }
  if (bVar1) {
    bVar9 = (byte)DAT_0049d070 & 0x1f;
    p_Var11 = (_func_void_int *)
              ((DAT_0049d070 ^ (uint)*(_func_void_int **)p_Var3) >> bVar9 |
              (DAT_0049d070 ^ (uint)*(_func_void_int **)p_Var3) << 0x20 - bVar9);
  }
  else {
    p_Var11 = *(_func_void_int **)p_Var3;
    bVar2 = false;
  }
  if (p_Var11 != (_func_void_int *)0x1) {
    if (p_Var11 == (_func_void_int *)0x0) {
      if (bVar2) {
        ___acrt_unlock(3);
      }
                    /* WARNING: Subroutine does not return */
      __exit(3);
    }
    if (((_SigNum == 8) || (_SigNum == 0xb)) || (_SigNum == 4)) {
      local_34 = *(int *)(p_Var12 + 4);
      *(int *)(p_Var12 + 4) = 0;
      if (_SigNum == 8) {
        puVar5 = (undefined4 *)FUN_0046de7e();
        local_38 = *puVar5;
        puVar5 = (undefined4 *)FUN_0046de7e();
        *puVar5 = 0x8c;
        goto LAB_0046dfc8;
      }
    }
    else {
LAB_0046dfc8:
      if (_SigNum == 8) {
        iVar6 = DAT_00485c44 * 0xc + *(int *)p_Var12;
        iVar10 = DAT_00485c48 * 0xc + iVar6;
        for (; iVar6 != iVar10; iVar6 = iVar6 + 0xc) {
          *(undefined4 *)(iVar6 + 8) = 0;
        }
        goto LAB_0046e00a;
      }
    }
    bVar9 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
    *(_func_void_int **)p_Var3 =
         (_func_void_int *)((0U >> bVar9 | 0 << 0x20 - bVar9) ^ DAT_0049d070);
  }
LAB_0046e00a:
  FUN_0046e047();
  if (p_Var11 != (_func_void_int *)0x1) {
    if (_SigNum == 8) {
      p_Var7 = FUN_0046aa74();
      iVar6 = 0x46e032;
      (*(code *)PTR_guard_check_icall_004805b0)(8,*(undefined4 *)(p_Var7 + 8));
      (*p_Var11)(iVar6);
    }
    else {
      iVar6 = 0x46e060;
      (*(code *)PTR_guard_check_icall_004805b0)(_SigNum);
      (*p_Var11)(iVar6);
      if ((_SigNum != 0xb) && (_SigNum != 4)) goto LAB_0046e089;
    }
    *(int *)(p_Var12 + 4) = local_34;
    if (_SigNum == 8) {
      p_Var12 = FUN_0046aa74();
      *(undefined4 *)(p_Var12 + 8) = local_38;
    }
  }
LAB_0046e089:
  iVar6 = FUN_00477799();
  return iVar6;
}


