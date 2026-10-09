// _setvbuf @ 00465896 size=118 callers=2

/* Library Function - Single Match
    _setvbuf
   
   Library: Visual Studio 2015 Release */

int __cdecl _setvbuf(FILE *_File,char *_Buf,int _Mode,size_t _Size)

{
  int *piVar1;
  int iVar2;
  size_t *local_18;
  FILE **local_14;
  int *local_10;
  char **local_c;
  FILE *local_8;
  
  local_8 = _File;
  if (_File == (FILE *)0x0) {
LAB_004658a8:
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    iVar2 = -1;
  }
  else {
    if (_Mode == 4) {
LAB_004658ce:
      if ((_Mode == 0) || (_Mode == 0x40)) goto LAB_004658d7;
    }
    else {
      if (_Mode != 0) {
        if (_Mode != 0x40) goto LAB_004658a8;
        goto LAB_004658ce;
      }
LAB_004658d7:
      if (0x7ffffffd < _Size - 2) goto LAB_004658a8;
    }
    local_18 = &_Size;
    local_14 = &local_8;
    local_10 = &_Mode;
    local_c = &_Buf;
    iVar2 = __acrt_lock_stream_and_call<<lambda_b721fa326cdb32351d23dfa67958c160>_>
                      (_File,(<lambda_b721fa326cdb32351d23dfa67958c160> *)&local_18);
  }
  return iVar2;
}


