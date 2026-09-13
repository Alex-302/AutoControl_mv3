// _LocaleUpdate @ 0045fae6 size=131 callers=33

/* Library Function - Single Match
    public: __thiscall _LocaleUpdate::_LocaleUpdate(struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

_LocaleUpdate * __thiscall
_LocaleUpdate::_LocaleUpdate(_LocaleUpdate *this,__crt_locale_pointers *param_1)

{
  uint uVar1;
  undefined *puVar2;
  __acrt_ptd *p_Var3;
  
  this[0xc] = (_LocaleUpdate)0x0;
  if (param_1 == (__crt_locale_pointers *)0x0) {
    if (DAT_0049f7f4 != 0) {
      p_Var3 = FUN_0046aa74();
      *(__acrt_ptd **)this = p_Var3;
      *(int *)(this + 4) = *(int *)(p_Var3 + 0x4c);
      *(int *)(this + 8) = *(int *)(p_Var3 + 0x48);
      ___acrt_update_locale_info((int)p_Var3,(int *)(this + 4));
      ___acrt_update_multibyte_info(*(int *)this,(int *)(this + 8));
      uVar1 = *(uint *)(*(int *)this + 0x350);
      if ((uVar1 & 2) != 0) {
        return this;
      }
      *(uint *)(*(int *)this + 0x350) = uVar1 | 2;
      this[0xc] = (_LocaleUpdate)0x1;
      return this;
    }
    *(undefined **)(this + 4) = PTR_PTR_0049d2e8;
    puVar2 = PTR_DAT_0049d2ec;
  }
  else {
    *(undefined4 *)(this + 4) = *(undefined4 *)param_1;
    puVar2 = *(undefined **)(param_1 + 4);
  }
  *(undefined **)(this + 8) = puVar2;
  return this;
}


