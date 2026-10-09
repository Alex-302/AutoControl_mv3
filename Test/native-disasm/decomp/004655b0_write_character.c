// write_character @ 004655b0 size=66 callers=3

/* Library Function - Single Match
    public: bool __thiscall
   __crt_stdio_output::string_output_adapter<char>::write_character(char,int * const)const 
   
   Library: Visual Studio 2015 Release */

bool __thiscall
__crt_stdio_output::string_output_adapter<char>::write_character
          (string_output_adapter<char> *this,char param_1,int *param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  iVar1 = *(int *)this;
  if (*(int *)(iVar1 + 8) == *(int *)(iVar1 + 4)) {
    if (*(char *)(iVar1 + 0xc) == '\0') {
      *param_2 = -1;
    }
    else {
      *param_2 = *param_2 + 1;
    }
    uVar2 = *(undefined1 *)(*(int *)this + 0xc);
  }
  else {
    *param_2 = *param_2 + 1;
    *(int *)(*(int *)this + 8) = *(int *)(*(int *)this + 8) + 1;
    *(char *)**(undefined4 **)this = param_1;
    **(int **)this = **(int **)this + 1;
    uVar2 = 1;
  }
  return (bool)uVar2;
}


