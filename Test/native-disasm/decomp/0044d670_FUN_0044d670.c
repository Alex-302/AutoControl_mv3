// FUN_0044d670 @ 0044d670 size=156 callers=1

void __fastcall FUN_0044d670(undefined4 *param_1)

{
  void *pvVar1;
  void *pvVar2;
  
  *param_1 = &PTR_FUN_0048e838;
  pvVar2 = (void *)param_1[5];
  while (pvVar2 != (void *)0x0) {
    pvVar1 = *(void **)((int)pvVar2 + 0x10);
    FID_conflict__free(*(void **)((int)pvVar2 + 0xc));
    FUN_0045a6a4(pvVar2);
    pvVar2 = pvVar1;
  }
  FUN_0045a6a4((void *)param_1[6]);
  pvVar2 = (void *)param_1[7];
  if (pvVar2 != (void *)0x0) {
    FID_conflict__free(*(void **)((int)pvVar2 + 8));
    FUN_0045a6a4(pvVar2);
  }
  pvVar2 = (void *)param_1[8];
  if (pvVar2 != (void *)0x0) {
    FID_conflict__free(*(void **)((int)pvVar2 + 8));
    FUN_0045a6a4(pvVar2);
  }
  pvVar2 = (void *)param_1[10];
  while (pvVar2 != (void *)0x0) {
    pvVar1 = *(void **)((int)pvVar2 + 0x10);
    FID_conflict__free(*(void **)((int)pvVar2 + 0xc));
    FUN_0045a6a4(pvVar2);
    pvVar2 = pvVar1;
  }
  *param_1 = &PTR_LAB_0048ecb0;
  return;
}


