// ___vcrt_initialize_winapi_thunks @ 0045ef08 size=58 callers=1

/* Library Function - Single Match
    ___vcrt_initialize_winapi_thunks
   
   Library: Visual Studio 2015 Release */

void ___vcrt_initialize_winapi_thunks(void)

{
  byte bVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  
  puVar2 = &DAT_0049f4b0;
  bVar1 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
  iVar3 = 0;
  uVar4 = (0U >> bVar1 | 0 << 0x20 - bVar1) ^ DAT_0049d070;
  do {
    iVar3 = iVar3 + 1;
    *puVar2 = uVar4;
    puVar2 = puVar2 + 1;
  } while (iVar3 != 9);
  return;
}


