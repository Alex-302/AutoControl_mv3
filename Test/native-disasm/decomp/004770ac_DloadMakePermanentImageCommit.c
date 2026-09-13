// DloadMakePermanentImageCommit @ 004770ac size=114 callers=1

/* Library Function - Single Match
    void __stdcall DloadMakePermanentImageCommit(void *,unsigned long)
   
   Library: Visual Studio 2015 Release */

void DloadMakePermanentImageCommit(void *param_1,ulong param_2)

{
  code *pcVar1;
  SIZE_T SVar2;
  int iVar3;
  undefined4 *puVar4;
  _SYSTEM_INFO local_44;
  _MEMORY_BASIC_INFORMATION local_20;
  
  SVar2 = VirtualQuery(param_1,&local_20,0x1c);
  if (SVar2 == 0) {
    pcVar1 = (code *)swi(0x29);
    (*pcVar1)();
  }
  if (((byte)local_20.Protect & 0x44) != 0) {
    GetSystemInfo(&local_44);
    puVar4 = (undefined4 *)(~(local_44.dwPageSize - 1) & (uint)param_1);
    for (iVar3 = (((local_44.dwPageSize - 1 & param_2) - 1) +
                 (local_44.dwPageSize - 1 & (uint)param_1) + local_44.dwPageSize) /
                 local_44.dwPageSize + param_2 / local_44.dwPageSize; iVar3 != 0; iVar3 = iVar3 + -1
        ) {
      LOCK();
      *puVar4 = *puVar4;
      UNLOCK();
      puVar4 = (undefined4 *)((int)puVar4 + local_44.dwPageSize);
    }
  }
  return;
}


