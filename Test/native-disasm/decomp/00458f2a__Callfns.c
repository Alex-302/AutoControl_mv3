// _Callfns @ 00458f2a size=50 callers=1

/* Library Function - Single Match
    private: void __thiscall std::ios_base::_Callfns(enum std::ios_base::event)
   
   Library: Visual Studio 2015 Release */

void __thiscall std::ios_base::_Callfns(ios_base *this,event param_1)

{
  undefined4 *puVar1;
  code *pcVar2;
  event eVar3;
  ios_base *piVar4;
  undefined4 uVar5;
  
  for (puVar1 = *(undefined4 **)(this + 0x2c); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    uVar5 = puVar1[1];
    pcVar2 = (code *)puVar1[2];
    eVar3 = param_1;
    piVar4 = this;
    guard_check_icall();
    (*pcVar2)(eVar3,piVar4,uVar5);
  }
  return;
}


