// shift_bytes @ 0046c539 size=52 callers=4

/* Library Function - Single Match
    void __cdecl shift_bytes(char * const,unsigned int,char * const,int)
   
   Library: Visual Studio 2015 Release */

void __cdecl shift_bytes(char *param_1,uint param_2,char *param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  
  if (param_4 != 0) {
    pcVar2 = param_3;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_0045b0e0((uint *)(param_3 + param_4),(uint *)param_3,
                 (uint)(pcVar2 + (1 - (int)(param_3 + 1))));
  }
  return;
}


