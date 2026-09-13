// DloadReleaseSectionWriteAccess @ 00477211 size=56 callers=4

/* Library Function - Single Match
    void __stdcall DloadReleaseSectionWriteAccess(void)
   
   Library: Visual Studio 2015 Release */

void DloadReleaseSectionWriteAccess(void)

{
  ulong local_8;
  
  if ((IMAGE_LOAD_CONFIG_DIRECTORY32_0048cac8.GuardFlags & IMAGE_GUARD_PROTECT_DELAYLOAD_IAT) != 0)
  {
    DloadLock();
    DAT_0049fc20 = DAT_0049fc20 + -1;
    if (DAT_0049fc20 == 0) {
      DloadProtectSection(DAT_0049fc24,&local_8);
    }
    DloadUnlock();
  }
  return;
}


