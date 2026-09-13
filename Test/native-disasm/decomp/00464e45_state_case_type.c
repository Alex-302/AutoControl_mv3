// state_case_type @ 00464e45 size=559 callers=2

/* Library Function - Single Match
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::state_case_type(void)
   
   Library: Visual Studio 2015 Release */

bool __thiscall
__crt_stdio_output::
output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
::state_case_type(output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  *this)

{
  output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
  *poVar1;
  output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
  oVar2;
  bool bVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 local_8;
  
  iVar6 = 1;
  oVar2 = this[0x31];
  local_8 = this;
  if ((char)oVar2 < 'e') {
    if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x64) {
LAB_00464ef6:
      *(uint *)(this + 0x20) = *(uint *)(this + 0x20) | 0x10;
      goto LAB_00464efa;
    }
    if ('X' < (char)oVar2) {
      if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x5a) {
        uVar5 = type_case_Z((__uint64 *)this);
        cVar4 = (char)uVar5;
        goto LAB_00464e92;
      }
      if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x61) {
        if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                      )0x63) {
          return false;
        }
LAB_00464eb6:
        uVar5 = type_case_c_tchar((__uint64 *)this);
        cVar4 = (char)uVar5;
        goto LAB_00464e92;
      }
LAB_00464f06:
      uVar5 = type_case_a((uint *)this);
      cVar4 = (char)uVar5;
      goto LAB_00464e92;
    }
    if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x58) {
      if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x41) {
        if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                      )0x43) goto LAB_00464eb6;
        if ((char)oVar2 < 'E') {
          return false;
        }
        if ('G' < (char)oVar2) {
          if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                        )0x53) {
            return false;
          }
          goto LAB_00464e8b;
        }
      }
      goto LAB_00464f06;
    }
    cVar4 = '\x01';
LAB_00464ea2:
    uVar8 = 0x10;
  }
  else {
    if ((char)oVar2 < 'q') {
      if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x70) {
        cVar4 = type_case_p(this);
        goto LAB_00464e92;
      }
      if ((char)oVar2 < 'h') goto LAB_00464f06;
      if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x69) {
        if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                      )0x6e) {
          uVar8 = type_case_n((int)this);
          cVar4 = (char)uVar8;
        }
        else {
          if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                        )0x6f) {
            return false;
          }
          cVar4 = type_case_o(this);
        }
        goto LAB_00464e92;
      }
      goto LAB_00464ef6;
    }
    if (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x73) {
LAB_00464e8b:
      uVar5 = type_case_s((__uint64 *)this);
      cVar4 = (char)uVar5;
      goto LAB_00464e92;
    }
    if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x75) {
      if (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                    )0x78) {
        return false;
      }
      cVar4 = '\0';
      goto LAB_00464ea2;
    }
LAB_00464efa:
    cVar4 = '\0';
    uVar8 = 10;
  }
  uVar8 = type_case_integer(this,uVar8,cVar4);
  cVar4 = (char)uVar8;
LAB_00464e92:
  if (cVar4 == '\0') {
    return false;
  }
  if (this[0x30] !=
      (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
       )0x0) {
    return true;
  }
  uVar8 = *(uint *)(this + 0x20);
  local_8 = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
             *)((uint)local_8 & 0xff000000);
  iVar7 = 0;
  if ((uVar8 >> 4 & 1) != 0) {
    iVar7 = iVar6;
    if ((uVar8 >> 6 & 1) == 0) {
      if ((uVar8 & 1) == 0) {
        iVar7 = 0;
        if ((uVar8 >> 1 & 1) != 0) {
          local_8 = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                     *)CONCAT31(local_8._1_3_,0x20);
          iVar7 = iVar6;
        }
      }
      else {
        local_8 = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                   *)CONCAT31(local_8._1_3_,0x2b);
      }
    }
    else {
      local_8 = (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                 *)CONCAT31(local_8._1_3_,0x2d);
    }
  }
  oVar2 = this[0x31];
  if (((oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x78) &&
      (oVar2 != (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                 )0x58)) || ((uVar8 >> 5 & 1) == 0)) {
    iVar6 = 0;
  }
  if ((oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                 )0x61) ||
     (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                )0x41)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (((char)iVar6 != '\0') || (bVar3)) {
    *(undefined1 *)((int)&local_8 + iVar7) = 0x30;
    if ((oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                   )0x58) ||
       (oVar2 == (output_processor<char,__crt_stdio_output::string_output_adapter<char>,__crt_stdio_output::standard_base<char,__crt_stdio_output::string_output_adapter<char>_>_>
                  )0x41)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    *(byte *)((int)&local_8 + iVar7 + 1) = (!bVar3 - 1U & 0xe0) + 0x78;
    iVar7 = iVar7 + 2;
  }
  iVar6 = (*(int *)(this + 0x24) - *(int *)(this + 0x38)) - iVar7;
  if ((uVar8 & 0xc) == 0) {
    write_multiple_characters<__crt_stdio_output::string_output_adapter<char>,char>
              ((string_output_adapter<char> *)(this + 0x448),' ',iVar6,(int *)(this + 0x18));
  }
  string_output_adapter<char>::write_string
            ((string_output_adapter<char> *)(this + 0x448),(char *)&local_8,iVar7,
             (int *)(this + 0x18),*(int **)(this + 0xc));
  poVar1 = this + 0x18;
  if (((*(uint *)(this + 0x20) >> 3 & 1) != 0) && ((*(uint *)(this + 0x20) >> 2 & 1) == 0)) {
    write_multiple_characters<__crt_stdio_output::string_output_adapter<char>,char>
              ((string_output_adapter<char> *)(this + 0x448),'0',iVar6,(int *)poVar1);
  }
  write_stored_string_tchar((int)this);
  if ((-1 < *(int *)poVar1) && ((*(uint *)(this + 0x20) >> 2 & 1) != 0)) {
    write_multiple_characters<__crt_stdio_output::string_output_adapter<char>,char>
              ((string_output_adapter<char> *)(this + 0x448),' ',iVar6,(int *)poVar1);
  }
  return true;
}


