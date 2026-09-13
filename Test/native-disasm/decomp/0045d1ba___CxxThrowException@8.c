// __CxxThrowException@8 @ 0045d1ba size=110 callers=106

/* Library Function - Single Match
    __CxxThrowException@8
   
   Library: Visual Studio 2015 Release */

void __CxxThrowException_8(int *param_1,byte *param_2)

{
  code *pcVar1;
  int iVar2;
  int *piVar3;
  DWORD *pDVar4;
  DWORD *pDVar5;
  DWORD local_24 [4];
  DWORD local_14;
  ULONG_PTR local_10;
  int *local_c;
  byte *local_8;
  
  pDVar4 = &DAT_00483de0;
  pDVar5 = local_24;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pDVar5 = *pDVar4;
    pDVar4 = pDVar4 + 1;
    pDVar5 = pDVar5 + 1;
  }
  if ((param_2 != (byte *)0x0) && ((*param_2 & 0x10) != 0)) {
    piVar3 = (int *)(*param_1 + -4);
    pcVar1 = *(code **)(*piVar3 + 0x20);
    param_2 = *(byte **)(*piVar3 + 0x18);
    guard_check_icall();
    (*pcVar1)(piVar3);
  }
  local_c = param_1;
  if ((param_2 != (byte *)0x0) && ((*param_2 & 8) != 0)) {
    local_10 = 0x1994000;
  }
  local_8 = param_2;
  RaiseException(local_24[0],local_24[1],local_14,&local_10);
  return;
}


