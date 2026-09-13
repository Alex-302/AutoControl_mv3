// initialize_lc_time @ 004717f3 size=637 callers=1

/* Library Function - Single Match
    bool __cdecl initialize_lc_time(struct __crt_lc_time_data * const,struct __crt_locale_data *
   const)
   
   Library: Visual Studio 2015 Release */

bool __cdecl initialize_lc_time(__crt_lc_time_data *param_1,__crt_locale_data *param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  wchar_t *pwVar18;
  uint uVar19;
  __crt_locale_data *local_18;
  undefined4 local_14;
  int local_10;
  wchar_t *local_c;
  __crt_lc_time_data *local_8;
  
  local_14 = 0;
  pwVar18 = *(wchar_t **)(param_2 + 0xb4);
  local_18 = param_2;
  local_c = pwVar18;
  pwVar1 = FUN_00467e68(pwVar18);
  uVar17 = 0;
  *(wchar_t **)(param_1 + 0x160) = pwVar1;
  local_8 = (__crt_lc_time_data *)0x31;
  local_10 = 7;
  do {
    uVar16 = ((int)local_8 - 0x30U) % 7;
    uVar2 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,(uint)local_8,
                         (int *)(param_1 + uVar16 * 4));
    uVar19 = (int)local_8 - 7;
    uVar3 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,local_c,uVar19,
                         (int *)(param_1 + uVar16 * 4 + 0x1c));
    uVar4 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,local_c,(uint)local_8,
                         (int *)(param_1 + uVar16 * 4 + 0xb4));
    pwVar18 = local_c;
    uVar16 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,local_c,uVar19,
                          (int *)(param_1 + uVar16 * 4 + 0xd0));
    uVar17 = uVar17 | uVar2 | uVar3 | uVar4 | uVar16;
    local_8 = (__crt_lc_time_data *)((int)local_8 + 1);
    local_10 = local_10 + -1;
  } while (local_10 != 0);
  local_8 = param_1 + 0x68;
  local_c = (wchar_t *)0x38;
  local_10 = 0xc;
  do {
    uVar4 = (int)local_c + 0xc;
    uVar2 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,uVar4,(int *)(local_8 + -0x30)
                        );
    uVar3 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,(uint)local_c,(int *)local_8);
    uVar4 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,uVar4,(int *)(local_8 + 0x84))
    ;
    pwVar1 = local_c;
    uVar16 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,(uint)local_c,
                          (int *)(local_8 + 0xb4));
    uVar17 = uVar17 | uVar2 | uVar3 | uVar4 | uVar16;
    local_8 = local_8 + 4;
    local_c = (wchar_t *)((int)pwVar1 + 1);
    local_10 = local_10 + -1;
  } while (local_10 != 0);
  iVar5 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,0x28,(int *)(param_1 + 0x98));
  iVar6 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,0x29,(int *)(param_1 + 0x9c));
  iVar7 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,0x28,(int *)(param_1 + 0x14c));
  iVar8 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,0x29,(int *)(param_1 + 0x150));
  iVar9 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,0x1f,(int *)(param_1 + 0xa0));
  iVar10 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,0x20,(int *)(param_1 + 0xa4));
  iVar11 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,1,pwVar18,0x1003,(int *)(param_1 + 0xa8))
  ;
  iVar12 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,0,pwVar18,0x1009,(int *)(param_1 + 0xac))
  ;
  iVar13 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,0x1f,(int *)(param_1 + 0x154));
  iVar14 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,0x20,(int *)(param_1 + 0x158));
  iVar15 = FUN_0046e1c8((__crt_locale_pointers *)&local_18,2,pwVar18,0x1003,(int *)(param_1 + 0x15c)
                       );
  return (bool)('\x01' - (iVar15 != 0 ||
                         ((((((((((uVar17 != 0 || iVar5 != 0) || iVar6 != 0) || iVar7 != 0) ||
                               iVar8 != 0) || iVar9 != 0) || iVar10 != 0) || iVar11 != 0) ||
                           iVar12 != 0) || iVar13 != 0) || iVar14 != 0)));
}


