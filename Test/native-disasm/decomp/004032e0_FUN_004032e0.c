// FUN_004032e0 @ 004032e0 size=86 callers=1

ulong __thiscall FUN_004032e0(void *this,int param_1)

{
  int *piVar1;
  ulong uVar2;
  char *_Str;
  char *local_4;
  
  _Str = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    _Str = *(char **)this;
  }
  local_4 = this;
  piVar1 = __errno();
  *piVar1 = 0;
  uVar2 = _strtoul(_Str,&local_4,param_1);
  if (_Str != local_4) {
    piVar1 = __errno();
    if (*piVar1 != 0x22) {
      return uVar2;
    }
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("stoul argument out of range");
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ea4("invalid stoul argument");
}


