// write_string @ 00465699 size=147 callers=3

/* Library Function - Single Match
    public: void __thiscall __crt_stdio_output::string_output_adapter<char>::write_string(char const
   * const,int,int * const,int * const)const 
   
   Library: Visual Studio 2015 Release */

void __thiscall
__crt_stdio_output::string_output_adapter<char>::write_string
          (string_output_adapter<char> *this,char *param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  iVar1 = *param_4;
  *param_4 = 0;
  puVar2 = *(undefined4 **)this;
  if (puVar2[2] == puVar2[1]) {
    if (*(char *)(puVar2 + 3) == '\0') {
      *param_3 = -1;
    }
    else {
      *param_3 = *param_3 + param_2;
    }
  }
  else {
    uVar3 = puVar2[1] - puVar2[2];
    if ((uint)param_2 <= uVar3) {
      uVar3 = param_2;
    }
    FUN_0045c870((uint *)*puVar2,(uint *)param_1,uVar3);
    **(int **)this = **(int **)this + uVar3;
    *(int *)(*(int *)this + 8) = *(int *)(*(int *)this + 8) + uVar3;
    if (*(char *)(*(int *)this + 0xc) == '\0') {
      if (uVar3 == param_2) {
        *param_3 = *param_3 + uVar3;
      }
      else {
        *param_3 = -1;
      }
    }
    else {
      *param_3 = *param_3 + param_2;
    }
  }
  if ((*param_4 == 0) && (iVar1 != 0)) {
    *param_4 = iVar1;
  }
  return;
}


