// FUN_004413d0 @ 004413d0 size=75 callers=1

undefined4 * __fastcall FUN_004413d0(undefined4 *param_1,uint param_2)

{
  void *_Dst;
  
  _Dst = (void *)FUN_0045a6b2(param_2);
  if (_Dst != (void *)0x0) {
    _memset(_Dst,0,param_2);
    *param_1 = _Dst;
    return param_1;
  }
  *param_1 = 0;
  return param_1;
}


