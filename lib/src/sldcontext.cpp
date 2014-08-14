#include "sldcontext.h"

SldContext::SldContext()
{
    ptr_app_context = new SldAppContext();
}

SldContext::~SldContext()
{
    delete ptr_app_context;
}

ISldWorksPtr SldContext::get_swApp(){
    return ptr_app_context->getApp();
}

SldAppContext * SldContext::app(){
    return ptr_app_context;
}
