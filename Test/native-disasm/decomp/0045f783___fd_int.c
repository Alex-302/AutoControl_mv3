// __fd_int @ 0045f783 size=207 callers=2

/* Library Function - Single Match
    __fd_int
   
   Library: Visual Studio 2015 Release */

int __cdecl __fd_int(ushort *param_1,int param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  uint uVar4;
  
  uVar3 = param_1[1];
  uVar4 = uVar3 >> 7 & 0xff;
  if ((short)uVar4 == 0xff) {
    if (((uVar3 & 0x7f) == 0) && (*param_1 == 0)) {
      iVar2 = 1;
    }
    else {
      iVar2 = 2;
    }
  }
  else if (((uVar3 & 0x7fff) == 0) && (*param_1 == 0)) {
    iVar2 = 0;
  }
  else {
    uVar4 = (0x96 - uVar4) - param_2;
    sVar1 = (short)uVar4;
    if (sVar1 < 1) {
      iVar2 = 0;
    }
    else if (sVar1 < 0x18) {
      uVar3 = *(ushort *)(&DAT_00484628 + (uVar4 & 0xf) * 2) &
              param_1[*(int *)(&DAT_00484648 + (sVar1 >> 4) * 4)];
      param_1[*(int *)(&DAT_00484648 + (sVar1 >> 4) * 4)] =
           param_1[*(int *)(&DAT_00484648 + (sVar1 >> 4) * 4)] ^ uVar3;
      if (0 < sVar1 >> 4) {
        uVar3 = uVar3 | *param_1;
        *param_1 = 0;
      }
      iVar2 = (uVar3 == 0) - 1;
    }
    else {
      *param_1 = 0;
      iVar2 = -1;
      param_1[1] = uVar3 & 0x8000;
    }
  }
  return iVar2;
}


