// operator() @ 00467d0e size=92 callers=1

/* Library Function - Single Match
    public: void __thiscall <lambda_2af78c5f5901b1372d98f9ab3177dfa6>::operator()(void)const 
   
   Library: Visual Studio 2015 Release */

void __thiscall
<lambda_2af78c5f5901b1372d98f9ab3177dfa6>::operator()
          (<lambda_2af78c5f5901b1372d98f9ab3177dfa6> *this)

{
  LPVOID pvVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  pvVar1 = __calloc_base(1,0xb8);
  **(undefined4 **)this = pvVar1;
  FID_conflict__free((void *)0x0);
  if (pvVar1 != (LPVOID)0x0) {
    local_18 = *(undefined4 *)this;
    local_14 = *(undefined4 *)(this + 4);
    local_10 = *(undefined4 *)(this + 8);
    local_c = *(undefined4 *)(this + 0xc);
    local_8 = *(undefined4 *)(this + 0x10);
    __acrt_lock_and_call<<lambda_e378711a6f6581bf7f0efd7cdf97f5d9>_>
              (4,(<lambda_e378711a6f6581bf7f0efd7cdf97f5d9> *)&local_18);
  }
  return;
}


