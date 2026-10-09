// _iswctype @ 0046ae89 size=95 callers=3

/* Library Function - Single Match
    _iswctype
   
   Library: Visual Studio 2015 Release */

int __cdecl _iswctype(wint_t _C,wctype_t _Type)

{
  uint uVar1;
  BOOL BVar2;
  uint in_ECX;
  WCHAR local_c;
  undefined2 uStack_a;
  uint local_8;
  
  if (_C == 0xffff) {
LAB_0046ae9e:
    uVar1 = 0;
  }
  else {
    if (_C < 0x100) {
      local_8._0_2_ = *(ushort *)(PTR_DAT_0049d1e4 + (uint)_C * 2);
    }
    else {
      _local_c = CONCAT22((short)(in_ECX >> 0x10),_C);
      local_8 = in_ECX & 0xffff0000;
      BVar2 = GetStringTypeW(1,&local_c,1,(LPWORD)&local_8);
      if (BVar2 == 0) goto LAB_0046ae9e;
    }
    uVar1 = (uint)((ushort)local_8 & _Type);
  }
  return uVar1;
}


