// FUN_00440660 @ 00440660 size=299 callers=5

_Facet_base * __cdecl FUN_00440660(int param_1)

{
  uint uVar1;
  _Facet_base *p_Var2;
  int iVar3;
  _Facet_base *p_Var4;
  undefined **local_2c;
  undefined8 local_28;
  _Lockit local_20 [4];
  _Lockit local_1c [4];
  _Facet_base *local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dfa8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::_Lockit::_Lockit(local_20,0);
  p_Var2 = DAT_004a2a3c;
  local_8 = 0;
  local_18[0] = DAT_004a2a3c;
  if (DAT_0049ef48 == 0) {
    std::_Lockit::_Lockit(local_1c,0);
    if (DAT_0049ef48 == 0) {
      DAT_0049ef28 = DAT_0049ef28 + 1;
      DAT_0049ef48 = DAT_0049ef28;
    }
    FUN_0045884d((int *)local_1c);
  }
  uVar1 = DAT_0049ef48;
  iVar3 = *(int *)(param_1 + 4);
  if (DAT_0049ef48 < *(uint *)(iVar3 + 0xc)) {
    p_Var4 = *(_Facet_base **)(*(int *)(iVar3 + 8) + DAT_0049ef48 * 4);
    if (p_Var4 != (_Facet_base *)0x0) goto LAB_00440770;
  }
  else {
    p_Var4 = (_Facet_base *)0x0;
  }
  if (*(char *)(iVar3 + 0x14) == '\0') {
LAB_00440704:
    if (p_Var4 != (_Facet_base *)0x0) goto LAB_00440770;
  }
  else {
    iVar3 = FUN_00458a34();
    if (uVar1 < *(uint *)(iVar3 + 0xc)) {
      p_Var4 = *(_Facet_base **)(*(int *)(iVar3 + 8) + uVar1 * 4);
      goto LAB_00440704;
    }
  }
  p_Var4 = p_Var2;
  if (p_Var2 == (_Facet_base *)0x0) {
    iVar3 = FUN_004029a0((int *)local_18,param_1);
    p_Var4 = local_18[0];
    if (iVar3 == -1) {
      local_2c = std::bad_cast::vftable;
      local_28 = 0x48cb38;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_2c,&DAT_00499f94);
    }
    DAT_004a2a3c = local_18[0];
    if (*(code **)(*(int *)local_18[0] + 4) == FUN_004027d0) {
      LOCK();
      *(int *)(local_18[0] + 4) = *(int *)(local_18[0] + 4) + 1;
      UNLOCK();
    }
    else {
      (**(code **)(*(int *)local_18[0] + 4))();
    }
    std::_Facet_Register(p_Var4);
  }
LAB_00440770:
  FUN_0045884d((int *)local_20);
  ExceptionList = local_10;
  return p_Var4;
}


