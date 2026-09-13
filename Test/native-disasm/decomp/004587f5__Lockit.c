// _Lockit @ 004587f5 size=49 callers=8

/* Library Function - Single Match
    public: __thiscall std::_Lockit::_Lockit(int)
   
   Library: Visual Studio 2015 Release */

_Lockit * __thiscall std::_Lockit::_Lockit(_Lockit *this,int param_1)

{
  *(int *)this = param_1;
  if (param_1 == 0) {
    __lock_locales();
  }
  else if (param_1 < 8) {
    __Mtxlock((_Rmtx *)(&DAT_0049ee68 + param_1 * 0x18));
  }
  return this;
}


