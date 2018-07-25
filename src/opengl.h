#ifndef __libmolphene__opengl__
#define __libmolphene__opengl__

#include <iostream>

#ifdef _WIN64

#elif _WIN32

#elif __APPLE__

#include "TargetConditionals.h"
#if TARGET_OS_IPHONE

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#if TARGET_IPHONE_SIMULATOR

#endif

#else

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

#endif

#elif __ANDROID__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#elif __linux

#elif __unix

#elif __posix

#endif

#endif
