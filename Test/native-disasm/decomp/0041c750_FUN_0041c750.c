// FUN_0041c750 @ 0041c750 size=299 callers=1

void FUN_0041c750(int *param_1,int param_2,int param_3,int *param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  char cVar6;
  
  if ((param_5 & 4) == 0) {
    cVar5 = (-((param_5 & 8) != 0) & 6U) + 0x4c;
  }
  else {
    cVar5 = 'C';
  }
  if ((param_5 & 0x10) == 0) {
    cVar6 = (-((param_5 & 0x20) != 0) & 0xeeU) + 0x54;
  }
  else {
    cVar6 = 'M';
  }
  if ((cVar5 == 'L') && (param_4[2] < *param_1 + param_2)) {
    cVar5 = 'R';
  }
  if ((cVar6 == 'T') && (param_4[3] < param_1[1] + param_3)) {
    cVar6 = 'B';
  }
  if ((cVar5 == 'R') && (*param_1 - param_2 < *param_4)) {
    cVar5 = 'L';
  }
  if ((cVar6 == 'B') && (param_1[1] - param_3 < param_4[1])) {
    cVar6 = 'T';
  }
  if (cVar5 == 'C') {
    iVar4 = param_2 / 2;
  }
  else {
    iVar4 = 0;
    if (cVar5 == 'R') {
      iVar4 = param_2;
    }
  }
  *param_1 = *param_1 - iVar4;
  if (cVar6 == 'M') {
    iVar4 = param_3 / 2;
  }
  else {
    iVar4 = 0;
    if (cVar6 == 'B') {
      iVar4 = param_3;
    }
  }
  param_1[1] = param_1[1] - iVar4;
  iVar4 = *param_1;
  iVar3 = *param_4 - iVar4;
  iVar1 = param_1[1];
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  iVar2 = (iVar4 - param_4[2]) + param_2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  *param_1 = (iVar4 - iVar2) + iVar3;
  iVar4 = param_4[1] - iVar1;
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  iVar3 = (iVar1 - param_4[3]) + param_3;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  param_1[1] = (iVar1 - iVar3) + iVar4;
  return;
}


