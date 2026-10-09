// FUN_0044d910 @ 0044d910 size=88 callers=1

uint __fastcall FUN_0044d910(int *param_1)

{
  byte *pbVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  uint uVar3;
  
  if (*(int *)param_1[7] != 0) {
    iVar2 = *(int *)param_1[0xb];
    if (0 < iVar2) {
      *(int *)param_1[0xb] = iVar2 + -1;
      pbVar1 = *(byte **)param_1[7];
      *(byte **)param_1[7] = pbVar1 + 1;
      return (uint)*pbVar1;
    }
  }
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x1c);
  if (UNRECOVERED_JUMPTABLE == std::basic_streambuf<char,std::char_traits<char>_>::uflow) {
    iVar2 = (**(code **)(*param_1 + 0x18))();
    if (iVar2 == -1) {
      return 0xffffffff;
    }
    *(int *)param_1[0xb] = *(int *)param_1[0xb] + -1;
    pbVar1 = *(byte **)param_1[7];
    *(byte **)param_1[7] = pbVar1 + 1;
    return (uint)*pbVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x0044d966. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*UNRECOVERED_JUMPTABLE)();
  return uVar3;
}


