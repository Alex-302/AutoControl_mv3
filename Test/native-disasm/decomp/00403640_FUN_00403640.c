// FUN_00403640 @ 00403640 size=276 callers=1

int __fastcall FUN_00403640(char *param_1,int param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  
  uVar6 = 0;
  pcVar4 = param_1;
  if ((2 < param_3) && (param_3 != 2)) {
    do {
      bVar1 = *(byte *)(param_2 + uVar6);
      bVar2 = *(byte *)(param_2 + 1 + uVar6);
      bVar3 = *(byte *)(param_2 + 2 + uVar6);
      uVar6 = uVar6 + 3;
      *pcVar4 = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz0000111122223333444455556666777788889999++++////"
                [bVar1];
      pcVar4[1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                  [(uint)(bVar2 >> 4) | (bVar1 & 3) << 4];
      pcVar4[2] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                  [(bVar2 & 0xf) << 2 | (uint)(bVar3 >> 6)];
      pcVar4[3] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                  [bVar3];
      pcVar4 = pcVar4 + 4;
    } while (uVar6 < param_3 - 2);
  }
  if (param_3 != uVar6) {
    uVar5 = (uint)*(byte *)(uVar6 + param_2);
    if (param_3 - uVar6 != 1) {
      bVar1 = *(byte *)(uVar6 + 1 + param_2);
      *pcVar4 = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz0000111122223333444455556666777788889999++++////"
                [uVar5];
      pcVar4[1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                  [(uint)(bVar1 >> 4) | (uVar5 & 3) << 4];
      pcVar4[2] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                  [(bVar1 & 0xf) * 4];
      pcVar4[3] = '=';
      pcVar4[4] = '\0';
      return (int)(pcVar4 + 4) - (int)param_1;
    }
    *pcVar4 = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz0000111122223333444455556666777788889999++++////"
              [uVar5];
    pcVar4[1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                [(uVar5 & 3) * 0x10];
    pcVar4[2] = '=';
    pcVar4[3] = '=';
    pcVar4 = pcVar4 + 4;
  }
  *pcVar4 = '\0';
  return (int)pcVar4 - (int)param_1;
}


