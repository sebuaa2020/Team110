/*********************
 音频合成的头文件
 ********************/
#ifndef __QTTS_H__
#define __QTTS_H__

#if !defined(MSPAPI)
#if defined(WIN32)
	#define MSPAPI __stdcall
#else
	#define MSPAPI
#endif /* WIN32 */
#endif /* MSPAPI */

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

#include "msp_types.h"

/**********************
 开始进程
 成功返回ID 否则返回NULL
 传入参数与进程ID
**********************/
const char* MSPAPI QTTSSessionBegin(const char* params, int* errorCode);
typedef const char* (MSPAPI *Proc_QTTSSessionBegin)(const char* params, int* errorCode);
#ifdef MSP_WCHAR_SUPPORT
const wchar_t* MSPAPI QTTSSessionBeginW(const wchar_t* params, int* errorCode);
typedef const wchar_t* (MSPAPI *Proc_QTTSSessionBeginW)(const wchar_t* params, int* errorCode);
#endif

/***********************
文本输出模块
成功返回0
对应的进程ID 文本内容长度		
**********************/
int MSPAPI QTTSTextPut(const char* sessionID, const char* textString, unsigned int textLen, const char* params);
typedef int (MSPAPI *Proc_QTTSTextPut)(const char* sessionID, const char* textString, unsigned int textLen, const char* params);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QTTSTextPutW(const wchar_t* sessionID, const wchar_t* textString, unsigned int textLen, const wchar_t* params);
typedef int (MSPAPI *Proc_QTTSTextPutW)(const wchar_t* sessionID, const wchar_t* textString, unsigned int textLen, const wchar_t* params);
#endif

/***********************************************
获取对应的音频文件
参数对应是进程ID 音频文件和大小 合成状态 错误代码
返回值就是合成的音频文件

***********************************************/
const void* MSPAPI QTTSAudioGet(const char* sessionID, unsigned int* audioLen, int* synthStatus, int* errorCode);
typedef const void* (MSPAPI *Proc_QTTSAudioGet)(const char* sessionID, unsigned int* audioLen, int* synthStatus, int* errorCode);
#ifdef MSP_WCHAR_SUPPORT
const void* MSPAPI QTTSAudioGetW(const wchar_t* sessionID, unsigned int* audioLen, int* synthStatus, int* errorCode);
typedef const void* (MSPAPI *Proc_QTTSAudioGetW)(const wchar_t* sessionID, unsigned int* audioLen, int* synthStatus, int* errorCode);
#endif

/*******************
获取具体的音频信息
进程ID	
*******************/
const char* MSPAPI QTTSAudioInfo(const char* sessionID);
typedef const char* (MSPAPI *Proc_QTTSAudioInfo)(const char* sessionID);
#ifdef MSP_WCHAR_SUPPORT
const wchar_t* MSPAPI QTTSAudioInfoW(const wchar_t* sessionID);
typedef const wchar_t* (MSPAPI *Proc_QTTSAudioInfoW)(const wchar_t* sessionID);
#endif

/************************
结束音频识别的进程	
************************/
int MSPAPI QTTSSessionEnd(const char* sessionID, const char* hints);
typedef int (MSPAPI *Proc_QTTSSessionEnd)(const char* sessionID, const char* hints);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QTTSSessionEndW(const wchar_t* sessionID, const wchar_t* hints);
typedef int (MSPAPI *Proc_QTTSSessionEndW)(const wchar_t* sessionID, const wchar_t* hints);
#endif

/************************************
 获取各种参数
 成功返回0
 包括进程ID 变量名字和值 文件的话要有长度
************************************/
int MSPAPI QTTSGetParam(const char* sessionID, const char* paramName, char* paramValue, unsigned int* valueLen);
typedef int (MSPAPI *Proc_QTTSGetParam)(const char* sessionID, const char* paramName, char* paramValue, unsigned int* valueLen);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QTTSGetParamW(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue, unsigned int* valueLen);
typedef int (MSPAPI *Proc_QTTSGetParamW)(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue, unsigned int* valueLen);
#endif

/************************************** 
 更改各种参数
 成功返回0
 包括进程ID 变量名字和值 文件的话要有长度	
**************************************/
int MSPAPI QTTSSetParam(const char *sessionID, const char *paramName, const char *paramValue);
typedef int (MSPAPI *Proc_QTTSSetParam)(const char* sessionID, const char* paramName, char* paramValue);

#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QTTSSetParamW(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue);
typedef int (MSPAPI *Proc_QTTSSetParamW)(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue);
#endif

typedef void ( *tts_result_ntf_handler)( const char *sessionID, const char *audio, int audioLen, int synthStatus, int ced, const char *audioInfo, int audioInfoLen, void *userData ); 
typedef void ( *tts_status_ntf_handler)( const char *sessionID, int type, int status, int param1, const void *param2, void *userData);
typedef void ( *tts_error_ntf_handler)(const char *sessionID, int errorCode,	const char *detail, void *userData);
int MSPAPI QTTSRegisterNotify(const char *sessionID, tts_result_ntf_handler rsltCb, tts_status_ntf_handler statusCb, tts_error_ntf_handler errCb, void *userData);

#ifdef __cplusplus
} /* extern "C" */
#endif /* C++ */

#endif /* __QTTS_H__ */