// FUN_00456840 @ 00456840 size=185 callers=1

void __fastcall FUN_00456840(char *param_1,int *param_2)

{
  char cVar1;
  uint uVar2;
  void *this;
  undefined1 local_30 [8];
  undefined4 local_28 [4];
  char *local_18 [3];
  int local_c;
  
  cVar1 = *param_1;
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else if (cVar1 == '\x01') {
    uVar2 = *(uint *)(*(int *)(param_1 + 8) + 4);
  }
  else if (cVar1 == '\x02') {
    uVar2 = (*(int **)(param_1 + 8))[1] - **(int **)(param_1 + 8) >> 4;
  }
  else {
    uVar2 = 1;
  }
  if ((uint)(param_2[2] - *param_2) < uVar2) {
    FUN_0043d780(param_2,uVar2);
  }
  FUN_004340a0(param_1,local_28);
  FUN_00434120(this,local_18);
  FUN_00457f60(local_30,local_18[0],(int *)local_18._4_8_,SUB84(local_18._4_8_,4),local_c);
  return;
}


