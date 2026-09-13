// ~basic_iostream<char,std::char_traits<char>_> @ 0043b9b0 size=85 callers=1

/* Library Function - Single Match
    public: virtual __thiscall std::basic_iostream<char,struct std::char_traits<char>
   >::~basic_iostream<char,struct std::char_traits<char> >(void)
   
   Library: Visual Studio 2019 Release */

void __thiscall
std::basic_iostream<char,std::char_traits<char>_>::~basic_iostream<char,std::char_traits<char>_>
          (basic_iostream<char,std::char_traits<char>_> *this)

{
  *(undefined ***)(this + *(int *)(*(int *)(this + -0x20) + 4) + -0x20) = &PTR_LAB_0048e968;
  *(int *)(this + *(int *)(*(int *)(this + -0x20) + 4) + -0x24) =
       *(int *)(*(int *)(this + -0x20) + 4) + -0x20;
  *(undefined ***)(this + *(int *)(*(int *)(this + -0x10) + 4) + -0x10) = &PTR_LAB_0048f09c;
  *(int *)(this + *(int *)(*(int *)(this + -0x10) + 4) + -0x14) =
       *(int *)(*(int *)(this + -0x10) + 4) + -8;
  *(undefined ***)(this + *(int *)(*(int *)(this + -0x20) + 4) + -0x20) = &PTR_LAB_0048ec6c;
  *(int *)(this + *(int *)(*(int *)(this + -0x20) + 4) + -0x24) =
       *(int *)(*(int *)(this + -0x20) + 4) + -0x18;
  return;
}


