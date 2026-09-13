// FUN_00448030 @ 00448030 size=146 callers=1

char * __fastcall FUN_00448030(undefined1 *param_1,undefined1 *param_2,char *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined1 *puVar5;
  char local_18 [8];
  undefined4 local_10;
  undefined4 local_c;
  
  if (param_1 == param_2) {
    return param_3;
  }
  do {
    cVar1 = param_2[-0x10];
    puVar5 = param_2 + -0x10;
    pcVar4 = param_3 + -0x10;
    uVar2 = *(undefined4 *)(param_2 + -8);
    uVar3 = *(undefined4 *)(param_2 + -4);
    *puVar5 = 0;
    *(undefined4 *)(param_2 + -8) = 0;
    *(undefined4 *)(param_2 + -4) = 0;
    local_18[0] = *pcVar4;
    *pcVar4 = cVar1;
    local_10 = *(undefined4 *)(param_3 + -8);
    local_c = *(undefined4 *)(param_3 + -4);
    *(undefined4 *)(param_3 + -8) = uVar2;
    *(undefined4 *)(param_3 + -4) = uVar3;
    FUN_00434820(local_18);
    param_3 = pcVar4;
    param_2 = puVar5;
  } while (puVar5 != param_1);
  return pcVar4;
}


