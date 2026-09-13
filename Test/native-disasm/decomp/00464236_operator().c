// operator() @ 00464236 size=70 callers=1

/* Library Function - Single Match
    public: unsigned int __thiscall <lambda_b51c0495177f500e782686251704ae76>::operator()(void)const
   
   
   Library: Visual Studio 2015 Release */

uint __thiscall
<lambda_b51c0495177f500e782686251704ae76>::operator()
          (<lambda_b51c0495177f500e782686251704ae76> *this)

{
  FILE *pFVar1;
  uint uVar2;
  size_t sVar3;
  
  pFVar1 = (FILE *)**(undefined4 **)this;
  uVar2 = ___acrt_stdio_begin_temporary_buffering_nolock(pFVar1);
  sVar3 = __fwrite_nolock((void *)**(undefined4 **)(this + 4),**(size_t **)(this + 8),
                          **(size_t **)(this + 0xc),(FILE *)**(undefined4 **)this);
  ___acrt_stdio_end_temporary_buffering_nolock((char)uVar2,pFVar1);
  return sVar3;
}


