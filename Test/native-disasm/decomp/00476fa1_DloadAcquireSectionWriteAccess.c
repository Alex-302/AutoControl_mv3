// DloadAcquireSectionWriteAccess @ 00476fa1 size=51 callers=2

/* Library Function - Single Match
    void __stdcall DloadAcquireSectionWriteAccess(void)
   
   Library: Visual Studio 2015 Release */

void DloadAcquireSectionWriteAccess(void)

{
  if ((IMAGE_LOAD_CONFIG_DIRECTORY32_0048cac8.GuardFlags & IMAGE_GUARD_PROTECT_DELAYLOAD_IAT) != 0)
  {
    DloadLock();
    DAT_0049fc20 = DAT_0049fc20 + 1;
    if (DAT_0049fc20 == 1) {
      DloadProtectSection(4,&DAT_0049fc24);
    }
    DloadUnlock();
    return;
  }
  return;
}


