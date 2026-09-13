// __umatherr @ 0046d00f size=162 callers=2

/* Library Function - Single Match
    __umatherr
   
   Library: Visual Studio 2015 Release */

float10 __cdecl
__umatherr(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  double dVar1;
  int iVar2;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 uStack_8;
  
  local_20 = 0;
  iVar2 = 0;
  do {
    if ((&DAT_00486998)[iVar2 * 2] == param_2) {
      local_20 = *(int *)(&UNK_0048699c + iVar2 * 8);
      break;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x1d);
  if (local_20 == 0) {
    __ctrlfp();
    __set_errno_from_matherr(param_1);
    dVar1 = (double)CONCAT44(param_8,param_7);
  }
  else {
    local_1c = param_3;
    local_18 = param_4;
    local_14 = param_5;
    local_10 = param_6;
    local_c = param_7;
    local_24 = param_1;
    uStack_8 = param_8;
    __ctrlfp();
    iVar2 = ___acrt_invoke_user_matherr(&local_24);
    if (iVar2 == 0) {
      __set_errno_from_matherr(param_1);
    }
    dVar1 = (double)CONCAT44(uStack_8,local_c);
  }
  return (float10)dVar1;
}


