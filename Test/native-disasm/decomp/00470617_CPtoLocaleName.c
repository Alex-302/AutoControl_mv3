// CPtoLocaleName @ 00470617 size=62 callers=2

/* Library Function - Single Match
    wchar_t const * __cdecl CPtoLocaleName(int)
   
   Library: Visual Studio 2015 Release */

wchar_t * __cdecl CPtoLocaleName(int param_1)

{
  if (param_1 == 0x3a4) {
    return (wchar_t *)PTR_u_ja_JP_00486c64;
  }
  if (param_1 == 0x3a8) {
    return (wchar_t *)PTR_u_zh_CN_00486c68;
  }
  if (param_1 == 0x3b5) {
    return (wchar_t *)PTR_u_ko_KR_00486c6c;
  }
  if (param_1 != 0x3b6) {
    return (wchar_t *)0x0;
  }
  return (wchar_t *)PTR_u_zh_TW_00486c70;
}


