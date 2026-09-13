// FUN_00457a70 @ 00457a70 size=162 callers=2

undefined4 __fastcall FUN_00457a70(byte *param_1,byte *param_2,int param_3,int *param_4)

{
  byte bVar1;
  undefined **ppuVar2;
  char cVar3;
  int in_EAX;
  int iVar4;
  uint uVar5;
  
  if (param_1 != param_2) {
    in_EAX = param_3 - (int)param_1;
    do {
      bVar1 = param_1[in_EAX];
      ppuVar2 = (undefined **)**(int **)(*param_4 + 4);
      if (ppuVar2 == std::ctype<char>::vftable) {
        iVar4 = __Tolower((uint)*param_1,(_Ctypevec *)(*(int **)(*param_4 + 4) + 2));
        cVar3 = (char)iVar4;
      }
      else {
        cVar3 = (*(code *)ppuVar2[4])(*param_1);
      }
      ppuVar2 = (undefined **)**(int **)(*param_4 + 4);
      if (ppuVar2 == std::ctype<char>::vftable) {
        uVar5 = __Tolower(CONCAT11(cVar3,bVar1) & 0xff,(_Ctypevec *)(*(int **)(*param_4 + 4) + 2));
      }
      else {
        uVar5 = (*(code *)ppuVar2[4])(bVar1);
      }
      if (cVar3 != (char)uVar5) {
        return uVar5 & 0xffffff00;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


