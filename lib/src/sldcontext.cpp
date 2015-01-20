#include "sldcontext.h"

SldContext::SldContext()
{
    ptr_app_context = new SldAppContext();
    ptr_vault_context = new SldPdmwContext();
}

SldContext::~SldContext()
{
    delete ptr_app_context;
    delete ptr_vault_context;
}

ISldWorksPtr SldContext::get_swApp(){
    return ptr_app_context->getApp();
}

SldAppContext * SldContext::app(){
    return ptr_app_context;
}

IPDMWConnectionPtr SldContext::get_swVault(){
    return ptr_vault_context->get_swVault();
}

SldPdmwContext * SldContext::vault(){
    return ptr_vault_context;
}
