#ifndef Version_h
#define Version_h

//Version info
#define SUPER_VERSION 0
#define MAIN_VERSION 0
#define SUB_VERSION 1
#define REVISION 0
#ifdef __linux__
#undef REVISION
#define REVISION 0
#endif

#define VER1_(x) #x
#define VER_(x) VER1_(x)
#define VERSION_STRING VER_(SUPER_VERSION) "." VER_(MAIN_VERSION) "." VER_(SUB_VERSION) "-" VER_(REVISION)

#endif
