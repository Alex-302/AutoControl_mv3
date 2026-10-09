// FUN_0042c850 @ 0042c850 size=191 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042c850(undefined4 *param_1)

{
  undefined **local_60;
  undefined4 local_5c;
  undefined ***local_3c;
  undefined **local_38;
  undefined *local_34;
  undefined ***local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047cd80;
  local_10 = ExceptionList;
  local_5c = *param_1;
  local_3c = &local_60;
  local_60 = &PTR_LAB_0048e770;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00417e10(&DAT_004a24d0,'\0');
  FUN_00433380(&DAT_004a24d0,(int *)&local_60);
  local_14 = &local_38;
  _DAT_004a2500 = 0;
  local_38 = &PTR_LAB_0048e8d8;
  local_34 = &DAT_004a24d0;
  local_8 = CONCAT31(local_8._1_3_,1);
  _DAT_004a24f8 = FUN_0040fd50(1000,(int *)local_14);
  if (local_14 != (undefined ***)0x0) {
    (*(code *)(*local_14)[4])(local_14 != &local_38);
  }
  if (local_3c != (undefined ***)0x0) {
    (*(code *)(*local_3c)[4])(local_3c != &local_60);
  }
  ExceptionList = local_10;
  return;
}


