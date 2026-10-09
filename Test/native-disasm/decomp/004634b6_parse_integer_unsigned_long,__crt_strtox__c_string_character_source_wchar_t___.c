// parse_integer<unsigned_long,__crt_strtox::c_string_character_source<wchar_t>_> @ 004634b6 size=1765 callers=1

/* Library Function - Single Match
    unsigned long __cdecl __crt_strtox::parse_integer<unsigned long,class
   __crt_strtox::c_string_character_source<wchar_t> >(struct __crt_locale_pointers * const,class
   __crt_strtox::c_string_character_source<wchar_t>,int,bool)
   
   Library: Visual Studio 2015 Release */

ulong __cdecl
__crt_strtox::parse_integer<unsigned_long,__crt_strtox::c_string_character_source<wchar_t>_>
          (__crt_locale_pointers *param_1,wchar_t *param_2,undefined4 *param_3,uint param_4,
          char param_5)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  wchar_t wVar9;
  int local_20 [3];
  char local_14;
  wchar_t *local_10;
  uint local_c;
  undefined4 local_8;
  
  bVar1 = c_string_character_source<char>::validate((c_string_character_source<char> *)&param_2);
  if (bVar1) {
    if ((param_4 == 0) || ((1 < (int)param_4 && ((int)param_4 < 0x25)))) {
      _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)local_20,param_1);
      local_c = 0;
      local_10 = param_2;
      do {
        wVar9 = *param_2;
        param_2 = param_2 + 1;
        iVar3 = _iswctype(wVar9,8);
      } while (iVar3 != 0);
      uVar7 = (uint)(param_5 != '\0');
      if (wVar9 == L'-') {
        uVar7 = uVar7 | 2;
LAB_0046354f:
        wVar9 = *param_2;
        param_2 = param_2 + 1;
      }
      else if (wVar9 == L'+') goto LAB_0046354f;
      uVar6 = (uint)(ushort)wVar9;
      local_8 = 0x19;
      if ((param_4 != 0) && (param_4 != 0x10)) goto LAB_00463857;
      if ((ushort)wVar9 < 0x30) goto LAB_004637da;
      if ((ushort)wVar9 < 0x3a) {
        iVar3 = uVar6 - 0x30;
LAB_004637d5:
        if (iVar3 == -1) goto LAB_004637da;
      }
      else {
        if (0xff0f < (ushort)wVar9) {
          if ((ushort)wVar9 < 0xff1a) {
            iVar3 = uVar6 - 0xff10;
          }
          else {
            iVar3 = -1;
          }
          goto LAB_004637d5;
        }
        if (0x65f < (ushort)wVar9) {
          if ((ushort)wVar9 < 0x66a) {
            iVar3 = uVar6 - 0x660;
          }
          else {
            if ((ushort)wVar9 < 0x6f0) goto LAB_004637da;
            if ((ushort)wVar9 < 0x6fa) {
              iVar3 = uVar6 - 0x6f0;
            }
            else {
              if ((ushort)wVar9 < 0x966) goto LAB_004637da;
              if ((ushort)wVar9 < 0x970) {
                iVar3 = uVar6 - 0x966;
              }
              else {
                if ((ushort)wVar9 < 0x9e6) goto LAB_004637da;
                if ((ushort)wVar9 < 0x9f0) {
                  iVar3 = uVar6 - 0x9e6;
                }
                else {
                  if ((ushort)wVar9 < 0xa66) goto LAB_004637da;
                  if ((ushort)wVar9 < 0xa70) {
                    iVar3 = uVar6 - 0xa66;
                  }
                  else {
                    if ((ushort)wVar9 < 0xae6) goto LAB_004637da;
                    if ((ushort)wVar9 < 0xaf0) {
                      iVar3 = uVar6 - 0xae6;
                    }
                    else {
                      if ((ushort)wVar9 < 0xb66) goto LAB_004637da;
                      if ((ushort)wVar9 < 0xb70) {
                        iVar3 = uVar6 - 0xb66;
                      }
                      else {
                        if ((ushort)wVar9 < 0xc66) goto LAB_004637da;
                        if ((ushort)wVar9 < 0xc70) {
                          iVar3 = uVar6 - 0xc66;
                        }
                        else {
                          if ((ushort)wVar9 < 0xce6) goto LAB_004637da;
                          if ((ushort)wVar9 < 0xcf0) {
                            iVar3 = uVar6 - 0xce6;
                          }
                          else {
                            if ((ushort)wVar9 < 0xd66) goto LAB_004637da;
                            if ((ushort)wVar9 < 0xd70) {
                              iVar3 = uVar6 - 0xd66;
                            }
                            else {
                              if ((ushort)wVar9 < 0xe50) goto LAB_004637da;
                              if ((ushort)wVar9 < 0xe5a) {
                                iVar3 = uVar6 - 0xe50;
                              }
                              else {
                                if ((ushort)wVar9 < 0xed0) goto LAB_004637da;
                                if ((ushort)wVar9 < 0xeda) {
                                  iVar3 = uVar6 - 0xed0;
                                }
                                else {
                                  if ((ushort)wVar9 < 0xf20) goto LAB_004637da;
                                  if ((ushort)wVar9 < 0xf2a) {
                                    iVar3 = uVar6 - 0xf20;
                                  }
                                  else {
                                    if ((ushort)wVar9 < 0x1040) goto LAB_004637da;
                                    if ((ushort)wVar9 < 0x104a) {
                                      iVar3 = uVar6 - 0x1040;
                                    }
                                    else {
                                      if ((ushort)wVar9 < 0x17e0) goto LAB_004637da;
                                      if ((ushort)wVar9 < 0x17ea) {
                                        iVar3 = uVar6 - 0x17e0;
                                      }
                                      else {
                                        if (((ushort)wVar9 < 0x1810) || (0x1819 < (ushort)wVar9))
                                        goto LAB_004637da;
                                        iVar3 = uVar6 - 0x1810;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          goto LAB_004637d5;
        }
LAB_004637da:
        if ((((ushort)wVar9 < 0x41) || (0x5a < (ushort)wVar9)) && (0x19 < (ushort)(wVar9 + L'ﾟ')))
        {
          iVar3 = -1;
        }
        else {
          uVar4 = uVar6;
          if ((ushort)(wVar9 + L'ﾟ') < 0x1a) {
            uVar4 = uVar6 - 0x20;
          }
          iVar3 = uVar4 - 0x37;
        }
      }
      if (iVar3 == 0) {
        wVar9 = *param_2;
        if ((wVar9 == L'x') || (wVar9 == L'X')) {
          if (param_4 == 0) {
            param_4 = 0x10;
          }
          uVar6 = (uint)(ushort)param_2[1];
          param_2 = param_2 + 2;
        }
        else {
          if (param_4 == 0) {
            param_4 = 8;
          }
          param_2 = param_2 + 1;
          c_string_character_source<wchar_t>::unget
                    ((c_string_character_source<wchar_t> *)&param_2,wVar9);
        }
      }
      else if (param_4 == 0) {
        param_4 = 10;
      }
LAB_00463857:
      uVar4 = (uint)(0xffffffff / (ulonglong)param_4);
      do {
        wVar9 = (wchar_t)uVar6;
        if ((ushort)wVar9 < 0x30) goto LAB_00463ac2;
        if ((ushort)wVar9 < 0x3a) {
          uVar5 = uVar6 - 0x30;
LAB_00463abd:
          if (uVar5 == 0xffffffff) goto LAB_00463ac2;
        }
        else {
          if (0xff0f < (ushort)wVar9) {
            if ((ushort)wVar9 < 0xff1a) {
              uVar5 = uVar6 - 0xff10;
            }
            else {
              uVar5 = 0xffffffff;
            }
            goto LAB_00463abd;
          }
          if (0x65f < (ushort)wVar9) {
            if ((ushort)wVar9 < 0x66a) {
              uVar5 = uVar6 - 0x660;
            }
            else {
              if ((ushort)wVar9 < 0x6f0) goto LAB_00463ac2;
              if ((ushort)wVar9 < 0x6fa) {
                uVar5 = uVar6 - 0x6f0;
              }
              else {
                if ((ushort)wVar9 < 0x966) goto LAB_00463ac2;
                if ((ushort)wVar9 < 0x970) {
                  uVar5 = uVar6 - 0x966;
                }
                else {
                  if ((ushort)wVar9 < 0x9e6) goto LAB_00463ac2;
                  if ((ushort)wVar9 < 0x9f0) {
                    uVar5 = uVar6 - 0x9e6;
                  }
                  else {
                    if ((ushort)wVar9 < 0xa66) goto LAB_00463ac2;
                    if ((ushort)wVar9 < 0xa70) {
                      uVar5 = uVar6 - 0xa66;
                    }
                    else {
                      if ((ushort)wVar9 < 0xae6) goto LAB_00463ac2;
                      if ((ushort)wVar9 < 0xaf0) {
                        uVar5 = uVar6 - 0xae6;
                      }
                      else {
                        if ((ushort)wVar9 < 0xb66) goto LAB_00463ac2;
                        if ((ushort)wVar9 < 0xb70) {
                          uVar5 = uVar6 - 0xb66;
                        }
                        else {
                          if ((ushort)wVar9 < 0xc66) goto LAB_00463ac2;
                          if ((ushort)wVar9 < 0xc70) {
                            uVar5 = uVar6 - 0xc66;
                          }
                          else {
                            if ((ushort)wVar9 < 0xce6) goto LAB_00463ac2;
                            if ((ushort)wVar9 < 0xcf0) {
                              uVar5 = uVar6 - 0xce6;
                            }
                            else {
                              if ((ushort)wVar9 < 0xd66) goto LAB_00463ac2;
                              if ((ushort)wVar9 < 0xd70) {
                                uVar5 = uVar6 - 0xd66;
                              }
                              else {
                                if ((ushort)wVar9 < 0xe50) goto LAB_00463ac2;
                                if ((ushort)wVar9 < 0xe5a) {
                                  uVar5 = uVar6 - 0xe50;
                                }
                                else {
                                  if ((ushort)wVar9 < 0xed0) goto LAB_00463ac2;
                                  if ((ushort)wVar9 < 0xeda) {
                                    uVar5 = uVar6 - 0xed0;
                                  }
                                  else {
                                    if ((ushort)wVar9 < 0xf20) goto LAB_00463ac2;
                                    if ((ushort)wVar9 < 0xf2a) {
                                      uVar5 = uVar6 - 0xf20;
                                    }
                                    else {
                                      if ((ushort)wVar9 < 0x1040) goto LAB_00463ac2;
                                      if ((ushort)wVar9 < 0x104a) {
                                        uVar5 = uVar6 - 0x1040;
                                      }
                                      else {
                                        if ((ushort)wVar9 < 0x17e0) goto LAB_00463ac2;
                                        if ((ushort)wVar9 < 0x17ea) {
                                          uVar5 = uVar6 - 0x17e0;
                                        }
                                        else {
                                          if (((ushort)wVar9 < 0x1810) || (0x1819 < (ushort)wVar9))
                                          goto LAB_00463ac2;
                                          uVar5 = uVar6 - 0x1810;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            goto LAB_00463abd;
          }
LAB_00463ac2:
          if ((((ushort)wVar9 < 0x41) || (0x5a < (ushort)wVar9)) &&
             ((ushort)local_8 < (ushort)(wVar9 + L'ﾟ'))) {
            uVar5 = 0xffffffff;
          }
          else {
            if ((ushort)(wVar9 + L'ﾟ') <= (ushort)local_8) {
              uVar6 = uVar6 - 0x20;
            }
            uVar5 = uVar6 - 0x37;
          }
        }
        if ((uVar5 == 0xffffffff) || (param_4 <= uVar5)) goto LAB_00463b28;
        uVar8 = uVar7 | 8;
        if ((local_c < uVar4) ||
           ((local_c == uVar4 && (uVar5 <= (uint)(0xffffffff % (ulonglong)param_4))))) {
          local_c = local_c * param_4 + uVar5;
        }
        else {
          uVar8 = uVar7 | 0xc;
        }
        uVar6 = (uint)(ushort)*param_2;
        param_2 = param_2 + 1;
        uVar7 = uVar8;
      } while( true );
    }
    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_00465fa2();
  }
  uVar6 = 0;
LAB_004634f1:
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = param_2;
  }
  return uVar6;
LAB_00463b28:
  c_string_character_source<wchar_t>::unget((c_string_character_source<wchar_t> *)&param_2,wVar9);
  uVar6 = local_c;
  if ((uVar7 & 8) == 0) {
    uVar6 = 0;
    param_2 = local_10;
  }
  else {
    bVar1 = is_overflow_condition<unsigned_long>(uVar7,local_c);
    if (bVar1) {
      piVar2 = __errno();
      *piVar2 = 0x22;
      if ((uVar7 & 1) == 0) {
        uVar6 = 0xffffffff;
      }
      else if ((uVar7 & 2) == 0) {
        uVar6 = 0x7fffffff;
      }
      else {
        uVar6 = 0x80000000;
      }
    }
    else if ((uVar7 & 2) != 0) {
      uVar6 = -uVar6;
    }
  }
  if (local_14 != '\0') {
    *(uint *)(local_20[0] + 0x350) = *(uint *)(local_20[0] + 0x350) & 0xfffffffd;
  }
  goto LAB_004634f1;
}


