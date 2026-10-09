// FUN_0043c970 @ 0043c970 size=57 callers=2

void __fastcall FUN_0043c970(void *param_1)

{
  int *piVar1;
  int *piVar2;
  int local_10 [3];
  
  piVar1 = *(int **)((int)param_1 + 4);
  if ((int *)*piVar1 != piVar1) {
    piVar1 = (int *)piVar1[1];
    do {
      piVar2 = (int *)**(undefined4 **)((int)param_1 + 4);
      FUN_00443460(param_1,local_10,(byte *)(piVar2 + 2),piVar2);
    } while (piVar2 != piVar1);
  }
  return;
}


