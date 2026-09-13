// ___scrt_uninitialize_crt @ 0045a627 size=40 callers=1

/* Library Function - Single Match
    ___scrt_uninitialize_crt
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___scrt_uninitialize_crt(char param_1,char param_2)

{
  undefined4 in_EAX;
  
  if ((DAT_0049f158 == '\0') || (param_2 == '\0')) {
    ___acrt_uninitialize();
    in_EAX = ___vcrt_uninitialize(param_1);
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


