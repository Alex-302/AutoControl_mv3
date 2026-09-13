// FUN_004108c0 @ 004108c0 size=311 callers=1

char * __fastcall FUN_004108c0(char *param_1)

{
  HRSRC hResInfo;
  HGLOBAL hResData;
  uint *puVar1;
  DWORD DVar2;
  uint uVar3;
  uint uVar4;
  void *local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  uint local_1c;
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a71e;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffc8;
  local_20 = 0;
  ExceptionList = &local_10;
  local_18 = param_1;
  hResInfo = FindResourceA((HMODULE)0x0,(LPCSTR)0x1,&DAT_0000000a);
  hResData = LoadResource((HMODULE)0x0,hResInfo);
  puVar1 = LockResource(hResData);
  DVar2 = SizeofResource((HMODULE)0x0,hResInfo);
  if ((puVar1 == (uint *)0x0) || (DVar2 == 0)) {
    local_8 = 3;
    *param_1 = '\0';
    FUN_004381d0(param_1 + 8,'\0');
  }
  else {
    local_1c = local_1c & 0xffffff00;
    local_2c = (void *)0x0;
    local_28 = 0;
    local_24 = 0;
    FUN_00447980(&local_2c,puVar1,DVar2 + (int)puVar1);
    uVar4 = 0;
    uVar3 = local_28 - (int)local_2c;
    if (uVar3 != 0) {
      do {
        *(char *)((int)local_2c + uVar4) =
             *(char *)((int)local_2c + uVar4) -
             ((char)((ulonglong)((uVar3 - uVar4) * (uVar3 - uVar4)) % 200) +
             (char)((ulonglong)(uVar4 * uVar4) % 200));
        uVar4 = uVar4 + 1;
        uVar3 = local_28 - (int)local_2c;
        param_1 = local_18;
      } while (uVar4 < uVar3);
    }
    local_8 = 1;
    FUN_00433c80(param_1,(int *)&local_2c);
    if (local_2c != (void *)0x0) {
      FUN_00402430(local_2c,local_24 - (int)local_2c,1);
      ExceptionList = local_10;
      return param_1;
    }
  }
  ExceptionList = local_10;
  return param_1;
}


