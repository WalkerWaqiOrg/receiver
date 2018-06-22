#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOG4QT_LIB)
#  define LOG4QT_EXPORT Q_DECL_EXPORT
# else
#  define LOG4QT_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOG4QT_EXPORT
#endif
