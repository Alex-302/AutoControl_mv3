// DloadLock @ 0047704f size=93 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x00477096) */
/* Library Function - Single Match
    void __stdcall DloadLock(void)
   
   Library: Visual Studio 2015 Release */

void DloadLock(void)

{
  code *pcVar1;
  uchar uVar2;
  
  uVar2 = DloadGetSRWLockFunctionPointers();
  pcVar1 = DAT_0049fc14;
  if (uVar2 == '\0') {
    do {
    } while (DAT_0049fc1c != 0);
    LOCK();
    DAT_0049fc1c = 1;
    UNLOCK();
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(&DAT_0049fc1c);
    (*pcVar1)();
  }
  return;
}


