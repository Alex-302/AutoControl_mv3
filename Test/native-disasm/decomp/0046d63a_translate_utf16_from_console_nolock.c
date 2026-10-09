// translate_utf16_from_console_nolock @ 0046d63a size=129 callers=1

/* Library Function - Single Match
    int __cdecl translate_utf16_from_console_nolock(int,wchar_t * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl translate_utf16_from_console_nolock(int param_1,wchar_t *param_2,uint param_3)

{
  wchar_t *pwVar1;
  byte *pbVar2;
  wchar_t wVar3;
  wchar_t *pwVar4;
  wchar_t *pwVar5;
  wchar_t *pwVar6;
  
  pwVar1 = param_2 + param_3;
  pwVar6 = param_2;
  if (param_2 < pwVar1) {
    pwVar5 = param_2 + 1;
    pwVar4 = param_2;
    do {
      wVar3 = *pwVar4;
      if (wVar3 == L'\x1a') {
        pbVar2 = (byte *)((&DAT_0049f8f8)[param_1 >> 6] + 0x28 + (param_1 & 0x3fU) * 0x30);
        *pbVar2 = *pbVar2 | 2;
        break;
      }
      if (((wVar3 == L'\r') && (pwVar5 < pwVar1)) && (*pwVar5 == L'\n')) {
        pwVar4 = pwVar4 + 2;
        *pwVar6 = L'\n';
        pwVar5 = pwVar5 + 2;
      }
      else {
        *pwVar6 = wVar3;
        pwVar4 = pwVar4 + 1;
        pwVar5 = pwVar5 + 1;
      }
      pwVar6 = pwVar6 + 1;
    } while (pwVar4 < pwVar1);
  }
  return (int)pwVar6 - (int)param_2 & 0xfffffffe;
}


