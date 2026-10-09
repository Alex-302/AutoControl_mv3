// ~_Fac_node @ 004588af size=95 callers=1

/* Library Function - Single Match
    public: __thiscall std::_Fac_node::~_Fac_node(void)
   
   Library: Visual Studio 2015 Release */

void __thiscall std::_Fac_node::~_Fac_node(_Fac_node *this)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ed5d;
  local_10 = ExceptionList;
  uVar2 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcVar1 = *(code **)(**(int **)(this + 4) + 8);
  guard_check_icall();
  puVar3 = (undefined4 *)(*pcVar1)(uVar2);
  if (puVar3 != (undefined4 *)0x0) {
    uVar4 = 1;
    pcVar1 = *(code **)*puVar3;
    guard_check_icall();
    (*pcVar1)(uVar4);
  }
  ExceptionList = local_10;
  return;
}


