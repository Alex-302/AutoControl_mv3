// FID_conflict:operator() @ 00467d6a size=254 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Multiple Matches With Different Base Names
    public: void __thiscall <lambda_b57350f2640456a0859d250846f69caf>::operator()(void)const 
    public: void __thiscall <lambda_e378711a6f6581bf7f0efd7cdf97f5d9>::operator()(void)const 
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

void __fastcall FID_conflict_operator__(undefined4 *param_1)

{
  ushort uVar1;
  wchar_t *pwVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  bool bVar6;
  
  __copytlocinfo_nolock(*(undefined4 **)*param_1,*(undefined4 **)(*(int *)param_1[1] + 0x4c));
  pwVar2 = FUN_0046872c(*(int *)*param_1,*(int *)param_1[3],*(wchar_t **)param_1[4]);
  *(wchar_t **)param_1[2] = pwVar2;
  if (pwVar2 == (wchar_t *)0x0) {
    ___acrt_release_locale_ref(*(int *)*param_1);
    ___acrt_free_locale(*(void **)*param_1);
  }
  else {
    puVar3 = *(ushort **)param_1[4];
    if (puVar3 != (ushort *)0x0) {
      puVar5 = &DAT_0049d2f0;
      do {
        uVar1 = *puVar3;
        bVar6 = uVar1 < *puVar5;
        if (uVar1 != *puVar5) {
LAB_00467ddb:
          uVar4 = -(uint)bVar6 | 1;
          goto LAB_00467ddf;
        }
        if (uVar1 == 0) break;
        uVar1 = puVar3[1];
        bVar6 = uVar1 < puVar5[1];
        if (uVar1 != puVar5[1]) goto LAB_00467ddb;
        puVar3 = puVar3 + 2;
        puVar5 = puVar5 + 2;
      } while (uVar1 != 0);
      uVar4 = 0;
LAB_00467ddf:
      if (uVar4 != 0) {
        LOCK();
        DAT_0049f7f4 = 1;
        UNLOCK();
      }
    }
    __updatetlocinfoEx_nolock((undefined4 *)(*(int *)param_1[1] + 0x4c),*(undefined ***)*param_1);
    ___acrt_release_locale_ref(*(int *)*param_1);
    if (((*(byte *)(*(int *)param_1[1] + 0x350) & 2) == 0) && (((byte)DAT_0049d3f8 & 1) == 0)) {
      __updatetlocinfoEx_nolock(&DAT_0049fafc,*(undefined ***)(*(int *)param_1[1] + 0x4c));
      PTR_PTR_0049d1d0 = (undefined *)DAT_0049fafc[0x22];
      PTR_DAT_0049d1e0 = (undefined *)*DAT_0049fafc;
      _DAT_0049d22c = DAT_0049fafc[1];
      return;
    }
  }
  return;
}


