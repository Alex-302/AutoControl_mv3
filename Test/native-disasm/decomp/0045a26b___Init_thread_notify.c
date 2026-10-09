// __Init_thread_notify @ 0045a26b size=65 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __Init_thread_notify
   
   Library: Visual Studio 2015 Release */

void __Init_thread_notify(void)

{
  byte bVar1;
  uint uVar2;
  undefined *puVar3;
  
  if (DAT_0049f12c == (HANDLE)0x0) {
    uVar2 = DAT_0049d070 ^ _DAT_0049f134;
    bVar1 = (byte)DAT_0049d070 & 0x1f;
    puVar3 = &DAT_0049f128;
    guard_check_icall();
    (*(code *)(uVar2 >> bVar1 | uVar2 << 0x20 - bVar1))(puVar3);
    return;
  }
  SetEvent(DAT_0049f12c);
  ResetEvent(DAT_0049f12c);
  return;
}


