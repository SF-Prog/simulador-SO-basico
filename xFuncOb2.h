#ifndef XFUNCOB2_H
#define XFUNCOB2_H

#include "aStruct.h"

TipoRet MKDIR (Sistema &s, char nombreDirectorio[]/*, string &mensaje*/);

TipoRet CD (Sistema &s, char nombreDirS[]);

TipoRet RMDIR (Sistema &s, char nombreDirectorio[]);

TipoRet PWD(Sistema &s, char nombreDirectorio[]);

#endif
