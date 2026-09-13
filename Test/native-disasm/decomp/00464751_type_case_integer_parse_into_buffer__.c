// type_case_integer_parse_into_buffer<> @ 00464751 size=117 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: void __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> >
   >::type_case_integer_parse_into_buffer<unsigned int>(unsigned int,unsigned int,bool)
    private: void __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_integer_parse_into_buffer<unsigned int>(unsigned int,unsigned int,bool)
    private: void __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_integer_parse_into_buffer<unsigned
   int>(unsigned int,unsigned int,bool)
    private: void __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_integer_parse_into_buffer<unsigned int>(unsigned int,unsigned int,bool)
     12 names - too many to list
   
   Library: Visual Studio 2015 Release */

void __thiscall
type_case_integer_parse_into_buffer<>(void *this,uint param_1,uint param_2,char param_3)

{
  uint uVar1;
  char cVar2;
  formatting_buffer *pfVar3;
  
  pfVar3 = *(formatting_buffer **)((int)this + 0x444);
  if (*(formatting_buffer **)((int)this + 0x444) == (formatting_buffer *)0x0) {
    pfVar3 = (formatting_buffer *)((int)this + 0x40);
  }
  uVar1 = __crt_stdio_output::formatting_buffer::count<char>
                    ((formatting_buffer *)((int)this + 0x40));
  *(formatting_buffer **)((int)this + 0x34) = pfVar3 + (uVar1 - 1);
  while ((0 < *(int *)((int)this + 0x28) || (param_1 != 0))) {
    cVar2 = (char)(param_1 % param_2) + '0';
    *(int *)((int)this + 0x28) = *(int *)((int)this + 0x28) + -1;
    if ('9' < cVar2) {
      cVar2 = cVar2 + ((param_3 == '\0') - 1U & 0xe0) + 0x27;
    }
    **(char **)((int)this + 0x34) = cVar2;
    *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) + -1;
    param_1 = param_1 / param_2;
  }
  *(int *)((int)this + 0x38) = (int)(pfVar3 + (uVar1 - 1)) - *(int *)((int)this + 0x34);
  *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) + 1;
  return;
}


