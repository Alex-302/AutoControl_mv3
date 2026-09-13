// _tolower @ 0045fc34 size=48 callers=3

/* Library Function - Single Match
    _tolower
   
   Library: Visual Studio 2015 Release */

int __cdecl _tolower(int _C)

{
  if (DAT_0049f7f4 == 0) {
    if (_C - 0x41U < 0x1a) {
      _C = _C + 0x20;
    }
  }
  else {
    _C = __tolower_l(_C,(_locale_t)0x0);
  }
  return _C;
}


