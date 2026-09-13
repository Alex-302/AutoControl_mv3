// FUN_00450960 @ 00450960 size=138 callers=1

int * __thiscall FUN_00450960(void *this,int *param_1,int *param_2)

{
  byte *pbVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  
  piVar3 = param_2 + 2;
  if (0xf < (uint)param_2[7]) {
    piVar3 = (int *)*piVar3;
  }
  uVar4 = 0;
  uVar5 = 0x811c9dc5;
  if (param_2[6] != 0) {
    do {
      pbVar1 = (byte *)((int)piVar3 + uVar4);
      uVar4 = uVar4 + 1;
      uVar5 = (*pbVar1 ^ uVar5) * 0x1000193;
    } while (uVar4 < (uint)param_2[6]);
  }
  iVar2 = (*(uint *)((int)this + 0x18) & uVar5) * 8;
  piVar3 = (int *)(*(int *)((int)this + 0xc) + iVar2);
  if ((int *)piVar3[1] == param_2) {
    if ((int *)*piVar3 == param_2) {
      *piVar3 = *(int *)((int)this + 4);
      *(undefined4 *)(*(int *)((int)this + 0xc) + 4 + iVar2) = *(undefined4 *)((int)this + 4);
    }
    else {
      piVar3[1] = param_2[1];
    }
  }
  else if ((int *)*piVar3 == param_2) {
    *piVar3 = *param_2;
  }
  FUN_00450d60((void *)((int)this + 4),param_1,param_2);
  return param_1;
}


