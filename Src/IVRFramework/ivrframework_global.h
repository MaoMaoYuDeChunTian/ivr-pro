#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IVRFRAMEWORK_LIB)
#  define IVRFRAMEWORK_EXPORT Q_DECL_EXPORT
# else
#  define IVRFRAMEWORK_EXPORT Q_DECL_IMPORT
# endif
#else
# define IVRFRAMEWORK_EXPORT
#endif
