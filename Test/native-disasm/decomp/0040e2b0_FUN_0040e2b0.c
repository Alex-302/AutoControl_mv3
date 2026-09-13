// FUN_0040e2b0 @ 0040e2b0 size=231 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall FUN_0040e2b0(void *this,undefined4 *param_1)

{
  HRESULT HVar1;
  int *piVar2;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 auStack_34 [2];
  HRESULT local_2c;
  int *local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047a394;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_14 = 0;
  local_2c = HVar1;
  piVar2 = FUN_0040dbc0(&local_28,this);
  local_14._0_1_ = 1;
  piVar2 = FUN_0040b930(&local_24,piVar2,5);
  local_14._0_1_ = 2;
  local_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  auStack_34[0] = 0;
  piVar2 = (int *)*piVar2;
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x58))
              (piVar2,&local_40,&uStack_3c,&uStack_38,auStack_34,_DAT_0048e618,_UNK_0048e61c,
               _UNK_0048e620,_UNK_0048e624);
  }
  *param_1 = local_40;
  param_1[1] = uStack_3c;
  param_1[2] = uStack_38;
  param_1[3] = auStack_34[0];
  local_14._0_1_ = 3;
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  local_14 = CONCAT31(local_14._1_3_,4);
  if (local_28 != (int *)0x0) {
    (**(code **)(*local_28 + 8))(local_28);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  ExceptionList = local_1c;
  return param_1;
}


