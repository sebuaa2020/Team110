#ifndef FORMATS_H_160601_TT
#define FPRMATS_H_160601_TT 1

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1

/***********************************
参考科大讯飞语音包
author: Zhang Cenyue

format.h
存储WAV格式的头部信息
***********************************/

typedef struct tWAVEFORMATEX {
    unsigned short wFormatTag;
    unsigned short nChannels;
    unsigned int   nSamplesPerSec;
    unsigned int   nAvgBytesPerSec;
    unsigned short nBlockAlign;
    unsigned short wBitsPerSample;
    unsigned short cbsize;

} WAVEFORMATEX;
#endif
#endif
