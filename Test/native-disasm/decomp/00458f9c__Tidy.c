// _Tidy @ 00458f9c size=72 callers=1

/* Library Function - Single Match
    private: void __thiscall std::ios_base::_Tidy(void)
   
   Library: Visual Studio 2015 Release */

void __thiscall std::ios_base::_Tidy(ios_base *this)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  _Callfns(this,0);
  puVar2 = *(undefined4 **)(this + 0x28);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    FUN_0045a6a4(puVar2);
    puVar2 = puVar1;
  }
  *(undefined4 *)(this + 0x28) = 0;
  puVar2 = *(undefined4 **)(this + 0x2c);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    FUN_0045a6a4(puVar2);
    puVar2 = puVar1;
  }
  *(undefined4 *)(this + 0x2c) = 0;
  return;
}


