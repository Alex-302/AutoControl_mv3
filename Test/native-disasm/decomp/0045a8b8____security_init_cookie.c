// ___security_init_cookie @ 0045a8b8 size=156 callers=1

/* Library Function - Single Match
    ___security_init_cookie
   
   Library: Visual Studio 2015 Release */

void __cdecl ___security_init_cookie(void)

{
  DWORD DVar1;
  LARGE_INTEGER local_18;
  _FILETIME local_10;
  uint local_8;
  
  local_10.dwLowDateTime = 0;
  local_10.dwHighDateTime = 0;
  if ((DAT_0049d070 == 0xbb40e64e) || ((DAT_0049d070 & 0xffff0000) == 0)) {
    GetSystemTimeAsFileTime(&local_10);
    local_8 = local_10.dwHighDateTime ^ local_10.dwLowDateTime;
    DVar1 = GetCurrentThreadId();
    local_8 = local_8 ^ DVar1;
    DVar1 = GetCurrentProcessId();
    local_8 = local_8 ^ DVar1;
    QueryPerformanceCounter(&local_18);
    DAT_0049d070 = local_18.s.HighPart ^ local_18.s.LowPart ^ local_8 ^ (uint)&local_8;
    if (DAT_0049d070 == 0xbb40e64e) {
      DAT_0049d070 = 0xbb40e64f;
    }
    else if ((DAT_0049d070 & 0xffff0000) == 0) {
      DAT_0049d070 = DAT_0049d070 | (DAT_0049d070 | 0x4711) << 0x10;
    }
  }
  DAT_0049d06c = ~DAT_0049d070;
  return;
}


