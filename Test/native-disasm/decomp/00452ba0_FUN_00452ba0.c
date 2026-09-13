// FUN_00452ba0 @ 00452ba0 size=181 callers=1

byte * __fastcall
FUN_00452ba0(byte *param_1,byte *param_2,undefined1 *param_3,undefined1 *param_4,int param_5)

{
  undefined1 uVar1;
  undefined **ppuVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  byte *pbVar6;
  
  pbVar6 = param_1;
  do {
    if ((pbVar6 == param_2) || (param_3 == param_4)) {
      if (param_3 == param_4) {
        param_1 = pbVar6;
      }
      return param_1;
    }
    uVar1 = *param_3;
    ppuVar2 = (undefined **)**(int **)(param_5 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar5 = __Tolower((uint)*pbVar6,(_Ctypevec *)(*(int **)(param_5 + 4) + 2));
      cVar3 = (char)iVar5;
    }
    else {
      cVar3 = (*(code *)ppuVar2[4])(*pbVar6);
    }
    ppuVar2 = (undefined **)**(int **)(param_5 + 4);
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar5 = __Tolower(CONCAT11(cVar3,uVar1) & 0xff,(_Ctypevec *)(*(int **)(param_5 + 4) + 2));
      cVar4 = (char)iVar5;
    }
    else {
      cVar4 = (*(code *)ppuVar2[4])(uVar1);
    }
    pbVar6 = pbVar6 + 1;
    param_3 = param_3 + 1;
  } while (cVar3 == cVar4);
  return param_1;
}


