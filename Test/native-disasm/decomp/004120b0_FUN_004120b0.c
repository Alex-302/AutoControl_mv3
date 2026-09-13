// FUN_004120b0 @ 004120b0 size=585 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004120b0(void)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  puVar1 = DAT_004a29a4;
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_004a29a4 != (undefined4 *)0x0) {
    ExceptionList = &local_10;
    GdipDeleteFont(*DAT_004a29a4);
    GdipFree(puVar1);
  }
  puVar1 = DAT_004a29a0;
  if (DAT_004a29a0 != (undefined4 *)0x0) {
    GdipDeleteFont(*DAT_004a29a0);
    GdipFree(puVar1);
  }
  puVar1 = DAT_004a299c;
  if (DAT_004a299c != (undefined4 *)0x0) {
    FUN_0041bff0(DAT_004a299c);
    FUN_0045a6a4(puVar1);
  }
  _eh_vector_destructor_iterator_(&DAT_004a298c,4,2,FUN_00422890);
  if (DAT_004a2978 != (void *)0x0) {
    FUN_00402430(DAT_004a2978,DAT_004a2980 - (int)DAT_004a2978 >> 2,4);
    DAT_004a2978 = (void *)0x0;
    _DAT_004a297c = 0;
    DAT_004a2980 = 0;
  }
  FUN_0043e550((int *)&DAT_004a2970);
  FID_conflict__free(DAT_004a2970);
  if (DAT_004a2958 != (void *)0x0) {
    FUN_00402430(DAT_004a2958,DAT_004a2960 - (int)DAT_004a2958 >> 2,4);
    DAT_004a2958 = (void *)0x0;
    _DAT_004a295c = 0;
    DAT_004a2960 = 0;
  }
  FUN_004361e0((int *)&DAT_004a2950);
  FID_conflict__free(DAT_004a2950);
  if (DAT_004a2938 != (void *)0x0) {
    FUN_00402430(DAT_004a2938,DAT_004a2940 - (int)DAT_004a2938 >> 2,4);
    DAT_004a2938 = (void *)0x0;
    _DAT_004a293c = 0;
    DAT_004a2940 = 0;
  }
  FUN_004362e0((int *)&DAT_004a2930);
  FID_conflict__free(DAT_004a2930);
  if (DAT_004a2918 != (void *)0x0) {
    FUN_00402430(DAT_004a2918,DAT_004a2920 - (int)DAT_004a2918 >> 2,4);
    DAT_004a2918 = (void *)0x0;
    _DAT_004a291c = 0;
    DAT_004a2920 = 0;
  }
  FUN_004362e0((int *)&DAT_004a2910);
  FID_conflict__free(DAT_004a2910);
  if (DAT_004a2900 != (uint *)0x0) {
    FUN_004479e0(DAT_004a2900,DAT_004a2904);
    FUN_00402430(DAT_004a2900,(DAT_004a2908 - (int)DAT_004a2900) / 0x28,0x28);
    DAT_004a2900 = (uint *)0x0;
    DAT_004a2904 = (uint *)0x0;
    DAT_004a2908 = 0;
  }
  FUN_00432980();
  ExceptionList = local_10;
  return;
}


