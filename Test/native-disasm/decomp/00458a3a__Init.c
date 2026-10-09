// _Init @ 00458a3a size=142 callers=6

/* WARNING: Function: __EH_prolog3 replaced with injection: EH_prolog3 */
/* WARNING: Function: __EH_epilog3 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    private: static class std::locale::_Locimp * __cdecl std::locale::_Init(bool)
   
   Library: Visual Studio 2015 Release */

_Locimp * __cdecl std::locale::_Init(bool param_1)

{
  code *pcVar1;
  _Locimp *p_Var2;
  _Lockit local_14 [12];
  undefined4 local_8;
  undefined4 uStack_4;
  
  uStack_4 = 8;
  local_8 = 0x458a46;
  _Lockit::_Lockit(local_14,0);
  local_8 = 0;
  p_Var2 = DAT_0049ef30;
  if (DAT_0049ef30 == (_Locimp *)0x0) {
    p_Var2 = _Locimp::_New_Locimp(false);
    _Setgloballocale(p_Var2);
    *(undefined4 *)(p_Var2 + 0x10) = 0x3f;
    _Yarn<char>::operator=((_Yarn<char> *)(p_Var2 + 0x18),"C");
    pcVar1 = *(code **)(*(int *)p_Var2 + 4);
    DAT_0049ef2c = p_Var2;
    guard_check_icall();
    (*pcVar1)();
    _DAT_0049ef50 = DAT_0049ef2c;
  }
  if (param_1) {
    pcVar1 = *(code **)(*(int *)p_Var2 + 4);
    guard_check_icall();
    (*pcVar1)();
  }
  FUN_0045884d((int *)local_14);
  return p_Var2;
}


