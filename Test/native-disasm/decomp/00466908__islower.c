// _islower @ 00466908 size=45 callers=1

/* Library Function - Single Match
    _islower
   
   Library: Visual Studio 2015 Release */

int __cdecl _islower(int _C)

{
  int iVar1;
  
  if (DAT_0049f7f4 != 0) {
    iVar1 = __islower_l(_C,(_locale_t)0x0);
    return iVar1;
  }
  return *(ushort *)(PTR_DAT_0049d230 + _C * 2) & 2;
}


