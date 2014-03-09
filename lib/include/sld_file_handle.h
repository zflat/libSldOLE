#ifndef SLD_FILE_HANDLE_H
#define SLD_FILE_HANDLE_H

#include "libsldole_global.h"
#include <string>

class LIBSLDOLESHARED_EXPORT SldFileHandle
{

public:
    SldFileHandle();
    open(std::string const& fpath);
    close();
};

#endif // SLD_FILE_HANDLE_H
