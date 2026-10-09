// __onexit @ 0045a64f size=59 callers=1

/* Library Function - Single Match
    __onexit
   
   Library: Visual Studio 2015 Release */

_onexit_t __cdecl __onexit(_onexit_t _Func)

{
  int iVar1;
  byte bVar2;
  
  bVar2 = (byte)DAT_0049d070 & 0x1f;
  if (((DAT_0049d070 ^ DAT_0049f140) >> bVar2 | (DAT_0049d070 ^ DAT_0049f140) << 0x20 - bVar2) ==
      0xffffffff) {
    iVar1 = __crt_atexit();
  }
  else {
    iVar1 = __register_onexit_function();
  }
  return (_onexit_t)(~-(uint)(iVar1 != 0) & (uint)_Func);
}


