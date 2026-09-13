// setmbcp_internal @ 004708c1 size=257 callers=1

/* Library Function - Single Match
    int __cdecl setmbcp_internal(int,bool)
   
   Library: Visual Studio 2015 Release */

int __cdecl setmbcp_internal(int param_1,bool param_2)

{
  int iVar1;
  __crt_multibyte_data *p_Var2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  __crt_multibyte_data *p_Var6;
  __acrt_ptd **local_10 [2];
  __acrt_ptd *local_8;
  
  local_8 = FUN_0046aa74();
  ___acrt_update_thread_multibyte_data();
  local_10[0] = (__acrt_ptd **)getSystemCP(param_1);
  if (local_10[0] == *(__acrt_ptd ***)(*(int *)(local_8 + 0x48) + 4)) {
    return 0;
  }
  p_Var2 = __malloc_base(0x220);
  if (p_Var2 != (__crt_multibyte_data *)0x0) {
    puVar5 = *(undefined4 **)(local_8 + 0x48);
    p_Var6 = p_Var2;
    for (iVar4 = 0x88; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)p_Var6 = *puVar5;
      puVar5 = puVar5 + 1;
      p_Var6 = p_Var6 + 4;
    }
    *(undefined4 *)p_Var2 = 0;
    iVar4 = __setmbcp_nolock((int)local_10[0],p_Var2);
    if (iVar4 != -1) {
      if (!param_2) {
        ___acrt_set_locale_changed();
      }
      piVar3 = *(int **)(local_8 + 0x48);
      LOCK();
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if ((iVar1 == 1) && (*(undefined4 **)(local_8 + 0x48) != &DAT_0049d788)) {
        FID_conflict__free(*(void **)(local_8 + 0x48));
      }
      *(undefined4 *)p_Var2 = 1;
      p_Var6 = (__crt_multibyte_data *)0x0;
      *(__crt_multibyte_data **)(local_8 + 0x48) = p_Var2;
      if ((((byte)local_8[0x350] & 2) == 0) && (((byte)DAT_0049d3f8 & 1) == 0)) {
        local_10[0] = &local_8;
        __acrt_lock_and_call<<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c>_>
                  (5,(<lambda_ad1ced32f4ac17aa236e5ef05d6b3b7c> *)local_10);
        if (param_2) {
          PTR_DAT_0049d2ec = PTR_DAT_0049d9a8;
        }
      }
      goto LAB_00470938;
    }
    piVar3 = __errno();
    *piVar3 = 0x16;
  }
  iVar4 = -1;
  p_Var6 = p_Var2;
LAB_00470938:
  FID_conflict__free(p_Var6);
  return iVar4;
}


