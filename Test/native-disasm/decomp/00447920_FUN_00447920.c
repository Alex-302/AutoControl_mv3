// FUN_00447920 @ 00447920 size=90 callers=2

void __fastcall FUN_00447920(void *param_1,void *param_2,int *param_3)

{
  void *this;
  undefined1 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 local_8 [2];
  
  for (; param_1 != param_2; param_1 = (void *)((int)param_1 + 0x10)) {
    puVar1 = (undefined1 *)FUN_00434550(param_1,1);
    iVar2 = FUN_00434550(param_1,0);
    this = *(void **)(*param_3 + 8);
    piVar3 = FUN_00447700(this,*(undefined4 **)(iVar2 + 8),puVar1);
    FUN_00447780(this,local_8,extraout_ECX,(byte *)(piVar3 + 4),piVar3);
  }
  return;
}


