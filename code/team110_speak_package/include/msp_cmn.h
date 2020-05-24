/*******************************************************

msp_cmn.h
即移动端的语音交互
包括诸多的函数借口
 


 ******************************************************/


#ifndef __MSP_CMN_H__
#define __MSP_CMN_H__


#include "msp_types.h"

#ifdef __cplusplus

extern "C" {

#endif /* C++ */

//#ifdef MSP_WCHAR_SUPPORT

/************************************** 

返回 int MSPAPI 检测这个东西是否成功 成功返回0

const wchar_t* wcstr 	源路径

char* mbstr				目标路径

int len					最大容量
**************************************/

char *Wchar2Mbytes(const wchar_t* wcstr);


/*************************
用户登录
其余参数同上
************************/

wchar_t *Mbytes2Wchar(const char *mbstr);

//#endif /*MSP_WCHAR_SUPPORT*/



/********************************

MSP登录模块
参数同上	

*******************************/

int MSPAPI MSPLogin(const char* usr, const char* pwd, const char* params);

typedef int (MSPAPI *Proc_MSPLogin)(const char* usr, const char* pwd, const char* params);

//#ifdef MSP_WCHAR_SUPPORT

int MSPAPI MSPLoginW(const wchar_t* usr, const wchar_t* pwd, const wchar_t* params);

typedef int (MSPAPI *Proc_MSPLoginW)(const wchar_t* usr, const wchar_t* pwd, const wchar_t* params);

//#endif/*MSP_WCHAR_SUPPORT*/

/******************************
 退出登录模块	
******************************/

int MSPAPI MSPLogout();

typedef int (MSPAPI *Proc_MSPLogout)();

//#ifdef MSP_WCHAR_SUPPORT

int MSPAPI MSPLogoutW();

typedef int (MSPAPI *Proc_MSPLogoutW)();

//#endif/*MSP_WCHAR_SUPPORT*/

/*********************************
上传模块

返回值 int MSPAPI 成功返回0

上传数据名称	
*********************************/

int MSPAPI MSPUpload( const char* dataName, const char* params, const char* dataID);

typedef int (MSPAPI* Proc_MSPUpload)( const char* dataName, const char* params, const char* dataID);



/********************************
下载模块

返回值 int MSPAPI 成功返回0

下载数据名称		

*******************************/

typedef int (*DownloadStatusCB)(int errorCode, long param1, const void *param2, void *userData);

typedef int (*DownloadResultCB)(const void *data, long dataLen, void *userData);

int MSPAPI MSPDownload(const char* dataName, const char* params, DownloadStatusCB statusCb, DownloadResultCB resultCb, void*userData);

typedef int (MSPAPI* Proc_MSPDownload)(const char* dataName, const char* params, DownloadStatusCB statusCb, DownloadResultCB resultCb, void*userData);

int MSPAPI MSPDownloadW(const wchar_t* wdataName, const wchar_t* wparams, DownloadStatusCB statusCb, DownloadResultCB resultCb, void*userData);

typedef int (MSPAPI* Proc_MSPDownloadW) (const wchar_t* wdataName, const wchar_t* wparams, DownloadStatusCB statusCb, DownloadResultCB resultCb, void*userData);

/*************************************** 

MSP 获得数据
成功返回0
void*data 为文件的指针
dataLen 文件长度
dataStatus 文件属性

**************************************/

int MSPAPI MSPAppendData(void* data, unsigned int dataLen, unsigned int dataStatus);

typedef int (MSPAPI* Proc_MSPAppendData)(void* data, unsigned int dataLen, unsigned int dataStatus);



/******************************

获得结果

返回值为上传或者下载的结果

以及目标文件对应的长度和状态

是否出现错误标记

******************************/

const char* MSPAPI MSPGetResult(unsigned int* rsltLen, int* rsltStatus, int *errorCode);

typedef const char * (MSPAPI *Proc_MSPGetResult)(unsigned int* rsltLen, int* rsltStatus, int *errorCode);



/*********************************** 
设置对应的参数变量	
***********************************/

int MSPAPI MSPSetParam( const char* paramName, const char* paramValue );

typedef int (MSPAPI *Proc_MSPSetParam)(const char* paramName, const char* paramValue);

/*****************************
获取对应的参数变量	
类似前面
*****************************/

int MSPAPI MSPGetParam( const char *paramName, char *paramValue, unsigned int *valueLen );

typedef int (MSPAPI *Proc_MSPGetParam)( const char *paramName, char *paramValue, unsigned int *valueLen );



/******************************

上传数据

对应的服务器名称
文件名称
文件长度
相关参数
错误代码

****************************/

const char* MSPAPI MSPUploadData(const char* dataName, void* data, unsigned int dataLen, const char* params, int* errorCode);

typedef const char* (MSPAPI* Proc_MSPUploadData)(const char* dataName, void* data, unsigned int dataLen, const char* params, int* errorCode);



/*******************************
下载数据
和前面是一样的
*******************************/

const void* MSPAPI MSPDownloadData(const char* params, unsigned int* dataLen, int* errorCode);

typedef const void* (MSPAPI* Proc_MSPDownloadData)(const char* params, unsigned int* dataLen, int* errorCode);

//#ifdef MSP_WCHAR_SUPPORT

const void* MSPAPI MSPDownloadDataW(const wchar_t* params, unsigned int* dataLen, int* errorCode);

typedef const void* (MSPAPI* Proc_MSPDownloadDataW)(const wchar_t* params, unsigned int* dataLen, int* errorCode);

//#endif/*MSP_WCHAR_SUPPORT*/

/***************************
搜索对应结果
**************************/

const char* MSPAPI MSPSearch(const char* params, const char* text, unsigned int* dataLen, int* errorCode);

typedef const char* (MSPAPI* Proc_MSPSearch)(const char* params, const char* text, unsigned int* dataLen, int* errorCode);

typedef int (*NLPSearchCB)(const char *sessionID, int errorCode, int status, const void* result, long rsltLen, void *userData);

const char* MSPAPI MSPNlpSearch(const char* params, const char* text, unsigned int textLen, int *errorCode, NLPSearchCB callback, void *userData);

typedef const char* (MSPAPI* Proc_MSPNlpSearch)(const char* params, const char* text, unsigned int textLen, int *errorCode, NLPSearchCB callback, void *userData);

int MSPAPI MSPNlpSchCancel(const char *sessionID, const char *hints);



/******************************
注册模块
用户数据
*****************************/

typedef void ( *msp_status_ntf_handler)( int type, int status, int param1, const void *param2, void *userData );

int MSPAPI MSPRegisterNotify( msp_status_ntf_handler statusCb, void *userData );

typedef const char* (MSPAPI* Proc_MSPRegisterNotify)( msp_status_ntf_handler statusCb, void *userData );



/**
获取当前的版本号
 */

const char* MSPAPI MSPGetVersion(const char *verName, int *errorCode);

typedef const char* (MSPAPI * Proc_MSPGetVersion)(const char *verName, int *errorCode);

#ifdef __cplusplus

} /* extern "C" */	

#endif /* C++ */

#endif /* __MSP_CMN_H__ */