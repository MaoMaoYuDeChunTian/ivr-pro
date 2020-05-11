#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IVRTESTPLUGIN_LIB)
#  define IVRTESTPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define IVRTESTPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define IVRTESTPLUGIN_EXPORT
#endif
