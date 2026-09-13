// write_multiple_characters<__crt_stdio_output::string_output_adapter<char>,char> @ 0046484e size=44 callers=3

/* Library Function - Single Match
    void __cdecl __crt_stdio_output::write_multiple_characters<class
   __crt_stdio_output::string_output_adapter<char>,char>(class
   __crt_stdio_output::string_output_adapter<char> const &,char,int,int * const)
   
   Library: Visual Studio 2015 Release */

void __cdecl
__crt_stdio_output::write_multiple_characters<__crt_stdio_output::string_output_adapter<char>,char>
          (string_output_adapter<char> *param_1,char param_2,int param_3,int *param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_3) {
    do {
      string_output_adapter<char>::write_character(param_1,param_2,param_4);
      if (*param_4 == -1) {
        return;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  return;
}


