#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <time.h>

typedef struct _CPU CPU;
struct _CPU {
	char name[20];		// 名字
	// 从系统启动开始累计到当前时刻
	unsigned int user;	// 处于用户态的运行时间，不包含 nice值为负进程。
	unsigned int nice;	// nice值为负的进程所占用的CPU时间
	unsigned int system;// 处于核心态的运行时间
	unsigned int idle;	// 除IO等待时间以外的其它等待时间
	unsigned int iowait;// IO等待时间
	unsigned int irq;	// 硬中断时间
	unsigned int softirq; // 软中断时间
};
// 得到当前时间
char* get_time(char* s);
// 得到当前CPU信息
CPU get_cpu();
// 计算CPU占用率
double cacl_cpu(CPU *cpu1, CPU *cpu2);

#endif