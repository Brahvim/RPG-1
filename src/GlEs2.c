/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gles2.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif



int GLAD_GL_ES_VERSION_2_0 = 0;
int GLAD_GL_ES_VERSION_3_0 = 0;



PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = NULL;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
PFNGLBINDSAMPLERPROC glBindSampler = NULL;
PFNGLBINDTEXTUREPROC glBindTexture = NULL;
PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = NULL;
PFNGLBLENDFUNCPROC glBlendFunc = NULL;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLCLEARPROC glClear = NULL;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = NULL;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = NULL;
PFNGLCLEARCOLORPROC glClearColor = NULL;
PFNGLCLEARDEPTHFPROC glClearDepthf = NULL;
PFNGLCLEARSTENCILPROC glClearStencil = NULL;
PFNGLCLIENTWAITSYNCPROC glClientWaitSync = NULL;
PFNGLCOLORMASKPROC glColorMask = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = NULL;
PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLCULLFACEPROC glCullFace = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;
PFNGLDELETESAMPLERSPROC glDeleteSamplers = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDELETESYNCPROC glDeleteSync = NULL;
PFNGLDELETETEXTURESPROC glDeleteTextures = NULL;
PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLDEPTHFUNCPROC glDepthFunc = NULL;
PFNGLDEPTHMASKPROC glDepthMask = NULL;
PFNGLDEPTHRANGEFPROC glDepthRangef = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLDISABLEPROC glDisable = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLDRAWARRAYSPROC glDrawArrays = NULL;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLDRAWELEMENTSPROC glDrawElements = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLENABLEPROC glEnable = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = NULL;
PFNGLFENCESYNCPROC glFenceSync = NULL;
PFNGLFINISHPROC glFinish = NULL;
PFNGLFLUSHPROC glFlush = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = NULL;
PFNGLFRONTFACEPROC glFrontFace = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
PFNGLGENSAMPLERSPROC glGenSamplers = NULL;
PFNGLGENTEXTURESPROC glGenTextures = NULL;
PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = NULL;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETBOOLEANVPROC glGetBooleanv = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = NULL;
PFNGLGETERRORPROC glGetError = NULL;
PFNGLGETFLOATVPROC glGetFloatv = NULL;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = NULL;
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = NULL;
PFNGLGETINTEGER64VPROC glGetInteger64v = NULL;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = NULL;
PFNGLGETINTEGERVPROC glGetIntegerv = NULL;
PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = NULL;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = NULL;
PFNGLGETQUERYIVPROC glGetQueryiv = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = NULL;
PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = NULL;
PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = NULL;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSTRINGPROC glGetString = NULL;
PFNGLGETSTRINGIPROC glGetStringi = NULL;
PFNGLGETSYNCIVPROC glGetSynciv = NULL;
PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = NULL;
PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = NULL;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC glGetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC glGetUniformiv = NULL;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = NULL;
PFNGLHINTPROC glHint = NULL;
PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = NULL;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLISENABLEDPROC glIsEnabled = NULL;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
PFNGLISQUERYPROC glIsQuery = NULL;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = NULL;
PFNGLISSAMPLERPROC glIsSampler = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLISSYNCPROC glIsSync = NULL;
PFNGLISTEXTUREPROC glIsTexture = NULL;
PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = NULL;
PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;
PFNGLLINEWIDTHPROC glLineWidth = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = NULL;
PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = NULL;
PFNGLPIXELSTOREIPROC glPixelStorei = NULL;
PFNGLPOLYGONOFFSETPROC glPolygonOffset = NULL;
PFNGLPROGRAMBINARYPROC glProgramBinary = NULL;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = NULL;
PFNGLREADBUFFERPROC glReadBuffer = NULL;
PFNGLREADPIXELSPROC glReadPixels = NULL;
PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = NULL;
PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = NULL;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;
PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = NULL;
PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = NULL;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = NULL;
PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = NULL;
PFNGLSCISSORPROC glScissor = NULL;
PFNGLSHADERBINARYPROC glShaderBinary = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLSTENCILFUNCPROC glStencilFunc = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKPROC glStencilMask = NULL;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = NULL;
PFNGLSTENCILOPPROC glStencilOp = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;
PFNGLTEXIMAGE2DPROC glTexImage2D = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXPARAMETERFPROC glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glTexParameteriv = NULL;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = NULL;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = NULL;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = NULL;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLVIEWPORTPROC glViewport = NULL;
PFNGLWAITSYNCPROC glWaitSync = NULL;


static void glad_gl_load_GL_ES_VERSION_2_0( GLADuserptrloadfunc load, void* userptr) {
	if(!GLAD_GL_ES_VERSION_2_0) return;
	glActiveTexture = (PFNGLACTIVETEXTUREPROC) load(userptr, "glActiveTexture");
	glAttachShader = (PFNGLATTACHSHADERPROC) load(userptr, "glAttachShader");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) load(userptr, "glBindAttribLocation");
	glBindBuffer = (PFNGLBINDBUFFERPROC) load(userptr, "glBindBuffer");
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) load(userptr, "glBindFramebuffer");
	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) load(userptr, "glBindRenderbuffer");
	glBindTexture = (PFNGLBINDTEXTUREPROC) load(userptr, "glBindTexture");
	glBlendColor = (PFNGLBLENDCOLORPROC) load(userptr, "glBlendColor");
	glBlendEquation = (PFNGLBLENDEQUATIONPROC) load(userptr, "glBlendEquation");
	glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) load(userptr, "glBlendEquationSeparate");
	glBlendFunc = (PFNGLBLENDFUNCPROC) load(userptr, "glBlendFunc");
	glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) load(userptr, "glBlendFuncSeparate");
	glBufferData = (PFNGLBUFFERDATAPROC) load(userptr, "glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC) load(userptr, "glBufferSubData");
	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) load(userptr, "glCheckFramebufferStatus");
	glClear = (PFNGLCLEARPROC) load(userptr, "glClear");
	glClearColor = (PFNGLCLEARCOLORPROC) load(userptr, "glClearColor");
	glClearDepthf = (PFNGLCLEARDEPTHFPROC) load(userptr, "glClearDepthf");
	glClearStencil = (PFNGLCLEARSTENCILPROC) load(userptr, "glClearStencil");
	glColorMask = (PFNGLCOLORMASKPROC) load(userptr, "glColorMask");
	glCompileShader = (PFNGLCOMPILESHADERPROC) load(userptr, "glCompileShader");
	glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load(userptr, "glCompressedTexImage2D");
	glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load(userptr, "glCompressedTexSubImage2D");
	glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load(userptr, "glCopyTexImage2D");
	glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load(userptr, "glCopyTexSubImage2D");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) load(userptr, "glCreateProgram");
	glCreateShader = (PFNGLCREATESHADERPROC) load(userptr, "glCreateShader");
	glCullFace = (PFNGLCULLFACEPROC) load(userptr, "glCullFace");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load(userptr, "glDeleteBuffers");
	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) load(userptr, "glDeleteFramebuffers");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) load(userptr, "glDeleteProgram");
	glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) load(userptr, "glDeleteRenderbuffers");
	glDeleteShader = (PFNGLDELETESHADERPROC) load(userptr, "glDeleteShader");
	glDeleteTextures = (PFNGLDELETETEXTURESPROC) load(userptr, "glDeleteTextures");
	glDepthFunc = (PFNGLDEPTHFUNCPROC) load(userptr, "glDepthFunc");
	glDepthMask = (PFNGLDEPTHMASKPROC) load(userptr, "glDepthMask");
	glDepthRangef = (PFNGLDEPTHRANGEFPROC) load(userptr, "glDepthRangef");
	glDetachShader = (PFNGLDETACHSHADERPROC) load(userptr, "glDetachShader");
	glDisable = (PFNGLDISABLEPROC) load(userptr, "glDisable");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) load(userptr, "glDisableVertexAttribArray");
	glDrawArrays = (PFNGLDRAWARRAYSPROC) load(userptr, "glDrawArrays");
	glDrawElements = (PFNGLDRAWELEMENTSPROC) load(userptr, "glDrawElements");
	glEnable = (PFNGLENABLEPROC) load(userptr, "glEnable");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) load(userptr, "glEnableVertexAttribArray");
	glFinish = (PFNGLFINISHPROC) load(userptr, "glFinish");
	glFlush = (PFNGLFLUSHPROC) load(userptr, "glFlush");
	glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) load(userptr, "glFramebufferRenderbuffer");
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) load(userptr, "glFramebufferTexture2D");
	glFrontFace = (PFNGLFRONTFACEPROC) load(userptr, "glFrontFace");
	glGenBuffers = (PFNGLGENBUFFERSPROC) load(userptr, "glGenBuffers");
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) load(userptr, "glGenFramebuffers");
	glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) load(userptr, "glGenRenderbuffers");
	glGenTextures = (PFNGLGENTEXTURESPROC) load(userptr, "glGenTextures");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) load(userptr, "glGenerateMipmap");
	glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) load(userptr, "glGetActiveAttrib");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) load(userptr, "glGetActiveUniform");
	glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) load(userptr, "glGetAttachedShaders");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) load(userptr, "glGetAttribLocation");
	glGetBooleanv = (PFNGLGETBOOLEANVPROC) load(userptr, "glGetBooleanv");
	glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load(userptr, "glGetBufferParameteriv");
	glGetError = (PFNGLGETERRORPROC) load(userptr, "glGetError");
	glGetFloatv = (PFNGLGETFLOATVPROC) load(userptr, "glGetFloatv");
	glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) load(userptr, "glGetFramebufferAttachmentParameteriv");
	glGetIntegerv = (PFNGLGETINTEGERVPROC) load(userptr, "glGetIntegerv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) load(userptr, "glGetProgramInfoLog");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) load(userptr, "glGetProgramiv");
	glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) load(userptr, "glGetRenderbufferParameteriv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) load(userptr, "glGetShaderInfoLog");
	glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC) load(userptr, "glGetShaderPrecisionFormat");
	glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) load(userptr, "glGetShaderSource");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) load(userptr, "glGetShaderiv");
	glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
	glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) load(userptr, "glGetTexParameterfv");
	glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) load(userptr, "glGetTexParameteriv");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) load(userptr, "glGetUniformLocation");
	glGetUniformfv = (PFNGLGETUNIFORMFVPROC) load(userptr, "glGetUniformfv");
	glGetUniformiv = (PFNGLGETUNIFORMIVPROC) load(userptr, "glGetUniformiv");
	glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) load(userptr, "glGetVertexAttribPointerv");
	glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) load(userptr, "glGetVertexAttribfv");
	glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) load(userptr, "glGetVertexAttribiv");
	glHint = (PFNGLHINTPROC) load(userptr, "glHint");
	glIsBuffer = (PFNGLISBUFFERPROC) load(userptr, "glIsBuffer");
	glIsEnabled = (PFNGLISENABLEDPROC) load(userptr, "glIsEnabled");
	glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) load(userptr, "glIsFramebuffer");
	glIsProgram = (PFNGLISPROGRAMPROC) load(userptr, "glIsProgram");
	glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) load(userptr, "glIsRenderbuffer");
	glIsShader = (PFNGLISSHADERPROC) load(userptr, "glIsShader");
	glIsTexture = (PFNGLISTEXTUREPROC) load(userptr, "glIsTexture");
	glLineWidth = (PFNGLLINEWIDTHPROC) load(userptr, "glLineWidth");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) load(userptr, "glLinkProgram");
	glPixelStorei = (PFNGLPIXELSTOREIPROC) load(userptr, "glPixelStorei");
	glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) load(userptr, "glPolygonOffset");
	glReadPixels = (PFNGLREADPIXELSPROC) load(userptr, "glReadPixels");
	glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC) load(userptr, "glReleaseShaderCompiler");
	glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) load(userptr, "glRenderbufferStorage");
	glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load(userptr, "glSampleCoverage");
	glScissor = (PFNGLSCISSORPROC) load(userptr, "glScissor");
	glShaderBinary = (PFNGLSHADERBINARYPROC) load(userptr, "glShaderBinary");
	glShaderSource = (PFNGLSHADERSOURCEPROC) load(userptr, "glShaderSource");
	glStencilFunc = (PFNGLSTENCILFUNCPROC) load(userptr, "glStencilFunc");
	glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) load(userptr, "glStencilFuncSeparate");
	glStencilMask = (PFNGLSTENCILMASKPROC) load(userptr, "glStencilMask");
	glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) load(userptr, "glStencilMaskSeparate");
	glStencilOp = (PFNGLSTENCILOPPROC) load(userptr, "glStencilOp");
	glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) load(userptr, "glStencilOpSeparate");
	glTexImage2D = (PFNGLTEXIMAGE2DPROC) load(userptr, "glTexImage2D");
	glTexParameterf = (PFNGLTEXPARAMETERFPROC) load(userptr, "glTexParameterf");
	glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) load(userptr, "glTexParameterfv");
	glTexParameteri = (PFNGLTEXPARAMETERIPROC) load(userptr, "glTexParameteri");
	glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) load(userptr, "glTexParameteriv");
	glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load(userptr, "glTexSubImage2D");
	glUniform1f = (PFNGLUNIFORM1FPROC) load(userptr, "glUniform1f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC) load(userptr, "glUniform1fv");
	glUniform1i = (PFNGLUNIFORM1IPROC) load(userptr, "glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC) load(userptr, "glUniform1iv");
	glUniform2f = (PFNGLUNIFORM2FPROC) load(userptr, "glUniform2f");
	glUniform2fv = (PFNGLUNIFORM2FVPROC) load(userptr, "glUniform2fv");
	glUniform2i = (PFNGLUNIFORM2IPROC) load(userptr, "glUniform2i");
	glUniform2iv = (PFNGLUNIFORM2IVPROC) load(userptr, "glUniform2iv");
	glUniform3f = (PFNGLUNIFORM3FPROC) load(userptr, "glUniform3f");
	glUniform3fv = (PFNGLUNIFORM3FVPROC) load(userptr, "glUniform3fv");
	glUniform3i = (PFNGLUNIFORM3IPROC) load(userptr, "glUniform3i");
	glUniform3iv = (PFNGLUNIFORM3IVPROC) load(userptr, "glUniform3iv");
	glUniform4f = (PFNGLUNIFORM4FPROC) load(userptr, "glUniform4f");
	glUniform4fv = (PFNGLUNIFORM4FVPROC) load(userptr, "glUniform4fv");
	glUniform4i = (PFNGLUNIFORM4IPROC) load(userptr, "glUniform4i");
	glUniform4iv = (PFNGLUNIFORM4IVPROC) load(userptr, "glUniform4iv");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) load(userptr, "glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) load(userptr, "glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) load(userptr, "glUniformMatrix4fv");
	glUseProgram = (PFNGLUSEPROGRAMPROC) load(userptr, "glUseProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) load(userptr, "glValidateProgram");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) load(userptr, "glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) load(userptr, "glVertexAttrib1fv");
	glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) load(userptr, "glVertexAttrib2f");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) load(userptr, "glVertexAttrib2fv");
	glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) load(userptr, "glVertexAttrib3f");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) load(userptr, "glVertexAttrib3fv");
	glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) load(userptr, "glVertexAttrib4f");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) load(userptr, "glVertexAttrib4fv");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) load(userptr, "glVertexAttribPointer");
	glViewport = (PFNGLVIEWPORTPROC) load(userptr, "glViewport");
}
static void glad_gl_load_GL_ES_VERSION_3_0( GLADuserptrloadfunc load, void* userptr) {
	if(!GLAD_GL_ES_VERSION_3_0) return;
	glBeginQuery = (PFNGLBEGINQUERYPROC) load(userptr, "glBeginQuery");
	glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) load(userptr, "glBeginTransformFeedback");
	glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load(userptr, "glBindBufferBase");
	glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) load(userptr, "glBindBufferRange");
	glBindSampler = (PFNGLBINDSAMPLERPROC) load(userptr, "glBindSampler");
	glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC) load(userptr, "glBindTransformFeedback");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) load(userptr, "glBindVertexArray");
	glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) load(userptr, "glBlitFramebuffer");
	glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) load(userptr, "glClearBufferfi");
	glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) load(userptr, "glClearBufferfv");
	glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) load(userptr, "glClearBufferiv");
	glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) load(userptr, "glClearBufferuiv");
	glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) load(userptr, "glClientWaitSync");
	glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) load(userptr, "glCompressedTexImage3D");
	glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) load(userptr, "glCompressedTexSubImage3D");
	glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) load(userptr, "glCopyBufferSubData");
	glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) load(userptr, "glCopyTexSubImage3D");
	glDeleteQueries = (PFNGLDELETEQUERIESPROC) load(userptr, "glDeleteQueries");
	glDeleteSamplers = (PFNGLDELETESAMPLERSPROC) load(userptr, "glDeleteSamplers");
	glDeleteSync = (PFNGLDELETESYNCPROC) load(userptr, "glDeleteSync");
	glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC) load(userptr, "glDeleteTransformFeedbacks");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) load(userptr, "glDeleteVertexArrays");
	glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) load(userptr, "glDrawArraysInstanced");
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC) load(userptr, "glDrawBuffers");
	glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) load(userptr, "glDrawElementsInstanced");
	glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) load(userptr, "glDrawRangeElements");
	glEndQuery = (PFNGLENDQUERYPROC) load(userptr, "glEndQuery");
	glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) load(userptr, "glEndTransformFeedback");
	glFenceSync = (PFNGLFENCESYNCPROC) load(userptr, "glFenceSync");
	glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) load(userptr, "glFlushMappedBufferRange");
	glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) load(userptr, "glFramebufferTextureLayer");
	glGenQueries = (PFNGLGENQUERIESPROC) load(userptr, "glGenQueries");
	glGenSamplers = (PFNGLGENSAMPLERSPROC) load(userptr, "glGenSamplers");
	glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC) load(userptr, "glGenTransformFeedbacks");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) load(userptr, "glGenVertexArrays");
	glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) load(userptr, "glGetActiveUniformBlockName");
	glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) load(userptr, "glGetActiveUniformBlockiv");
	glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) load(userptr, "glGetActiveUniformsiv");
	glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) load(userptr, "glGetBufferParameteri64v");
	glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) load(userptr, "glGetBufferPointerv");
	glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) load(userptr, "glGetFragDataLocation");
	glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) load(userptr, "glGetInteger64i_v");
	glGetInteger64v = (PFNGLGETINTEGER64VPROC) load(userptr, "glGetInteger64v");
	glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) load(userptr, "glGetIntegeri_v");
	glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC) load(userptr, "glGetInternalformativ");
	glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC) load(userptr, "glGetProgramBinary");
	glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) load(userptr, "glGetQueryObjectuiv");
	glGetQueryiv = (PFNGLGETQUERYIVPROC) load(userptr, "glGetQueryiv");
	glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) load(userptr, "glGetSamplerParameterfv");
	glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) load(userptr, "glGetSamplerParameteriv");
	glGetStringi = (PFNGLGETSTRINGIPROC) load(userptr, "glGetStringi");
	glGetSynciv = (PFNGLGETSYNCIVPROC) load(userptr, "glGetSynciv");
	glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) load(userptr, "glGetTransformFeedbackVarying");
	glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) load(userptr, "glGetUniformBlockIndex");
	glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) load(userptr, "glGetUniformIndices");
	glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) load(userptr, "glGetUniformuiv");
	glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) load(userptr, "glGetVertexAttribIiv");
	glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) load(userptr, "glGetVertexAttribIuiv");
	glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC) load(userptr, "glInvalidateFramebuffer");
	glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) load(userptr, "glInvalidateSubFramebuffer");
	glIsQuery = (PFNGLISQUERYPROC) load(userptr, "glIsQuery");
	glIsSampler = (PFNGLISSAMPLERPROC) load(userptr, "glIsSampler");
	glIsSync = (PFNGLISSYNCPROC) load(userptr, "glIsSync");
	glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC) load(userptr, "glIsTransformFeedback");
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC) load(userptr, "glIsVertexArray");
	glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) load(userptr, "glMapBufferRange");
	glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC) load(userptr, "glPauseTransformFeedback");
	glProgramBinary = (PFNGLPROGRAMBINARYPROC) load(userptr, "glProgramBinary");
	glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC) load(userptr, "glProgramParameteri");
	glReadBuffer = (PFNGLREADBUFFERPROC) load(userptr, "glReadBuffer");
	glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) load(userptr, "glRenderbufferStorageMultisample");
	glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC) load(userptr, "glResumeTransformFeedback");
	glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) load(userptr, "glSamplerParameterf");
	glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) load(userptr, "glSamplerParameterfv");
	glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) load(userptr, "glSamplerParameteri");
	glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) load(userptr, "glSamplerParameteriv");
	glTexImage3D = (PFNGLTEXIMAGE3DPROC) load(userptr, "glTexImage3D");
	glTexStorage2D = (PFNGLTEXSTORAGE2DPROC) load(userptr, "glTexStorage2D");
	glTexStorage3D = (PFNGLTEXSTORAGE3DPROC) load(userptr, "glTexStorage3D");
	glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) load(userptr, "glTexSubImage3D");
	glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) load(userptr, "glTransformFeedbackVaryings");
	glUniform1ui = (PFNGLUNIFORM1UIPROC) load(userptr, "glUniform1ui");
	glUniform1uiv = (PFNGLUNIFORM1UIVPROC) load(userptr, "glUniform1uiv");
	glUniform2ui = (PFNGLUNIFORM2UIPROC) load(userptr, "glUniform2ui");
	glUniform2uiv = (PFNGLUNIFORM2UIVPROC) load(userptr, "glUniform2uiv");
	glUniform3ui = (PFNGLUNIFORM3UIPROC) load(userptr, "glUniform3ui");
	glUniform3uiv = (PFNGLUNIFORM3UIVPROC) load(userptr, "glUniform3uiv");
	glUniform4ui = (PFNGLUNIFORM4UIPROC) load(userptr, "glUniform4ui");
	glUniform4uiv = (PFNGLUNIFORM4UIVPROC) load(userptr, "glUniform4uiv");
	glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) load(userptr, "glUniformBlockBinding");
	glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) load(userptr, "glUniformMatrix2x3fv");
	glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) load(userptr, "glUniformMatrix2x4fv");
	glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) load(userptr, "glUniformMatrix3x2fv");
	glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) load(userptr, "glUniformMatrix3x4fv");
	glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) load(userptr, "glUniformMatrix4x2fv");
	glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) load(userptr, "glUniformMatrix4x3fv");
	glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) load(userptr, "glUnmapBuffer");
	glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) load(userptr, "glVertexAttribDivisor");
	glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) load(userptr, "glVertexAttribI4i");
	glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) load(userptr, "glVertexAttribI4iv");
	glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) load(userptr, "glVertexAttribI4ui");
	glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) load(userptr, "glVertexAttribI4uiv");
	glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) load(userptr, "glVertexAttribIPointer");
	glWaitSync = (PFNGLWAITSYNCPROC) load(userptr, "glWaitSync");
}



static void glad_gl_free_extensions(char **exts_i) {
	if (exts_i != NULL) {
		unsigned int index;
		for(index = 0; exts_i[index]; index++) {
			free((void *) (exts_i[index]));
		}
		free((void *)exts_i);
		exts_i = NULL;
	}
}
static int glad_gl_get_extensions( const char **out_exts, char ***out_exts_i) {
#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
	if (glGetStringi != NULL && glGetIntegerv != NULL) {
		unsigned int index = 0;
		unsigned int num_exts_i = 0;
		char **exts_i = NULL;
		glGetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts_i);
		exts_i = (char **) malloc((num_exts_i + 1) * (sizeof *exts_i));
		if (exts_i == NULL) {
			return 0;
		}
		for(index = 0; index < num_exts_i; index++) {
			const char *gl_str_tmp = (const char*) glGetStringi(GL_EXTENSIONS, index);
			size_t len = strlen(gl_str_tmp) + 1;

			char *local_str = (char*) malloc(len * sizeof(char));
			if(local_str == NULL) {
				exts_i[index] = NULL;
				glad_gl_free_extensions(exts_i);
				return 0;
			}

			memcpy(local_str, gl_str_tmp, len * sizeof(char));
			exts_i[index] = local_str;
		}
		exts_i[index] = NULL;

		*out_exts_i = exts_i;

		return 1;
	}
#else
	GLAD_UNUSED(out_exts_i);
#endif
	if (glGetString == NULL) {
		return 0;
	}
	*out_exts = (const char *)glGetString(GL_EXTENSIONS);
	return 1;
}
static int glad_gl_has_extension(const char *exts, char **exts_i, const char *ext) {
	if(exts_i) {
		unsigned int index;
		for(index = 0; exts_i[index]; index++) {
			const char *e = exts_i[index];
			if(strcmp(e, ext) == 0) {
				return 1;
			}
		}
	} else {
		const char *extensions;
		const char *loc;
		const char *terminator;
		extensions = exts;
		if(extensions == NULL || ext == NULL) {
			return 0;
		}
		while(1) {
			loc = strstr(extensions, ext);
			if(loc == NULL) {
				return 0;
			}
			terminator = loc + strlen(ext);
			if((loc == extensions || *(loc - 1) == ' ') &&
				(*terminator == ' ' || *terminator == '\0')) {
				return 1;
			}
			extensions = terminator;
		}
	}
	return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(void *userptr, const char* name) {
	return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gles2(void) {
	const char *exts = NULL;
	char **exts_i = NULL;
	if (!glad_gl_get_extensions(&exts, &exts_i)) return 0;

	GLAD_UNUSED(&glad_gl_has_extension);

	glad_gl_free_extensions(exts_i);

	return 1;
}

static int glad_gl_find_core_gles2(void) {
	int i;
	const char* version;
	const char* prefixes[] = {
		"OpenGL ES-CM ",
		"OpenGL ES-CL ",
		"OpenGL ES ",
		"OpenGL SC ",
		NULL
	};
	int major = 0;
	int minor = 0;
	version = (const char*) glGetString(GL_VERSION);
	if (!version) return 0;
	for (i = 0;  prefixes[i];  i++) {
		const size_t length = strlen(prefixes[i]);
		if (strncmp(version, prefixes[i], length) == 0) {
			version += length;
			break;
		}
	}

	GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

	GLAD_GL_ES_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
	GLAD_GL_ES_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;

	return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLES2UserPtr( GLADuserptrloadfunc load, void *userptr) {
	int version;

	glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
	if(glGetString == NULL) return 0;
	version = glad_gl_find_core_gles2();

	glad_gl_load_GL_ES_VERSION_2_0(load, userptr);
	glad_gl_load_GL_ES_VERSION_3_0(load, userptr);

	if (!glad_gl_find_extensions_gles2()) return 0;



	return version;
}


int gladLoadGLES2( GLADloadfunc load) {
	return gladLoadGLES2UserPtr( glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 


#ifdef __cplusplus
}
#endif
