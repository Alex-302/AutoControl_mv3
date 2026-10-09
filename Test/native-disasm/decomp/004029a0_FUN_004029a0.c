// FUN_004029a0 @ 004029a0 size=169 callers=1

undefined4 __cdecl FUN_004029a0(int *param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  wchar_t *pwVar3;
  undefined4 *puVar4;
  _Ctypevec *p_Var5;
  char *pcVar6;
  _Locinfo local_58 [52];
  _Ctypevec local_24;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047913f;
  local_10 = ExceptionList;
  local_14 = 0;
  if ((param_1 != (int *)0x0) && (*param_1 == 0)) {
    ExceptionList = &local_10;
    puVar4 = operator_new(0x18);
    local_8 = 0;
    iVar1 = *(int *)(param_2 + 4);
    if (iVar1 == 0) {
      pcVar6 = "";
    }
    else {
      pcVar6 = *(char **)(iVar1 + 0x18);
      if (pcVar6 == (char *)0x0) {
        pcVar6 = (char *)(iVar1 + 0x1c);
      }
    }
    FUN_004025d0(local_58,pcVar6);
    puVar4[1] = 0;
    *puVar4 = std::ctype<char>::vftable;
    p_Var5 = __Getctype(&local_24);
    psVar2 = p_Var5->_Table;
    iVar1 = p_Var5->_Delfl;
    pwVar3 = p_Var5->_LocaleName;
    puVar4[2] = p_Var5->_Page;
    puVar4[3] = psVar2;
    puVar4[4] = iVar1;
    puVar4[5] = pwVar3;
    *param_1 = (int)puVar4;
    FUN_004026a0(local_58);
  }
  ExceptionList = local_10;
  return 2;
}


