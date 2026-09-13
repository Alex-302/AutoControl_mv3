// set_buffer @ 00465863 size=51 callers=1

/* Library Function - Single Match
    int __cdecl set_buffer(class __crt_stdio_stream,char * const,unsigned int,int)
   
   Library: Visual Studio 2015 Release */

int __cdecl set_buffer(undefined4 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  LOCK();
  param_1[3] = param_1[3] | param_4;
  UNLOCK();
  param_1[6] = param_3;
  *param_1 = param_2;
  param_1[1] = param_2;
  param_1[2] = 0;
  return 0;
}


