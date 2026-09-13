// FUN_00403280 @ 00403280 size=84 callers=1

long __fastcall FUN_00403280(char *param_1)

{
  int *piVar1;
  long lVar2;
  char *_Str;
  char *local_4;
  
  _Str = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    _Str = *(char **)param_1;
  }
  local_4 = param_1;
  piVar1 = __errno();
  *piVar1 = 0;
  lVar2 = _strtol(_Str,&local_4,10);
  if (_Str != local_4) {
    piVar1 = __errno();
    if (*piVar1 != 0x22) {
      return lVar2;
    }
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("stoi argument out of range");
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ea4("invalid stoi argument");
}


