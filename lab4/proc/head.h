#ifndef HEAD
#define HEAD

typedef struct PROCESSINFO PRO;
struct PROCESSINFO {
    char name[32];
    char user[32];
    int id;
    int pid;
    double cpu;
    double mem;
    int pri;

    bool operator == (const PRO &b) const {


    }
};

#endif // HEAD

