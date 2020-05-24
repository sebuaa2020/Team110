/*********************************************
录制音频的模块

基本上和winrec.h一致

主要步骤如下
建立录音机
开启录音机
开始录音
停止录音
关闭录音机
销毁录音机
*********************************************/
#ifndef __IFLY_WINREC_H__
#define __IFLY_WINREC_H__

#include "formats.h"

//错误信息
enum {
	RECORD_ERR_BASE = 0,
	RECORD_ERR_GENERAL,
	RECORD_ERR_MEMFAIL,
	RECORD_ERR_INVAL,
	RECORD_ERR_NOT_READY
};

typedef struct record_dev_id {
    union U {
        char * name;
        int index;
        void * resv;
    }u;
}record_dev_id;

#ifdef __cplusplus

extern "C" {

#endif

//c/c++风格不同

typedef struct recorder {
    void (*on_data_ind)(char *data, unsigned long len, void *user_para);
	void * user_cb_para;
	volatile int state;	 //录音状态

	void * wavein_hdl;、
	/* thread id 很有可能是个struct 这个时候不传入 */

	pthread_t rec_thread; 

	/*void * rec_thread_hdl;*/

	void * bufheader;//读入缓存头部
	unsigned int bufcount; 

	//音频相关缓存等信息
	char *audiobuf;
	int bits_per_frame;
	unsigned int buffer_time;
	unsigned int period_time;

	size_t period_frames;
	size_t buffer_frames;
} recorder;

//创建录音机
int create_recorder(recorder ** out_rec, 
				void (*on_data_ind)(char *data, unsigned long len, void *user_para), 
				void* user_cb_para);

//销毁录音机
void destroy_recorder(recorder ** rec);

//打开录音机
int open_recorder(recorder *rec, record_dev_id dev,
                WAVEFORMATEX * fmt);

//关闭录音机
void close_recorder(recorder * rec);

//开始录音
int start_record(recorder * rec);

//结束录音
int stop_record(recorder * rec);

int is_record_stopped(recorder * rec);

#ifdef __cplusplus

}
#endif

#endif