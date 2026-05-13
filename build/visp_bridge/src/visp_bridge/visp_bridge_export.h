
#ifndef VISP_BRIDGE_EXPORT_H
#define VISP_BRIDGE_EXPORT_H

#ifdef VISP_BRIDGE_STATIC_DEFINE
#  define VISP_BRIDGE_EXPORT
#  define VISP_BRIDGE_NO_EXPORT
#else
#  ifndef VISP_BRIDGE_EXPORT
#    ifdef visp_bridge_EXPORTS
        /* We are building this library */
#      define VISP_BRIDGE_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VISP_BRIDGE_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VISP_BRIDGE_NO_EXPORT
#    define VISP_BRIDGE_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VISP_BRIDGE_DEPRECATED
#  define VISP_BRIDGE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VISP_BRIDGE_DEPRECATED_EXPORT
#  define VISP_BRIDGE_DEPRECATED_EXPORT VISP_BRIDGE_EXPORT VISP_BRIDGE_DEPRECATED
#endif

#ifndef VISP_BRIDGE_DEPRECATED_NO_EXPORT
#  define VISP_BRIDGE_DEPRECATED_NO_EXPORT VISP_BRIDGE_NO_EXPORT VISP_BRIDGE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VISP_BRIDGE_NO_DEPRECATED
#    define VISP_BRIDGE_NO_DEPRECATED
#  endif
#endif

#endif /* VISP_BRIDGE_EXPORT_H */
