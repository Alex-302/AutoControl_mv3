// _isdigit @ 004668db size=45 callers=1

/* Library Function - Single Match
    _isdigit
   
   Library: Visual Studio 2015 Release */

int __cdecl _isdigit(int _C)

{
  int iVar1;
  
  if (DAT_0049f7f4 != 0) {
    iVar1 = __isdigit_l(_C,(_locale_t)0x0);
    return iVar1;
  }
  return *(ushort *)(PTR_DAT_0049d230 + _C * 2) & 4;
}


