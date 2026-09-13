// FUN_004563d0 @ 004563d0 size=123 callers=1

bool __fastcall FUN_004563d0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (((param_1[0x14] & 0x4000U) == 0) || ((char)param_1[0x12] != '\\')) {
    if ((param_1[0x14] & 0x20000U) != 0) {
      uVar1 = FUN_00453ad0(param_1,'\0');
      if ((char)uVar1 != '\0') {
        return true;
      }
    }
    iVar2 = FUN_004553d0(param_1,10,0x7fffffff);
    if (iVar2 == 0x7fffffff) {
      uVar1 = FUN_00453c90(param_1);
      return (char)uVar1 != '\0';
    }
    if (param_1[0x11] != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458f04(2);
    }
  }
  else {
    param_1[0x11] = 0x5c;
    FUN_0044dfd0(param_1);
  }
  return true;
}


