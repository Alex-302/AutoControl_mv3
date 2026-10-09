// FUN_0041dfe0 @ 0041dfe0 size=322 callers=1

void __fastcall FUN_0041dfe0(HMENU param_1)

{
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  char local_88 [8];
  undefined8 local_80;
  undefined1 local_78 [8];
  undefined8 local_70;
  char local_68 [4];
  tagMENUINFO local_64;
  char local_48 [16];
  char local_38 [16];
  char local_28 [4];
  undefined1 *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047b8e4;
  local_1c = ExceptionList;
  local_88[0] = '\0';
  local_80 = 0;
  ExceptionList = &local_1c;
  FUN_00451110(local_88,(uint *)"itemId");
  local_64.cbSize = 0x1c;
  local_64.fMask = 8;
  local_64.dwStyle = 0;
  local_64.cyMax = 0;
  local_64.hbrBack = (HBRUSH)0x0;
  local_64.dwContextHelpID = 0;
  local_64.dwMenuData = 0;
  GetMenuInfo(param_1,&local_64);
  local_78[0] = 0;
  local_70 = 0;
  FUN_00451040(local_78,local_64.dwMenuData);
  local_14 = 0;
  FUN_00434b50(local_38,local_88,local_68,'\x01','\x02');
  local_14 = CONCAT31(local_14._1_3_,2);
  _eh_vector_destructor_iterator_(local_88,0x10,2,FUN_00434820);
  local_24 = &stack0xffffff60;
  local_14._0_1_ = 4;
  local_14._1_3_ = 0;
  uStack_a8 = 0x41e0ba;
  FUN_004381d0(&stack0xffffff68,'\0');
  local_14._0_1_ = 5;
  FUN_00434b50(auStack_b0,local_38,local_28,'\x01','\x02');
  local_14._0_1_ = 3;
  FUN_00408a00(local_48,0x30c);
  local_14 = CONCAT31(local_14._1_3_,7);
  _eh_vector_destructor_iterator_(local_38,0x10,1,FUN_00434820);
  FUN_0041db40(param_1,local_48);
  FUN_00434820(local_48);
  ExceptionList = local_1c;
  return;
}


