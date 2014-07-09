#ifndef SLD_FILE_HANDLE_H
#define SLD_FILE_HANDLE_H

#include "libsldole_global.h"
#include <string>

class LIBSLDOLESHARED_EXPORT SldFileHandle
{

public:
    SldFileHandle();
    //open(std::string const& fpath);
    //close();
    /**
     * @brief Determine the file type based on file extension
     * @param fpath
     * @return swDocumentTypes_e enumeration corresponding to file type
     */
    static long sld_doc_type(QString const& fpath);
};

#endif // SLD_FILE_HANDLE_H
