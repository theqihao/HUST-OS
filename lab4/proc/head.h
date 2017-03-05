#ifndef HEAD
#define HEAD

#include <string.h>
#include <malloc.h>

// PROCESS
typedef struct PROCESSINFO PRO;
struct PROCESSINFO {
    char name[32];
    char user[32];
    char state[32];
    int pid;
    int ppid;

    double cpu;
    int mem;
    int pri;
    bool vaild;

    PROCESSINFO() {

        pid = 0;
        ppid = 0;
        cpu = 100;
        mem = 100;
        pri = 400;
        vaild = false;
    }

    bool operator == (const PRO &b) const {
        if (strcmp(name, b.name) == 0 && \
            strcmp(user, b.user) == 0 && \
            strcmp(state, b.state) == 0 && \
            pid == b.pid && ppid == b.ppid && \
            cpu == b.cpu && mem == b.mem && \
            pri == b.pri)
        {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (const PRO &b) const {
        if (cpu != b.cpu) {
            return cpu < b.cpu;
        } else {
            return pid < b.pid;
        }
    }
};

// CPU
typedef struct _CPU CPU;
struct _CPU {
    char name[10];		// name
    // begin computer to now
    unsigned int user;	// user status time
    // nice值为负的进程所占用的CPU时间, 优先级最高，多分配的
    unsigned int nice;	// nice 改变过优先级的进程的占用CPU的百分比
    unsigned int system;// system status time
    unsigned int idle;	// wait time expect IO
    unsigned int iowait;// wait IO
    unsigned int irq;	// handware interupt
    unsigned int softirq; // soft interupt
};




// MEM
typedef struct _MEM MEM;
struct _MEM {
    unsigned int total;
    unsigned int free;  // unused
    unsigned int buffer;	// 用来给文件做缓冲大小
    unsigned int cached;    // 被高速缓冲存储器（cache memory）用的内存的大小
};
#endif // HEAD

