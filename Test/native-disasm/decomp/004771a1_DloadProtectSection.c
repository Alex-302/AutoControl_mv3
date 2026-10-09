// DloadProtectSection @ 004771a1 size=112 callers=2

/* Library Function - Single Match
    void __stdcall DloadProtectSection(unsigned long,unsigned long *)
   
   Library: Visual Studio 2015 Release */

void DloadProtectSection(ulong param_1,ulong *param_2)

{
  code *pcVar1;
  void *lpAddress;
  BOOL BVar2;
  uint local_c;
  ulong local_8;
  
  lpAddress = DloadObtainSection(&local_8,&local_c);
  if (lpAddress == (void *)0x0) {
    *param_2 = 4;
  }
  else {
    if (DAT_0049fc28 == 0) {
      DAT_0049fc28 = 1;
      if ((local_c & 0x80000000) == 0) {
        pcVar1 = (code *)swi(0x29);
        (*pcVar1)();
      }
      DloadMakePermanentImageCommit(lpAddress,local_8);
    }
    BVar2 = VirtualProtect(lpAddress,local_8,param_1,param_2);
    if (BVar2 == 0) {
      pcVar1 = (code *)swi(0x29);
      (*pcVar1)();
    }
  }
  return;
}


