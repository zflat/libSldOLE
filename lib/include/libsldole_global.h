#ifndef LIBSLDOLE_GLOBAL_H
#define LIBSLDOLE_GLOBAL_H

#include <QtCore/qglobal.h>

#import "C:\Program Files\SolidWorks Corp\SolidWorks\sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
#import "C:\Program Files\SolidWorks Corp\SolidWorks\swconst.tlb"  raw_interfaces_only, raw_native_types, no_namespace, named_guids

#import "C:\Program Files\Common Files\SolidWorks Shared\pdmworks.dll" raw_interfaces_only, no_namespace, named_guids

#include <windows.h>
#include <comdef.h>
#include <objbase.h>

#include <tlhelp32.h>

#if defined(LIBSLDOLE_LIBRARY)
#  define LIBSLDOLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBSLDOLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBSLDOLE_GLOBAL_H
