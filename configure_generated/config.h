/* library names */
#define BMX_LIBRARY_NAME     "bmx"

/* Library versions */
#define BMX_VERSION_MAJOR 1
#define BMX_VERSION_MINOR 2

/* Define printf size_t format specifier */
#if defined(_WIN64)
#define PRIszt  "I64u"
#elif defined(_WIN32)
#define PRIszt  "u"
#else
#define PRIszt "zu"
#endif

/* Define if CURL library is available for reading MXF files over HTTP */
/* #undef HAVE_LIBCURL */
