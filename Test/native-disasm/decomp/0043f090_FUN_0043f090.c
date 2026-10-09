// FUN_0043f090 @ 0043f090 size=48 callers=1

uint FUN_0043f090(int param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0x811c9dc5;
  uVar2 = 0;
  if (param_2 != param_1) {
    do {
      pbVar1 = (byte *)(uVar2 + param_1);
      uVar2 = uVar2 + 1;
      uVar3 = (*pbVar1 ^ uVar3) * 0x1000193;
    } while (uVar2 < (uint)(param_2 - param_1));
  }
  return uVar3;
}


