// find_in_environment_nolock<char> @ 00471019 size=84 callers=1

/* Library Function - Single Match
    int __cdecl find_in_environment_nolock<char>(char const * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl find_in_environment_nolock<char>(char *param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = DAT_0049f7c0;
  iVar2 = *DAT_0049f7c0;
  piVar3 = DAT_0049f7c0;
  while( true ) {
    if (iVar2 == 0) {
      return -((int)piVar3 - (int)piVar1 >> 2);
    }
    iVar2 = __strnicoll(param_1,(char *)*piVar3,param_2);
    if ((iVar2 == 0) &&
       ((*(char *)(param_2 + *piVar3) == '=' || (*(char *)(param_2 + *piVar3) == '\0')))) break;
    piVar3 = piVar3 + 1;
    iVar2 = *piVar3;
  }
  return (int)piVar3 - (int)piVar1 >> 2;
}


