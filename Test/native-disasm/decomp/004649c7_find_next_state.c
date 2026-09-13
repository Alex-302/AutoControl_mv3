// find_next_state @ 004649c7 size=50 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: enum __crt_stdio_output::state __thiscall
   __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::find_next_state(char,enum __crt_stdio_output::state)const 
    private: enum __crt_stdio_output::state __thiscall
   __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::find_next_state(char,enum __crt_stdio_output::state)const 
   
   Library: Visual Studio 2015 Release */

byte find_next_state(char param_1,int param_2)

{
  uint uVar1;
  
  if ((byte)(param_1 - 0x20U) < 0x5b) {
    uVar1 = (byte)(&DAT_004852f8)[param_1] & 0xf;
  }
  else {
    uVar1 = 0;
  }
  return (byte)(&DAT_00485318)[uVar1 * 8 + param_2] >> 4;
}


