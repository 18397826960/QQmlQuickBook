﻿//
// AUTOGENERATED, DO NOT EDIT
//
#ifndef OPENCV_CORE_OCL_RUNTIME_OPENCL_GL_WRAPPERS_HPP
#error "Invalid usage"
#endif

#ifdef cl_khr_gl_sharing

// generated by parser_cl.py
#undef clCreateFromGLBuffer
#define clCreateFromGLBuffer clCreateFromGLBuffer_fn
inline cl_mem clCreateFromGLBuffer(cl_context p0, cl_mem_flags p1, cl_GLuint p2, int* p3) { return clCreateFromGLBuffer_pfn(p0, p1, p2, p3); }
#undef clCreateFromGLRenderbuffer
#define clCreateFromGLRenderbuffer clCreateFromGLRenderbuffer_fn
inline cl_mem clCreateFromGLRenderbuffer(cl_context p0, cl_mem_flags p1, cl_GLuint p2, cl_int* p3) { return clCreateFromGLRenderbuffer_pfn(p0, p1, p2, p3); }
#undef clCreateFromGLTexture
#define clCreateFromGLTexture clCreateFromGLTexture_fn
inline cl_mem clCreateFromGLTexture(cl_context p0, cl_mem_flags p1, cl_GLenum p2, cl_GLint p3, cl_GLuint p4, cl_int* p5) { return clCreateFromGLTexture_pfn(p0, p1, p2, p3, p4, p5); }
#undef clCreateFromGLTexture2D
#define clCreateFromGLTexture2D clCreateFromGLTexture2D_fn
inline cl_mem clCreateFromGLTexture2D(cl_context p0, cl_mem_flags p1, cl_GLenum p2, cl_GLint p3, cl_GLuint p4, cl_int* p5) { return clCreateFromGLTexture2D_pfn(p0, p1, p2, p3, p4, p5); }
#undef clCreateFromGLTexture3D
#define clCreateFromGLTexture3D clCreateFromGLTexture3D_fn
inline cl_mem clCreateFromGLTexture3D(cl_context p0, cl_mem_flags p1, cl_GLenum p2, cl_GLint p3, cl_GLuint p4, cl_int* p5) { return clCreateFromGLTexture3D_pfn(p0, p1, p2, p3, p4, p5); }
#undef clEnqueueAcquireGLObjects
#define clEnqueueAcquireGLObjects clEnqueueAcquireGLObjects_fn
inline cl_int clEnqueueAcquireGLObjects(cl_command_queue p0, cl_uint p1, const cl_mem* p2, cl_uint p3, const cl_event* p4, cl_event* p5) { return clEnqueueAcquireGLObjects_pfn(p0, p1, p2, p3, p4, p5); }
#undef clEnqueueReleaseGLObjects
#define clEnqueueReleaseGLObjects clEnqueueReleaseGLObjects_fn
inline cl_int clEnqueueReleaseGLObjects(cl_command_queue p0, cl_uint p1, const cl_mem* p2, cl_uint p3, const cl_event* p4, cl_event* p5) { return clEnqueueReleaseGLObjects_pfn(p0, p1, p2, p3, p4, p5); }
#undef clGetGLContextInfoKHR
#define clGetGLContextInfoKHR clGetGLContextInfoKHR_fn
inline cl_int clGetGLContextInfoKHR(const cl_context_properties* p0, cl_gl_context_info p1, size_t p2, void* p3, size_t* p4) { return clGetGLContextInfoKHR_pfn(p0, p1, p2, p3, p4); }
#undef clGetGLObjectInfo
#define clGetGLObjectInfo clGetGLObjectInfo_fn
inline cl_int clGetGLObjectInfo(cl_mem p0, cl_gl_object_type* p1, cl_GLuint* p2) { return clGetGLObjectInfo_pfn(p0, p1, p2); }
#undef clGetGLTextureInfo
#define clGetGLTextureInfo clGetGLTextureInfo_fn
inline cl_int clGetGLTextureInfo(cl_mem p0, cl_gl_texture_info p1, size_t p2, void* p3, size_t* p4) { return clGetGLTextureInfo_pfn(p0, p1, p2, p3, p4); }

#endif // cl_khr_gl_sharing
