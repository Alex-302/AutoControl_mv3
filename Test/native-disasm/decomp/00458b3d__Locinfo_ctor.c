// _Locinfo_ctor @ 00458b3d size=75 callers=1

/* Library Function - Single Match
    public: static void __cdecl std::_Locinfo::_Locinfo_ctor(class std::_Locinfo *,char const *)
   
   Library: Visual Studio 2015 Release */

void __cdecl std::_Locinfo::_Locinfo_ctor(_Locinfo *param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = _setlocale(0,(char *)0x0);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = "";
  }
  _Yarn<char>::operator=((_Yarn<char> *)(param_1 + 0x24),pcVar1);
  if (param_2 != (char *)0x0) {
    pcVar1 = _setlocale(0,param_2);
    if (pcVar1 != (char *)0x0) goto LAB_00458b7c;
  }
  pcVar1 = "*";
LAB_00458b7c:
  _Yarn<char>::operator=((_Yarn<char> *)(param_1 + 0x2c),pcVar1);
  return;
}


