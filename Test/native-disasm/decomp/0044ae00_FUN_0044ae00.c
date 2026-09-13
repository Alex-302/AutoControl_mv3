// FUN_0044ae00 @ 0044ae00 size=105 callers=2

void __fastcall FUN_0044ae00(char *param_1,char *param_2,undefined1 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char local_18 [8];
  undefined4 local_10;
  undefined4 local_c;
  
  for (; param_1 != param_2; param_1 = param_1 + 0x10) {
    FUN_00434940(local_18,param_3);
    cVar1 = *param_1;
    *param_1 = local_18[0];
    uVar2 = *(undefined4 *)(param_1 + 0xc);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_1 + 8) = local_10;
    *(undefined4 *)(param_1 + 0xc) = local_c;
    local_18[0] = cVar1;
    local_10 = uVar3;
    local_c = uVar2;
    FUN_00434820(local_18);
  }
  return;
}


