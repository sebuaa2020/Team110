/********************************
 qisr.h
科大讯飞的识别语音头文件
不得不说其参考意义确实很大
********************************/

#ifndef __QISR_H__
#define __QISR_H__

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

#include "msp_types.h"

/*******************************
开启语音识别进程的函数
返回值为进程ID NULL意味着创建失败
存储的单词表 只调用一次...
对应参数
返回错误值
*******************************/
const char* MSPAPI QISRSessionBegin(const char* grammarList, const char* params, int* errorCode);
typedef const char* (MSPAPI *Proc_QISRSessionBegin)(const char* grammarList, const char* params, int *result);
#ifdef MSP_WCHAR_SUPPORT
const wchar_t* MSPAPI QISRSessionBeginW(const wchar_t* grammarList, const wchar_t* params, int *result);
typedef const wchar_t* (MSPAPI *Proc_QISRSessionBeginW)(const wchar_t* grammarList, const wchar_t* params, int *result);
#endif


/************************************************
自动写入音频的模块
采用二进制文件读写
成功返回0
const char* sessionID	进程ID
const void* waveData	二进制的.wav格式
unsigned int waveLen	二进制长度
int audioStatus			音频状态
int *epStatus			更改的状态
int *recogStatus		语音识别的状态
***********************************************/
int MSPAPI QISRAudioWrite(const char* sessionID, const void* waveData, unsigned int waveLen, int audioStatus, int *epStatus, int *recogStatus);
typedef int (MSPAPI *Proc_QISRAudioWrite)(const char* sessionID, const void* waveData, unsigned int waveLen, int audioStatus, int *epStatus, int *recogStatus);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRAudioWriteW(const wchar_t* sessionID, const void* waveData, unsigned int waveLen, int audioStatus, int *epStatus, int *recogStatus);
typedef int (MSPAPI *Proc_QISRAudioWriteW)(const wchar_t* sessionID, const void* waveData, unsigned int waveLen, int audioStatus, int *epStatus, int *recogStatus);
#endif

/*********************************************
获取识别结果
类似前面的借口
rsltStatus是识别的状态
*********************************************/
const char * MSPAPI QISRGetResult(const char* sessionID, int* rsltStatus, int waitTime, int *errorCode);
typedef const char * (MSPAPI *Proc_QISRGetResult)(const char* sessionID, int* rsltStatus, int waitTime, int *errorCode);
#ifdef MSP_WCHAR_SUPPORT
const wchar_t* MSPAPI QISRGetResultW(const wchar_t* sessionID, int* rsltStatus, int waitTime, int *errorCode);
typedef const wchar_t* (MSPAPI *Proc_QISRGetResultW)(const wchar_t* sessionID, int* rsltStatus, int waitTime, int *errorCode);
#endif

/**************
二进制识别结果	
**************/
const char * MSPAPI QISRGetBinaryResult(const char* sessionID, unsigned int* rsltLen,int* rsltStatus, int waitTime, int *errorCode);
typedef const char * (MSPAPI *Proc_QISRGetBinaryResult)(const char* sessionID, unsigned int* rsltLen, int* rsltStatus, int waitTime, int *errorCode);
#ifdef MSP_WCHAR_SUPPORT
const wchar_t* MSPAPI QISRGetBinaryResultW(const wchar_t* sessionID, unsigned int* rsltLen, int* rsltStatus, int waitTime, int *errorCode);
typedef const wchar_t* (MSPAPI *Proc_QISRGetBinaryResultW)(const wchar_t* sessionID, unsigned int* rsltLen, int* rsltStatus, int waitTime, int *errorCode);
#endif


/*******************************************
结束识别进程
释放之前读取的文件资源
成功返回0
后面的参数为对应的进程id和提示标志
******************************************/
int MSPAPI QISRSessionEnd(const char* sessionID, const char* hints);
typedef int (MSPAPI *Proc_QISRSessionEnd)(const char* sessionID, const char* hints);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRSessionEndW(const wchar_t* sessionID, const wchar_t* hints);
typedef int (MSPAPI *Proc_QISRSessionEndW)(const wchar_t* sessionID, const wchar_t* hints);
#endif

/********************************
获取进程进行中的各种参数...	
********************************/
int MSPAPI QISRGetParam(const char* sessionID, const char* paramName, char* paramValue, unsigned int* valueLen);
typedef int (MSPAPI *Proc_QISRGetParam)(const char* sessionID, const char* paramName, char* paramValue, unsigned int* valueLen);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRGetParamW(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue, unsigned int* valueLen);
typedef int (MSPAPI *Proc_QISRGetParamW)(const wchar_t* sessionID, const wchar_t* paramName, wchar_t* paramValue, unsigned int* valueLen);
#endif

/************
设置参数	
************/
int MSPAPI QISRSetParam(const char* sessionID, const char* paramName, const char* paramValue);
typedef int (MSPAPI *Proc_QISRSetParam)(const char* sessionID, const char* paramName, const char* paramValue);
#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRSetParamW(const wchar_t* sessionID, const wchar_t* paramName, const wchar_t* paramValue);
typedef int (MSPAPI *Proc_QISRSetParamW)(const wchar_t* sessionID, const wchar_t* paramName, const wchar_t* paramValue);
#endif


typedef void ( *recog_result_ntf_handler)( const char *sessionID, const char *result, int resultLen, int resultStatus, void *userData ); 
typedef void ( *recog_status_ntf_handler)( const char *sessionID, int type, int status, int param1, const void *param2, void *userData);
typedef void ( *recog_error_ntf_handler)(const char *sessionID, int errorCode,	const char *detail, void *userData);
int MSPAPI QISRRegisterNotify(const char *sessionID, recog_result_ntf_handler rsltCb, recog_status_ntf_handler statusCb, recog_error_ntf_handler errCb, void *userData);

typedef int ( *UserCallBack)( int, const char*, void*);
typedef int ( *GrammarCallBack)( int, const char*, void*);
typedef int ( *LexiconCallBack)( int, const char*, void*);

int MSPAPI QISRBuildGrammar(const char *grammarType, const char *grammarContent, unsigned int grammarLength, const char *params, GrammarCallBack callback, void *userData);
typedef int (MSPAPI *Proc_QISRBuildGrammar)(const char *grammarType, const char *grammarContent, unsigned int grammarLength, const char *params, GrammarCallBack callback, void *userData);

#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRBuildGrammarW(const wchar_t *grmmarType, const wchar_t *grammarContent, unsigned int grammarLength, const wchar_t *params, GrammarCallBack callback, void *userData);
typedef int (MSPAPI *Proc_QISRBuildGrammarW)(const wchar_t *grmmarType, const wchar_t *grammarContent, unsigned int grammarLength, const wchar_t *params, GrammarCallBack callback, void *userData);
#endif

int MSPAPI QISRUpdateLexicon(const char *lexiconName, const char *lexiconContent, unsigned int lexiconLength, const char *params, LexiconCallBack callback, void *userData);
typedef int (MSPAPI *Proc_QISRUpdataLexicon)(const char *lexiconName, const char *lexiconContent, unsigned int lexiconLength, const char *params, LexiconCallBack callback, void *userData);

#ifdef MSP_WCHAR_SUPPORT
int MSPAPI QISRUpdateLexiconW(const wchar_t *lexiconName, const wchar_t *lexiconContent, unsigned int lexiconLength, const wchar_t *params, LexiconCallBack callback, void *userData);
typedef int (MSPAPI Proc_QISRUpdateLexiconW)(const wchar_t *lexiconName, const wchar_t *lexiconContent, unsigned int lexiconLength, const wchar_t *params, LexiconCallBack callback, void *userData);
#endif


#ifdef __cplusplus
} /* extern "C" */	
#endif /* C++ */

#endif /* __QISR_H__ */

