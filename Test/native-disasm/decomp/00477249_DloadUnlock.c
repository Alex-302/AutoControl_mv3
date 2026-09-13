// DloadUnlock @ 00477249 size=74 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    void __stdcall DloadUnlock(void)
   
   Library: Visual Studio 2015 Release */

void DloadUnlock(void)

{
  code *pcVar1;
  uchar uVar2;
  
  uVar2 = DloadGetSRWLockFunctionPointers();
  pcVar1 = DAT_0049fc18;
  if (uVar2 == '\0') {
    DAT_0049fc1c = 0;
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(&DAT_0049fc1c);
    (*pcVar1)();
  }
  return;
}


