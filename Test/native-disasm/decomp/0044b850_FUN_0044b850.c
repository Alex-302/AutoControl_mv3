// FUN_0044b850 @ 0044b850 size=85 callers=1

void __fastcall FUN_0044b850(int param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char local_10 [8];
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00416fe0(local_10,(undefined4 *)**(undefined4 **)(param_1 + 8),0x7fffffff);
  pcVar2 = *(char **)(param_1 + 4);
  cVar1 = *pcVar2;
  *pcVar2 = local_10[0];
  uVar3 = *(undefined4 *)(pcVar2 + 8);
  uVar4 = *(undefined4 *)(pcVar2 + 0xc);
  *(undefined4 *)(pcVar2 + 8) = local_8;
  *(undefined4 *)(pcVar2 + 0xc) = local_4;
  local_10[0] = cVar1;
  local_8 = uVar3;
  local_4 = uVar4;
  FUN_00434820(local_10);
  return;
}


