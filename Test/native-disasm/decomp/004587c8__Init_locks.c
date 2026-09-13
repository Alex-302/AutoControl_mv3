// _Init_locks @ 004587c8 size=45 callers=2

/* Library Function - Single Match
    public: __thiscall std::_Init_locks::_Init_locks(void)
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

_Init_locks * __thiscall std::_Init_locks::_Init_locks(_Init_locks *this)

{
  _Rmtx *p_Var1;
  
  LOCK();
  DAT_0049d000 = DAT_0049d000 + 1;
  UNLOCK();
  if (DAT_0049d000 == 0) {
    p_Var1 = (_Rmtx *)&DAT_0049ee68;
    do {
      __Mtxinit(p_Var1);
      p_Var1 = p_Var1 + 1;
    } while ((int)p_Var1 < 0x49ef28);
  }
  return this;
}


