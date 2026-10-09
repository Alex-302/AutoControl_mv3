// FUN_00434820 @ 00434820 size=153 callers=942

void __fastcall FUN_00434820(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *local_4;
  
  cVar1 = *param_1;
  local_4 = param_1;
  if (cVar1 == '\x01') {
    puVar2 = *(undefined4 **)(param_1 + 8);
    FUN_0043d0d0(puVar2,&local_4,*(int **)*puVar2,(int *)*puVar2);
    FID_conflict__free((void *)*puVar2);
    FID_conflict__free(*(void **)(param_1 + 8));
  }
  else {
    if (cVar1 == '\x02') {
      FUN_00444df0(*(int **)(param_1 + 8));
      FID_conflict__free(*(void **)(param_1 + 8));
      return;
    }
    if (cVar1 == '\x03') {
      puVar2 = *(undefined4 **)(param_1 + 8);
      if (0xf < (uint)puVar2[5]) {
        FUN_00402430((void *)*puVar2,puVar2[5] + 1,1);
      }
      puVar2[5] = 0xf;
      puVar2[4] = 0;
      if (0xf < (uint)puVar2[5]) {
        puVar2 = (undefined4 *)*puVar2;
      }
      *(undefined1 *)puVar2 = 0;
      FID_conflict__free(*(void **)(param_1 + 8));
      return;
    }
  }
  return;
}


