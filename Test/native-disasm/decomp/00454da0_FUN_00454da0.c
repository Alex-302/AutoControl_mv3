// FUN_00454da0 @ 00454da0 size=186 callers=1

void * __thiscall
FUN_00454da0(void *this,byte *param_1,byte *param_2,byte *param_3,byte *param_4,int param_5)

{
  byte bVar1;
  undefined **ppuVar2;
  byte *pbVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  bool bVar7;
  
  pbVar3 = param_1;
  do {
    if (pbVar3 == param_2) {
      bVar7 = param_3 == param_4;
LAB_00454e32:
      if (bVar7) {
        param_1 = pbVar3;
      }
      break;
    }
    bVar7 = true;
    if (param_3 == param_4) goto LAB_00454e32;
    bVar1 = *param_3;
    ppuVar2 = (undefined **)**(int **)(param_5 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar6 = __Tolower((uint)*pbVar3,(_Ctypevec *)(*(int **)(param_5 + 4) + 2));
      cVar4 = (char)iVar6;
    }
    else {
      cVar4 = (*(code *)ppuVar2[4])(*pbVar3);
    }
    ppuVar2 = (undefined **)**(int **)(param_5 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar6 = __Tolower((uint)bVar1,(_Ctypevec *)(*(int **)(param_5 + 4) + 2));
      cVar5 = (char)iVar6;
    }
    else {
      cVar5 = (*(code *)ppuVar2[4])(bVar1);
    }
    pbVar3 = pbVar3 + 1;
    param_3 = param_3 + 1;
  } while (cVar4 == cVar5);
  *(byte **)this = param_1;
  return this;
}


