// FUN_00410150 @ 00410150 size=218 callers=2

bool __fastcall FUN_00410150(char param_1,char param_2)

{
  HANDLE hDevice;
  int iVar1;
  BOOL BVar2;
  int iVar3;
  undefined2 local_8;
  char local_6;
  DWORD local_4;
  
  hDevice = CreateFileA("\\\\.\\LCD",0xc0000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  if (hDevice == (HANDLE)0xffffffff) {
    return false;
  }
  local_8 = 0x3203;
  local_6 = '2';
  DeviceIoControl(hDevice,0x230498,(LPVOID)0x0,0,&local_8,3,&local_4,(LPOVERLAPPED)0x0);
  if ((local_8 & 1) != 0) {
    local_6 = local_8._1_1_;
  }
  if (param_2 != '\0') {
    iVar3 = (int)local_6 + (int)param_1;
    if ((iVar3 < 100) && (iVar3 < 0)) {
      param_1 = '\0';
    }
    else {
      iVar1 = 100;
      if (iVar3 < 100) {
        iVar1 = iVar3;
      }
      param_1 = (char)iVar1;
    }
  }
  local_8 = CONCAT11(param_1,(undefined1)local_8);
  local_6 = param_1;
  BVar2 = DeviceIoControl(hDevice,0x23049c,&local_8,3,(LPVOID)0x0,0,&local_4,(LPOVERLAPPED)0x0);
  CloseHandle(hDevice);
  return BVar2 != 0;
}


