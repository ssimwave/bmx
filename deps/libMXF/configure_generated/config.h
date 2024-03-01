/* library names */
#define LIBMXF_LIBRARY_NAME     "libMXF"
#define LIBMXF_LIBRARY_WNAME   L"libMXF"

/* Library versions */
#define LIBMXF_VERSION_MAJOR 1
#define LIBMXF_VERSION_MINOR 2

/* Define printf size_t format specifier */
#if defined(_WIN64)
#define PRIszt  "I64u"
#elif defined(_WIN32)
#define PRIszt  "u"
#else
#define PRIszt "zu"
#endif
