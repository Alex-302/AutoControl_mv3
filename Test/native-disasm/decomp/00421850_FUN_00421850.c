// FUN_00421850 @ 00421850 size=258 callers=1

void * __thiscall FUN_00421850(void *this,void *param_1)

{
  int *piVar1;
  _Locimp *p_Var2;
  _Facet_base *p_Var3;
  char *pcVar4;
  void *pvVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  void **ppvVar8;
  void *local_34 [5];
  uint local_20;
  undefined4 *local_1c;
  void *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047bc51;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  local_8 = 0;
  local_1c = (undefined4 *)((int)this + 4);
  local_18 = this;
  p_Var2 = std::locale::_Init(true);
  *(_Locimp **)((int)this + 0x10) = p_Var2;
  local_8 = 1;
  p_Var3 = FUN_004436c0((void *)((int)this + 0xc));
  *(undefined4 *)((int)this + 4) = p_Var3;
  p_Var3 = FUN_00440660((int)this + 0xc);
  pvVar5 = param_1;
  *(_Facet_base **)((int)this + 8) = p_Var3;
  local_8 = 2;
  pcVar4 = (char *)FUN_00440dd0(param_1,(uint *)&DAT_0048d7bc);
  FUN_004536b0(pcVar4,(uint *)&param_1);
  *(undefined1 *)((int)this + 0x14) = param_1._0_1_;
  ppvVar8 = local_34;
  pvVar5 = (void *)FUN_00440dd0(pvVar5,(uint *)"regex");
  puVar6 = FUN_00440bb0(pvVar5,ppvVar8);
  local_8 = CONCAT31(local_8._1_3_,3);
  param_1 = (void *)((uint)param_1 & 0xffffff00);
  puVar7 = puVar6;
  if (0xf < (uint)puVar6[5]) {
    puVar7 = (undefined4 *)*puVar6;
  }
  piVar1 = puVar6 + 4;
  if (0xf < (uint)puVar6[5]) {
    puVar6 = (undefined4 *)*puVar6;
  }
  FUN_00446e40(this,puVar6,*piVar1 + (int)puVar7);
  if (0xf < local_20) {
    FUN_00402430(local_34[0],local_20 + 1,1);
  }
  ExceptionList = local_10;
  return this;
}


