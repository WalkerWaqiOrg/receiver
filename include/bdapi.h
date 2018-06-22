//
// Interface for Biiton Dongle (Hardware Wallet Device).
//
#ifndef __BDAPI_H__
#define __BDAPI_H__

#if defined(_WIN32) || defined(WIN32)
#   define BD_OS_WIN32
#   include <windows.h>
#   ifdef BDAPI_EXPORTS
#       define BDAPI __declspec(dllexport)
#   else
#       define BDAPI __declspec(dllimport)
#       if defined _M_IX86
#           pragma comment(lib, "windows/x86/bdapi.lib")
#      elif defined _M_IA64
#       	error "IA64 does not supported."
#      elif defined _M_X64
#      	    pragma comment(lib, "windows/x64/bdapi.lib")
#       else
#           error "unknown platform."
#      endif
#   endif


#elif defined(__linux__)
#   define BD_OS_LINUX
#   define BD_OS_UNIX_LIKE


#elif defined(__APPLE__)
#   define BD_OS_MACOS
#   define BD_OS_UNIX_LIKE


#else
#	error unsupported platform.
#endif



#ifdef BD_OS_UNIX_LIKE
#   include <sys/types.h>
#   include <string.h>
#   include <cstdlib>
#   include <stdio.h>
#   include <stdarg.h>
#   include <unistd.h>
#   ifndef ULONG
#       define ULONG unsigned int
#       define DWORD unsigned int
#       define UINT unsigned int
#       define UINT8 unsigned char
#       define USHORT unsigned short
#       define BYTE unsigned char
#   endif
#   define BDAPI
#endif // BD_OS_UNIX_LIKE


#define BDRET_OK           0    // success
#define BDRET_INTERNAL    -1    // internal error
#define BDRET_BAD_PARAM   -2    // invalid parameter


typedef void* BDDEV;

// find all hard-wallet devices, return count of devices.
BDAPI int bd_find_device(void);

// connect to one of the devices.
BDAPI BDDEV bd_connect(int index);

// close a connected device.
BDAPI int bd_close(BDDEV* dev);

// get hardware serial number of the connected device.
BDAPI int bd_get_sn(BDDEV dev,  BYTE sn[16]);


#endif // __BDAPI_H__
