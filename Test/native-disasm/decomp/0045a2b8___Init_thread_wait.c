// __Init_thread_wait @ 0045a2b8 size=101 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __Init_thread_wait
   
   Library: Visual Studio 2015 Release */

bool __cdecl __Init_thread_wait(DWORD param_1)

{
  int iVar1;
  DWORD DVar2;
  byte bVar3;
  uint uVar4;
  bool bVar5;
  undefined *puVar6;
  undefined *puVar7;
  
  if (DAT_0049f12c == (HANDLE)0x0) {
    uVar4 = DAT_0049d070 ^ _DAT_0049f130;
    bVar3 = (byte)DAT_0049d070 & 0x1f;
    puVar7 = &DAT_0049f110;
    puVar6 = &DAT_0049f128;
    guard_check_icall();
    iVar1 = (*(code *)(uVar4 >> bVar3 | uVar4 << 0x20 - bVar3))(puVar6,puVar7,param_1);
    bVar5 = iVar1 != 0;
  }
  else {
    FUN_0045a2ac();
    DVar2 = WaitForSingleObjectEx(DAT_0049f12c,param_1,0);
    FUN_0045a25f();
    bVar5 = DVar2 == 0;
  }
  return bVar5;
}


