#ifndef HEAD
#define HEAD

#include <string.h>
#include <malloc.h>

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

    PROCESSINFO() {

        pid = 0;
        ppid = 0;
        cpu = 100;
        mem = 100;
        pri = 400;
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


#endif // HEAD

