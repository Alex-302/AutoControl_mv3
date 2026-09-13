// type_case_c_tchar @ 004652b8 size=144 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_c_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_c_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_c_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_c_tchar(char)
     6 names - too many to list
   
   Library: Visual Studio 2015 Release */

undefined4 __fastcall type_case_c_tchar(__uint64 *param_1)

{
  bool bVar1;
  uint _SizeInBytes;
  errno_t eVar2;
  formatting_buffer *pfVar3;
  formatting_buffer *this;
  wchar_t _WCh;
  
  bVar1 = __crt_stdio_output::is_wide_character_specifier<char>
                    (*param_1,*(char *)((int)param_1 + 0x31),
                     *(length_modifier *)((int)param_1 + 0x2c));
  this = (formatting_buffer *)(param_1 + 8);
  if (bVar1) {
    *(int *)((int)param_1 + 0x14) = *(int *)((int)param_1 + 0x14) + 4;
    _WCh = *(wchar_t *)(*(int *)((int)param_1 + 0x14) + -4);
    pfVar3 = *(formatting_buffer **)((int)param_1 + 0x444);
    if (*(formatting_buffer **)((int)param_1 + 0x444) == (formatting_buffer *)0x0) {
      pfVar3 = this;
    }
    _SizeInBytes = __crt_stdio_output::formatting_buffer::count<char>(this);
    eVar2 = _wctomb_s((int *)(param_1 + 7),(char *)pfVar3,_SizeInBytes,_WCh);
    if (eVar2 != 0) {
      *(undefined1 *)(param_1 + 6) = 1;
    }
  }
  else {
    pfVar3 = *(formatting_buffer **)((int)param_1 + 0x444);
    if (*(formatting_buffer **)((int)param_1 + 0x444) == (formatting_buffer *)0x0) {
      pfVar3 = this;
    }
    *(int *)((int)param_1 + 0x14) = *(int *)((int)param_1 + 0x14) + 4;
    *pfVar3 = *(formatting_buffer *)(*(int *)((int)param_1 + 0x14) + -4);
    *(undefined4 *)(param_1 + 7) = 1;
  }
  pfVar3 = *(formatting_buffer **)((int)param_1 + 0x444);
  if (pfVar3 != (formatting_buffer *)0x0) {
    this = pfVar3;
  }
  *(formatting_buffer **)((int)param_1 + 0x34) = this;
  return CONCAT31((int3)((uint)pfVar3 >> 8),1);
}


