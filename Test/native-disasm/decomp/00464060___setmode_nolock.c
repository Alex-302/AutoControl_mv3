// __setmode_nolock @ 00464060 size=209 callers=1

/* Library Function - Single Match
    __setmode_nolock
   
   Library: Visual Studio 2015 Release */

int __cdecl __setmode_nolock(int _FileHandle,int _Mode)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = _FileHandle >> 6;
  iVar4 = (_FileHandle & 0x3fU) * 0x30;
  iVar3 = (&DAT_0049f8f8)[iVar5];
  bVar1 = *(byte *)(iVar3 + 0x28 + iVar4);
  cVar2 = *(char *)(iVar3 + 0x29 + iVar4);
  if (_Mode == 0x4000) {
    *(byte *)(iVar3 + 0x28 + iVar4) = bVar1 | 0x80;
    *(undefined1 *)((&DAT_0049f8f8)[iVar5] + 0x29 + iVar4) = 0;
  }
  else if (_Mode == 0x8000) {
    *(byte *)(iVar3 + 0x28 + iVar4) = bVar1 & 0x7f;
  }
  else if ((_Mode == 0x10000) || (_Mode == 0x20000)) {
    *(byte *)(iVar3 + 0x28 + iVar4) = bVar1 | 0x80;
    *(undefined1 *)((&DAT_0049f8f8)[iVar5] + 0x29 + iVar4) = 2;
  }
  else if (_Mode == 0x40000) {
    *(byte *)(iVar3 + 0x28 + iVar4) = bVar1 | 0x80;
    *(undefined1 *)((&DAT_0049f8f8)[iVar5] + 0x29 + iVar4) = 1;
  }
  if ((bVar1 & 0x80) == 0) {
    iVar3 = 0x8000;
  }
  else if (cVar2 == '\0') {
    iVar3 = 0x4000;
  }
  else {
    iVar3 = ((cVar2 != '\x01') - 1 & 0x30000) + 0x10000;
  }
  return iVar3;
}


