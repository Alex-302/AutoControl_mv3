// process @ 00464ab1 size=249 callers=1

/* Library Function - Single Match
    public: int __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::process(void)
   
   Library: Visual Studio 2015 Release */

int __thiscall
__crt_stdio_output::
output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
::process(output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
          *this)

{
  output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
  oVar1;
  bool bVar2;
  byte bVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  undefined3 extraout_var;
  undefined4 uVar7;
  
  bVar2 = __crt_strtox::c_string_character_source<char>::validate
                    ((c_string_character_source<char> *)(this + 0x448));
  if (!bVar2) {
    return -1;
  }
  if (*(int *)(this + 0x10) == 0) {
LAB_00464ad6:
    piVar5 = __errno();
    *piVar5 = 0x16;
    FUN_00465fa2();
switchD_00464b21_default:
    iVar6 = -1;
  }
  else {
LAB_00464b91:
    *(int *)(this + 0x450) = *(int *)(this + 0x450) + 1;
    if (*(int *)(this + 0x450) != 2) {
      *(undefined4 *)(this + 0x38) = 0;
      *(undefined4 *)(this + 0x1c) = 0;
LAB_00464b7e:
      oVar1 = **(output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                 **)(this + 0x10);
      this[0x31] = oVar1;
      if (oVar1 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x0) {
        *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;
        if (*(int *)(this + 0x18) < 0) goto LAB_00464b91;
        bVar3 = find_next_state((char)this[0x31],*(int *)(this + 0x1c));
        iVar6 = CONCAT31(extraout_var,bVar3);
        *(int *)(this + 0x1c) = iVar6;
        if (iVar6 == 8) goto LAB_00464ad6;
        switch(iVar6) {
        case 0:
          uVar7 = state_case_normal((int)this);
          cVar4 = (char)uVar7;
          break;
        case 1:
          *(undefined4 *)(this + 0x28) = 0xffffffff;
          *(undefined4 *)(this + 0x24) = 0;
          this[0x30] = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                        )0x0;
          *(undefined4 *)(this + 0x20) = 0;
          *(undefined4 *)(this + 0x2c) = 0;
          this[0x3c] = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                        )0x0;
          goto LAB_00464b7e;
        case 2:
          uVar7 = state_case_flag((int)this);
          cVar4 = (char)uVar7;
          break;
        case 3:
          uVar7 = state_case_width(this);
          cVar4 = (char)uVar7;
          break;
        case 4:
          goto switchD_00464b21_caseD_4;
        case 5:
          uVar7 = state_case_precision(this);
          cVar4 = (char)uVar7;
          break;
        case 6:
          cVar4 = state_case_size(this);
          break;
        case 7:
          cVar4 = state_case_type(this);
          break;
        default:
          goto switchD_00464b21_default;
        }
        if (cVar4 == '\0') goto switchD_00464b21_default;
        goto LAB_00464b7e;
      }
      *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;
      goto LAB_00464b91;
    }
    iVar6 = *(int *)(this + 0x18);
  }
  return iVar6;
switchD_00464b21_caseD_4:
  *(undefined4 *)(this + 0x28) = 0;
  goto LAB_00464b7e;
}


