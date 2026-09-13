// crop_zeroes @ 00464970 size=87 callers=1

/* Library Function - Single Match
    void __cdecl __crt_stdio_output::crop_zeroes(char *,struct __crt_locale_pointers * const)
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

void __cdecl __crt_stdio_output::crop_zeroes(char *param_1,__crt_locale_pointers *param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  for (; (*param_1 != '\0' && (*param_1 != *(char *)**(undefined4 **)(*(int *)param_2 + 0x88)));
      param_1 = param_1 + 1) {
  }
  if (*param_1 != '\0') {
    do {
      param_1 = param_1 + 1;
      cVar1 = *param_1;
      pcVar2 = param_1;
      if ((cVar1 == '\0') || (cVar1 == 'e')) break;
    } while (cVar1 != 'E');
    do {
      pcVar3 = pcVar2;
      pcVar2 = pcVar3 + -1;
    } while (*pcVar2 == '0');
    if (*pcVar2 == *(char *)**(undefined4 **)(*(int *)param_2 + 0x88)) {
      pcVar2 = pcVar3 + -2;
    }
    do {
      cVar1 = *param_1;
      pcVar2 = pcVar2 + 1;
      param_1 = param_1 + 1;
      *pcVar2 = cVar1;
    } while (cVar1 != '\0');
  }
  return;
}


