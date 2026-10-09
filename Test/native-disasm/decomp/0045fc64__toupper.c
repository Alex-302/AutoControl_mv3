// _toupper @ 0045fc64 size=48 callers=1

/* Library Function - Single Match
    _toupper
   
   Library: Visual Studio 2015 Release */

int __cdecl _toupper(int _C)

{
  if (DAT_0049f7f4 == 0) {
    if (_C - 0x61U < 0x1a) {
      _C = _C + -0x20;
    }
  }
  else {
    _C = __toupper_l(_C,(_locale_t)0x0);
  }
  return _C;
}


