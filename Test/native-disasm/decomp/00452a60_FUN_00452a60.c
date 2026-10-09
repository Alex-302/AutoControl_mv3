// FUN_00452a60 @ 00452a60 size=197 callers=1

void __fastcall
FUN_00452a60(undefined4 *param_1,byte *param_2,byte *param_3,byte *param_4,byte *param_5,int param_6
            )

{
  byte bVar1;
  undefined **ppuVar2;
  byte *pbVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  
  pbVar3 = param_3;
  do {
    if ((pbVar3 == param_4) || (param_2 == param_5)) {
      if (param_2 == param_5) {
        param_3 = pbVar3;
      }
      *param_1 = param_3;
      return;
    }
    bVar1 = *param_2;
    ppuVar2 = (undefined **)**(int **)(param_6 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar6 = __Tolower((uint)*pbVar3,(_Ctypevec *)(*(int **)(param_6 + 4) + 2));
      cVar4 = (char)iVar6;
    }
    else {
      cVar4 = (*(code *)ppuVar2[4])(*pbVar3);
    }
    ppuVar2 = (undefined **)**(int **)(param_6 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar6 = __Tolower((uint)bVar1,(_Ctypevec *)(*(int **)(param_6 + 4) + 2));
      cVar5 = (char)iVar6;
    }
    else {
      cVar5 = (*(code *)ppuVar2[4])(bVar1);
    }
    param_2 = param_2 + 1;
    pbVar3 = pbVar3 + 1;
  } while (cVar4 == cVar5);
  *param_1 = param_3;
  return;
}


