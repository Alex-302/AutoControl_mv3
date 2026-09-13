// FUN_004569a0 @ 004569a0 size=111 callers=1

uint __fastcall FUN_004569a0(int *param_1,int param_2,int *param_3)

{
  uint uVar1;
  uint in_EAX;
  undefined3 uVar2;
  uint uVar3;
  
  uVar3 = param_2 - (int)param_1;
  while (uVar1 = uVar3 - 4, 3 < uVar3) {
    in_EAX = *param_1;
    if (in_EAX != *param_3) goto LAB_004569c6;
    param_1 = param_1 + 1;
    param_3 = param_3 + 1;
    uVar3 = uVar1;
  }
  if (uVar1 != 0xfffffffc) {
LAB_004569c6:
    uVar2 = (undefined3)(in_EAX >> 8);
    in_EAX = CONCAT31(uVar2,(char)*param_1);
    if (((char)*param_1 != (char)*param_3) ||
       ((uVar1 != 0xfffffffd &&
        ((in_EAX = CONCAT31(uVar2,*(char *)((int)param_1 + 1)),
         *(char *)((int)param_1 + 1) != *(char *)((int)param_3 + 1) ||
         ((uVar1 != 0xfffffffe &&
          ((in_EAX = CONCAT31(uVar2,*(char *)((int)param_1 + 2)),
           *(char *)((int)param_1 + 2) != *(char *)((int)param_3 + 2) ||
           ((uVar1 != 0xffffffff &&
            (in_EAX = CONCAT31(uVar2,*(char *)((int)param_1 + 3)),
            *(char *)((int)param_1 + 3) != *(char *)((int)param_3 + 3))))))))))))) {
      return in_EAX & 0xffffff00;
    }
  }
  return CONCAT31((int3)(in_EAX >> 8),1);
}


