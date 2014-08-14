/*
 * Wrapper Class to contain all supported context adapeters.
 * - Solidworks Application
 * - PDM vault
 * - Document manager
 */

#ifndef SLDCONTEXT_H
#define SLDCONTEXT_H

#include "libsldole_global.h"
#include "sld_app_context.h"

class SldContext
{
public:
    SldContext();
    ~SldContext();
    ISldWorksPtr get_swApp();

    SldAppContext * app();

private:
    SldAppContext * ptr_app_context;
};

#endif // SLDCONTEXT_H
