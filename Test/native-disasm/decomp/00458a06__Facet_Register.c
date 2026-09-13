// _Facet_Register @ 00458a06 size=46 callers=2

/* Library Function - Single Match
    void __cdecl std::_Facet_Register(class std::_Facet_base *)
   
   Library: Visual Studio 2015 Release */

void __cdecl std::_Facet_Register(_Facet_base *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(8);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = DAT_0049ef34;
    puVar1[1] = param_1;
  }
  DAT_0049ef34 = puVar1;
  return;
}


