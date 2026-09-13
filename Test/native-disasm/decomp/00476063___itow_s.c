// __itow_s @ 00476063 size=53 callers=2

/* Library Function - Single Match
    __itow_s
   
   Library: Visual Studio 2015 Release */

errno_t __cdecl __itow_s(int _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix)

{
  int iVar1;
  undefined1 local_8;
  
  if ((_Radix != 10) || (local_8 = true, -1 < _Val)) {
    local_8 = false;
  }
  iVar1 = common_xtox_s<unsigned_long,wchar_t>(_Val,_DstBuf,_SizeInWords,_Radix,local_8);
  return iVar1;
}


