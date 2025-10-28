#pragma once

#ifndef GL_CURRENT_PROGRAM
    #define GL_CURRENT_PROGRAM 0x8B8D
#endif

#ifndef GL_BLEND_COLOR
    #define GL_BLEND_COLOR 0x8005
#endif

#ifndef GL_TEXTURE0
    #define GL_TEXTURE0 0x84C0
#endif

#ifndef GL_CONSTANT_COLOR
    #define GL_CONSTANT_COLOR 0x8001
#endif

#ifndef GL_FRAGMENT_SHADER
    #define GL_FRAGMENT_SHADER 0x8B30
#endif

#ifndef GL_VERTEX_SHADER
    #define GL_VERTEX_SHADER 0x8B31
#endif

#ifndef GL_LINK_STATUS
    #define GL_LINK_STATUS 0x8B82
#endif

#ifndef GL_COMPILE_STATUS
    #define GL_COMPILE_STATUS 0x8B81
#endif

#ifndef GL_RGBA
    #define GL_RGBA 0x1908
#endif

#ifndef GL_UNSIGNED_BYTE
    #define GL_UNSIGNED_BYTE 0x1401
#endif

#ifndef GL_TEXTURE_2D
    #define GL_TEXTURE_2D 0x0DE1
#endif

#ifndef GL_TEXTURE_MIN_FILTER
    #define GL_TEXTURE_MIN_FILTER 0x2801
#endif

#ifndef GL_TEXTURE_MAG_FILTER
    #define GL_TEXTURE_MAG_FILTER 0x2800
#endif

#ifndef GL_TEXTURE_WRAP_S
    #define GL_TEXTURE_WRAP_S 0x2802
#endif

#ifndef GL_TEXTURE_WRAP_T
    #define GL_TEXTURE_WRAP_T 0x2803
#endif

#ifndef GL_LINEAR
    #define GL_LINEAR 0x2601
#endif

#ifndef GL_FRAMEBUFFER
    #define GL_FRAMEBUFFER 0x8D40
#endif

#ifndef GL_COLOR_ATTACHMENT0
    #define GL_COLOR_ATTACHMENT0 0x8CE0
#endif

#ifndef GL_FRAMEBUFFER_BINDING
    #define GL_FRAMEBUFFER_BINDING 0x8CA6
#endif

#ifndef GL_VIEWPORT
    #define GL_VIEWPORT 0x0BA2
#endif

#ifndef GL_ARRAY_BUFFER
    #define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
    #define GL_STATIC_DRAW 0x88E4
#endif

#ifndef GL_TRIANGLE_STRIP
    #define GL_TRIANGLE_STRIP 0x0005
#endif

#ifndef GL_FLOAT
    #define GL_FLOAT 0x1406
#endif

#ifndef GLchar
typedef char GLchar;
#endif

#ifndef GLsizeiptr
typedef ptrdiff_t GLsizeiptr;
#endif

typedef GLint(APIENTRY* glGetUniformLocation_fn)(GLuint, const char*);
typedef void(APIENTRY* glGetUniformfv_fn)(GLuint, GLint, GLfloat*);
typedef void(APIENTRY* glBlendColor_fn)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void(APIENTRY* glUniform3f_fn)(GLint, GLfloat, GLfloat, GLfloat);
typedef void(APIENTRY* glUniform1f_fn)(GLint, GLfloat);
typedef void(APIENTRY* glUniform2f_fn)(GLint, GLfloat, GLfloat);
typedef void(APIENTRY* glActiveTexture_fn)(GLenum);
typedef void(APIENTRY* glGetUniformiv_fn)(GLuint, GLint, GLint*);
typedef void(APIENTRY* glUniform4f_fn)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);

typedef void(APIENTRY* glAttachShader_fn)(GLuint, GLuint);
typedef void(APIENTRY* glLinkProgram_fn)(GLuint);
typedef GLuint(APIENTRY* glCreateProgram_fn)();
typedef void(APIENTRY* glGetAttachedShaders_fn)(GLuint, GLsizei, GLsizei*, GLuint*);
typedef void(APIENTRY* glGetProgramInfoLog_fn)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void(APIENTRY* glGetProgramiv_fn)(GLuint, GLenum, GLint*);
typedef void(APIENTRY* glUseProgram_fn)(GLuint);
typedef void(APIENTRY* glUniform1i_fn)(GLint, GLint);
typedef GLuint(APIENTRY* glCreateShader_fn)(GLenum);
typedef void(APIENTRY* glShaderSource_fn)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void(APIENTRY* glCompileShader_fn)(GLuint);
typedef void(APIENTRY* glGetShaderiv_fn)(GLuint, GLenum, GLint*);
typedef void(APIENTRY* glGetShaderInfoLog_fn)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void(APIENTRY* glUniformMatrix4fv_fn)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void(APIENTRY* glDeleteShader_fn)(GLuint);

typedef void(APIENTRY* glGenTextures_fn)(GLsizei, GLuint*);
typedef void(APIENTRY* glBindTexture_fn)(GLenum, GLuint);
typedef void(APIENTRY* glTexImage2D_fn)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void(APIENTRY* glTexParameteri_fn)(GLenum, GLenum, GLint);

typedef void(APIENTRY* glGenFramebuffers_fn)(GLsizei, GLuint*);
typedef void(APIENTRY* glBindFramebuffer_fn)(GLenum, GLuint);
typedef void(APIENTRY* glFramebufferTexture2D_fn)(GLenum, GLenum, GLenum, GLuint, GLint);
typedef void(APIENTRY* glViewport_fn)(GLint, GLint, GLsizei, GLsizei);
typedef void(APIENTRY* glGenVertexArrays_fn)(GLsizei, GLuint*);
typedef void(APIENTRY* glBindVertexArray_fn)(GLuint);
typedef void(APIENTRY* glGenBuffers_fn)(GLsizei, GLuint*);
typedef void(APIENTRY* glBindBuffer_fn)(GLenum, GLuint);
typedef void(APIENTRY* glBufferData_fn)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void(APIENTRY* glVertexAttribPointer_fn)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void(APIENTRY* glEnableVertexAttribArray_fn)(GLuint);
typedef void(APIENTRY* glDrawArrays_fn)(GLenum, GLint, GLsizei);
typedef void(APIENTRY* glDeleteVertexArrays_fn)(GLsizei, const GLuint*);
typedef void(APIENTRY* glDeleteBuffers_fn)(GLsizei, const GLuint*);

namespace gl_cache {
    inline glGetUniformLocation_fn cached_glGetUniformLocation = nullptr;
    inline glGetUniformfv_fn cached_glGetUniformfv = nullptr;
    inline glBlendColor_fn cached_glBlendColor = nullptr;
    inline glUniform3f_fn cached_glUniform3f = nullptr;
    inline glUniform1f_fn cached_glUniform1f = nullptr;
    inline glUniform2f_fn cached_glUniform2f = nullptr;
    inline glActiveTexture_fn cached_glActiveTexture = nullptr;
    inline glGetUniformiv_fn cached_glGetUniformiv = nullptr;
    inline glUniform4f_fn cached_glUniform4f = nullptr;
    inline glAttachShader_fn cached_glAttachShader = nullptr;
    inline glLinkProgram_fn cached_glLinkProgram = nullptr;
    inline glCreateProgram_fn cached_glCreateProgram = nullptr;
    inline glGetAttachedShaders_fn cached_glGetAttachedShaders = nullptr;
    inline glGetProgramInfoLog_fn cached_glGetProgramInfoLog = nullptr;
    inline glGetProgramiv_fn cached_glGetProgramiv = nullptr;
    inline glUseProgram_fn cached_glUseProgram = nullptr;
    inline glUniform1i_fn cached_glUniform1i = nullptr;
    inline glCreateShader_fn cached_glCreateShader = nullptr;
    inline glShaderSource_fn cached_glShaderSource = nullptr;
    inline glCompileShader_fn cached_glCompileShader = nullptr;
    inline glGetShaderiv_fn cached_glGetShaderiv = nullptr;
    inline glGetShaderInfoLog_fn cached_glGetShaderInfoLog = nullptr;
    inline glUniformMatrix4fv_fn cached_glUniformMatrix4fv = nullptr;
    inline glDeleteShader_fn cached_glDeleteShader = nullptr;
    inline glGenTextures_fn cached_glGenTextures = nullptr;
    inline glBindTexture_fn cached_glBindTexture = nullptr;
    inline glTexImage2D_fn cached_glTexImage2D = nullptr;
    inline glTexParameteri_fn cached_glTexParameteri = nullptr;
    inline glGenFramebuffers_fn cached_glGenFramebuffers = nullptr;
    inline glBindFramebuffer_fn cached_glBindFramebuffer = nullptr;
    inline glFramebufferTexture2D_fn cached_glFramebufferTexture2D = nullptr;
    inline glViewport_fn cached_glViewport = nullptr;
    inline glGenVertexArrays_fn cached_glGenVertexArrays = nullptr;
    inline glBindVertexArray_fn cached_glBindVertexArray = nullptr;
    inline glGenBuffers_fn cached_glGenBuffers = nullptr;
    inline glBindBuffer_fn cached_glBindBuffer = nullptr;
    inline glBufferData_fn cached_glBufferData = nullptr;
    inline glVertexAttribPointer_fn cached_glVertexAttribPointer = nullptr;
    inline glEnableVertexAttribArray_fn cached_glEnableVertexAttribArray = nullptr;
    inline glDrawArrays_fn cached_glDrawArrays = nullptr;
    inline glDeleteVertexArrays_fn cached_glDeleteVertexArrays = nullptr;
    inline glDeleteBuffers_fn cached_glDeleteBuffers = nullptr;
}

inline GLint glGetUniformLocation(GLuint program, const char* name) {
    if (!gl_cache::cached_glGetUniformLocation)
        gl_cache::cached_glGetUniformLocation = reinterpret_cast<glGetUniformLocation_fn>(wglGetProcAddress("glGetUniformLocation"));
    if (gl_cache::cached_glGetUniformLocation)
        return gl_cache::cached_glGetUniformLocation(program, name);
    return 0;
}

inline void glGetUniformfv(GLuint program, GLint location, GLfloat* params) {
    if (!gl_cache::cached_glGetUniformfv)
        gl_cache::cached_glGetUniformfv = reinterpret_cast<glGetUniformfv_fn>(wglGetProcAddress("glGetUniformfv"));
    if (gl_cache::cached_glGetUniformfv)
        gl_cache::cached_glGetUniformfv(program, location, params);
}

inline void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    if (!gl_cache::cached_glBlendColor)
        gl_cache::cached_glBlendColor = reinterpret_cast<glBlendColor_fn>(wglGetProcAddress("glBlendColor"));
    if (gl_cache::cached_glBlendColor)
        gl_cache::cached_glBlendColor(red, green, blue, alpha);
}

inline void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    if (!gl_cache::cached_glUniform3f)
        gl_cache::cached_glUniform3f = reinterpret_cast<glUniform3f_fn>(wglGetProcAddress("glUniform3f"));
    if (gl_cache::cached_glUniform3f)
        gl_cache::cached_glUniform3f(location, v0, v1, v2);
}

inline void glUniform1f(GLint location, GLfloat v0) {
    if (!gl_cache::cached_glUniform1f)
        gl_cache::cached_glUniform1f = reinterpret_cast<glUniform1f_fn>(wglGetProcAddress("glUniform1f"));
    if (gl_cache::cached_glUniform1f)
        gl_cache::cached_glUniform1f(location, v0);
}

inline void glUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    if (!gl_cache::cached_glUniform2f)
        gl_cache::cached_glUniform2f = reinterpret_cast<glUniform2f_fn>(wglGetProcAddress("glUniform2f"));
    if (gl_cache::cached_glUniform2f)
        gl_cache::cached_glUniform2f(location, v0, v1);
}

inline void glActiveTexture(GLenum texture) {
    if (!gl_cache::cached_glActiveTexture)
        gl_cache::cached_glActiveTexture = reinterpret_cast<glActiveTexture_fn>(wglGetProcAddress("glActiveTexture"));
    if (gl_cache::cached_glActiveTexture)
        gl_cache::cached_glActiveTexture(texture);
}

inline void glGetUniformiv(GLuint program, GLint location, GLint* params) {
    if (!gl_cache::cached_glGetUniformiv)
        gl_cache::cached_glGetUniformiv = reinterpret_cast<glGetUniformiv_fn>(wglGetProcAddress("glGetUniformiv"));
    if (gl_cache::cached_glGetUniformiv)
        gl_cache::cached_glGetUniformiv(program, location, params);
}

inline void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    if (!gl_cache::cached_glUniform4f)
        gl_cache::cached_glUniform4f = reinterpret_cast<glUniform4f_fn>(wglGetProcAddress("glUniform4f"));
    if (gl_cache::cached_glUniform4f)
        gl_cache::cached_glUniform4f(location, v0, v1, v2, v3);
}

inline void glAttachShader(GLuint program, GLuint shader) {
    if (!gl_cache::cached_glAttachShader)
        gl_cache::cached_glAttachShader = reinterpret_cast<glAttachShader_fn>(wglGetProcAddress("glAttachShader"));
    if (gl_cache::cached_glAttachShader)
        gl_cache::cached_glAttachShader(program, shader);
}

inline void glLinkProgram(GLuint program) {
    if (!gl_cache::cached_glLinkProgram)
        gl_cache::cached_glLinkProgram = reinterpret_cast<glLinkProgram_fn>(wglGetProcAddress("glLinkProgram"));
    if (gl_cache::cached_glLinkProgram)
        gl_cache::cached_glLinkProgram(program);
}

inline GLuint glCreateProgram() {
    if (!gl_cache::cached_glCreateProgram)
        gl_cache::cached_glCreateProgram = reinterpret_cast<glCreateProgram_fn>(wglGetProcAddress("glCreateProgram"));
    if (gl_cache::cached_glCreateProgram)
        return gl_cache::cached_glCreateProgram();
    return 0;
}

inline void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders) {
    if (!gl_cache::cached_glGetAttachedShaders)
        gl_cache::cached_glGetAttachedShaders = reinterpret_cast<glGetAttachedShaders_fn>(wglGetProcAddress("glGetAttachedShaders"));
    if (gl_cache::cached_glGetAttachedShaders)
        gl_cache::cached_glGetAttachedShaders(program, maxCount, count, shaders);
}

inline void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    if (!gl_cache::cached_glGetProgramInfoLog)
        gl_cache::cached_glGetProgramInfoLog = reinterpret_cast<glGetProgramInfoLog_fn>(wglGetProcAddress("glGetProgramInfoLog"));
    if (gl_cache::cached_glGetProgramInfoLog)
        gl_cache::cached_glGetProgramInfoLog(program, bufSize, length, infoLog);
}

inline void glGetProgramiv(GLuint program, GLenum pname, GLint* params) {
    if (!gl_cache::cached_glGetProgramiv)
        gl_cache::cached_glGetProgramiv = reinterpret_cast<glGetProgramiv_fn>(wglGetProcAddress("glGetProgramiv"));
    if (gl_cache::cached_glGetProgramiv)
        gl_cache::cached_glGetProgramiv(program, pname, params);
}

inline void glUseProgram(GLuint program) {
    if (!gl_cache::cached_glUseProgram)
        gl_cache::cached_glUseProgram = reinterpret_cast<glUseProgram_fn>(wglGetProcAddress("glUseProgram"));
    if (gl_cache::cached_glUseProgram)
        gl_cache::cached_glUseProgram(program);
}

inline void glUniform1i(GLint location, GLint v0) {
    if (!gl_cache::cached_glUniform1i)
        gl_cache::cached_glUniform1i = reinterpret_cast<glUniform1i_fn>(wglGetProcAddress("glUniform1i"));
    if (gl_cache::cached_glUniform1i)
        gl_cache::cached_glUniform1i(location, v0);
}

inline GLuint glCreateShader(GLenum type) {
    if (!gl_cache::cached_glCreateShader)
        gl_cache::cached_glCreateShader = reinterpret_cast<glCreateShader_fn>(wglGetProcAddress("glCreateShader"));
    if (gl_cache::cached_glCreateShader)
        return gl_cache::cached_glCreateShader(type);
    return 0;
}

inline void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
    if (!gl_cache::cached_glShaderSource)
        gl_cache::cached_glShaderSource = reinterpret_cast<glShaderSource_fn>(wglGetProcAddress("glShaderSource"));
    if (gl_cache::cached_glShaderSource)
        gl_cache::cached_glShaderSource(shader, count, string, length);
}

inline void glCompileShader(GLuint shader) {
    if (!gl_cache::cached_glCompileShader)
        gl_cache::cached_glCompileShader = reinterpret_cast<glCompileShader_fn>(wglGetProcAddress("glCompileShader"));
    if (gl_cache::cached_glCompileShader)
        gl_cache::cached_glCompileShader(shader);
}

inline void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {
    if (!gl_cache::cached_glGetShaderiv)
        gl_cache::cached_glGetShaderiv = reinterpret_cast<glGetShaderiv_fn>(wglGetProcAddress("glGetShaderiv"));
    if (gl_cache::cached_glGetShaderiv)
        gl_cache::cached_glGetShaderiv(shader, pname, params);
}

inline void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    if (!gl_cache::cached_glGetShaderInfoLog)
        gl_cache::cached_glGetShaderInfoLog = reinterpret_cast<glGetShaderInfoLog_fn>(wglGetProcAddress("glGetShaderInfoLog"));
    if (gl_cache::cached_glGetShaderInfoLog)
        gl_cache::cached_glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

inline void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    if (!gl_cache::cached_glUniformMatrix4fv)
        gl_cache::cached_glUniformMatrix4fv = reinterpret_cast<glUniformMatrix4fv_fn>(wglGetProcAddress("glUniformMatrix4fv"));
    if (gl_cache::cached_glUniformMatrix4fv)
        gl_cache::cached_glUniformMatrix4fv(location, count, transpose, value);
}

inline void glDeleteShader(GLuint shader) {
    if (!gl_cache::cached_glDeleteShader)
        gl_cache::cached_glDeleteShader = reinterpret_cast<glDeleteShader_fn>(wglGetProcAddress("glDeleteShader"));
    if (gl_cache::cached_glDeleteShader)
        gl_cache::cached_glDeleteShader(shader);
}

inline void glGenTextures(GLsizei n, GLuint* textures) {
    if (!gl_cache::cached_glGenTextures)
        gl_cache::cached_glGenTextures = reinterpret_cast<glGenTextures_fn>(wglGetProcAddress("glGenTextures"));
    if (gl_cache::cached_glGenTextures)
        gl_cache::cached_glGenTextures(n, textures);
}

inline void glBindTexture(GLenum target, GLuint texture) {
    if (!gl_cache::cached_glBindTexture)
        gl_cache::cached_glBindTexture = reinterpret_cast<glBindTexture_fn>(wglGetProcAddress("glBindTexture"));
    if (gl_cache::cached_glBindTexture)
        gl_cache::cached_glBindTexture(target, texture);
}

inline void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
    if (!gl_cache::cached_glTexImage2D)
        gl_cache::cached_glTexImage2D = reinterpret_cast<glTexImage2D_fn>(wglGetProcAddress("glTexImage2D"));
    if (gl_cache::cached_glTexImage2D)
        gl_cache::cached_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

inline void glTexParameteri(GLenum target, GLenum pname, GLint param) {
    if (!gl_cache::cached_glTexParameteri)
        gl_cache::cached_glTexParameteri = reinterpret_cast<glTexParameteri_fn>(wglGetProcAddress("glTexParameteri"));
    if (gl_cache::cached_glTexParameteri)
        gl_cache::cached_glTexParameteri(target, pname, param);
}

inline void glGenFramebuffers(GLsizei n, GLuint* framebuffers) {
    if (!gl_cache::cached_glGenFramebuffers)
        gl_cache::cached_glGenFramebuffers = reinterpret_cast<glGenFramebuffers_fn>(wglGetProcAddress("glGenFramebuffers"));
    if (gl_cache::cached_glGenFramebuffers)
        gl_cache::cached_glGenFramebuffers(n, framebuffers);
}

inline void glBindFramebuffer(GLenum target, GLuint framebuffer) {
    if (!gl_cache::cached_glBindFramebuffer)
        gl_cache::cached_glBindFramebuffer = reinterpret_cast<glBindFramebuffer_fn>(wglGetProcAddress("glBindFramebuffer"));
    if (gl_cache::cached_glBindFramebuffer)
        gl_cache::cached_glBindFramebuffer(target, framebuffer);
}

inline void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    if (!gl_cache::cached_glFramebufferTexture2D)
        gl_cache::cached_glFramebufferTexture2D = reinterpret_cast<glFramebufferTexture2D_fn>(wglGetProcAddress("glFramebufferTexture2D"));
    if (gl_cache::cached_glFramebufferTexture2D)
        gl_cache::cached_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

inline void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    if (!gl_cache::cached_glViewport)
        gl_cache::cached_glViewport = reinterpret_cast<glViewport_fn>(wglGetProcAddress("glViewport"));
    if (gl_cache::cached_glViewport)
        gl_cache::cached_glViewport(x, y, width, height);
}

inline void glGenVertexArrays(GLsizei n, GLuint* arrays) {
    if (!gl_cache::cached_glGenVertexArrays)
        gl_cache::cached_glGenVertexArrays = reinterpret_cast<glGenVertexArrays_fn>(wglGetProcAddress("glGenVertexArrays"));
    if (gl_cache::cached_glGenVertexArrays)
        gl_cache::cached_glGenVertexArrays(n, arrays);
}

inline void glBindVertexArray(GLuint array) {
    if (!gl_cache::cached_glBindVertexArray)
        gl_cache::cached_glBindVertexArray = reinterpret_cast<glBindVertexArray_fn>(wglGetProcAddress("glBindVertexArray"));
    if (gl_cache::cached_glBindVertexArray)
        gl_cache::cached_glBindVertexArray(array);
}

inline void glGenBuffers(GLsizei n, GLuint* buffers) {
    if (!gl_cache::cached_glGenBuffers)
        gl_cache::cached_glGenBuffers = reinterpret_cast<glGenBuffers_fn>(wglGetProcAddress("glGenBuffers"));
    if (gl_cache::cached_glGenBuffers)
        gl_cache::cached_glGenBuffers(n, buffers);
}

inline void glBindBuffer(GLenum target, GLuint buffer) {
    if (!gl_cache::cached_glBindBuffer)
        gl_cache::cached_glBindBuffer = reinterpret_cast<glBindBuffer_fn>(wglGetProcAddress("glBindBuffer"));
    if (gl_cache::cached_glBindBuffer)
        gl_cache::cached_glBindBuffer(target, buffer);
}

inline void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
    if (!gl_cache::cached_glBufferData)
        gl_cache::cached_glBufferData = reinterpret_cast<glBufferData_fn>(wglGetProcAddress("glBufferData"));
    if (gl_cache::cached_glBufferData)
        gl_cache::cached_glBufferData(target, size, data, usage);
}

inline void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    if (!gl_cache::cached_glVertexAttribPointer)
        gl_cache::cached_glVertexAttribPointer = reinterpret_cast<glVertexAttribPointer_fn>(wglGetProcAddress("glVertexAttribPointer"));
    if (gl_cache::cached_glVertexAttribPointer)
        gl_cache::cached_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

inline void glEnableVertexAttribArray(GLuint index) {
    if (!gl_cache::cached_glEnableVertexAttribArray)
        gl_cache::cached_glEnableVertexAttribArray = reinterpret_cast<glEnableVertexAttribArray_fn>(wglGetProcAddress("glEnableVertexAttribArray"));
    if (gl_cache::cached_glEnableVertexAttribArray)
        gl_cache::cached_glEnableVertexAttribArray(index);
}

inline void glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    if (!gl_cache::cached_glDrawArrays)
        gl_cache::cached_glDrawArrays = reinterpret_cast<glDrawArrays_fn>(wglGetProcAddress("glDrawArrays"));
    if (gl_cache::cached_glDrawArrays)
        gl_cache::cached_glDrawArrays(mode, first, count);
}

inline void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    if (!gl_cache::cached_glDeleteVertexArrays)
        gl_cache::cached_glDeleteVertexArrays = reinterpret_cast<glDeleteVertexArrays_fn>(wglGetProcAddress("glDeleteVertexArrays"));
    if (gl_cache::cached_glDeleteVertexArrays)
        gl_cache::cached_glDeleteVertexArrays(n, arrays);
}

inline void glDeleteBuffers(GLsizei n, const GLuint* buffers) {
    if (!gl_cache::cached_glDeleteBuffers)
        gl_cache::cached_glDeleteBuffers = reinterpret_cast<glDeleteBuffers_fn>(wglGetProcAddress("glDeleteBuffers"));
    if (gl_cache::cached_glDeleteBuffers)
        gl_cache::cached_glDeleteBuffers(n, buffers);
}