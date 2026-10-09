// state_case_size @ 00464cdc size=361 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::state_case_size(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::state_case_size(void)
   
   Library: Visual Studio 2015 Release */

bool __fastcall
state_case_size(output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                *param_1)

{
  output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
  oVar1;
  char cVar2;
  char *pcVar3;
  bool bVar4;
  int *piVar5;
  
  oVar1 = param_1[0x31];
  if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                )0x46) {
    if ((*(uint *)param_1 & 8) == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 7;
      bVar4 = __crt_stdio_output::
              output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
              ::state_case_type(param_1);
      return bVar4;
    }
  }
  else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                     )0x4e) {
    if ((*(uint *)param_1 & 8) == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 8;
LAB_00464d14:
      piVar5 = __errno();
      *piVar5 = 0x16;
      FUN_00465fa2();
      return false;
    }
  }
  else {
    if (*(int *)(param_1 + 0x2c) != 0) goto LAB_00464d14;
    if ((char)oVar1 < 'k') {
      if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x6a) {
        *(undefined4 *)(param_1 + 0x2c) = 5;
      }
      else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                         )0x49) {
        pcVar3 = *(char **)(param_1 + 0x10);
        cVar2 = *pcVar3;
        if ((cVar2 == '3') && (pcVar3[1] == '2')) {
          *(undefined4 *)(param_1 + 0x2c) = 10;
          *(char **)(param_1 + 0x10) = pcVar3 + 2;
        }
        else if ((cVar2 == '6') && (pcVar3[1] == '4')) {
          *(undefined4 *)(param_1 + 0x2c) = 0xb;
          *(char **)(param_1 + 0x10) = pcVar3 + 2;
        }
        else if ((((cVar2 == 'd') || (cVar2 == 'i')) || (cVar2 == 'o')) ||
                (((cVar2 == 'u' || (cVar2 == 'x')) || (cVar2 == 'X')))) {
          *(undefined4 *)(param_1 + 0x2c) = 9;
        }
      }
      else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                         )0x4c) {
        *(undefined4 *)(param_1 + 0x2c) = 8;
      }
      else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                         )0x54) {
        *(undefined4 *)(param_1 + 0x2c) = 0xd;
      }
      else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                         )0x68) {
        if (**(char **)(param_1 + 0x10) == 'h') {
          *(undefined4 *)(param_1 + 0x2c) = 1;
          *(char **)(param_1 + 0x10) = *(char **)(param_1 + 0x10) + 1;
        }
        else {
          *(undefined4 *)(param_1 + 0x2c) = 2;
        }
      }
    }
    else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                       )0x6c) {
      if (**(char **)(param_1 + 0x10) == 'l') {
        *(undefined4 *)(param_1 + 0x2c) = 4;
        *(char **)(param_1 + 0x10) = *(char **)(param_1 + 0x10) + 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x2c) = 3;
      }
    }
    else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                       )0x74) {
      *(undefined4 *)(param_1 + 0x2c) = 7;
    }
    else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                       )0x77) {
      *(undefined4 *)(param_1 + 0x2c) = 0xc;
    }
    else if (oVar1 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                       )0x7a) {
      *(undefined4 *)(param_1 + 0x2c) = 6;
    }
  }
  return true;
}


