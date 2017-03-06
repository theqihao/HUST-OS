#ifndef MYFILE_H
#define MYFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// size
#define InodeNum 1024
#define BlockNum 1024 * 80
#define MaxPerInode 1024
// begin address
#define SuperBegin 0
#define InodeBegin sizeof(SuperBlock)
#define BlockBegin (InodeBegin + InodeNum * sizeof(Inode))


struct SuperBlock {
    bool inode_map[INODE_NUM];
    bool block_map[BLOCK_NUM];
    int inode_used;
    int block_used;
};

struct Inode {
    int block_num;
    int blocks[MAX_PER_INODE];
    int size;
    int type;
};

struct DIR {
    char name[64];
    int inode;
};

FILE *FS;

int init_fs(void);
int close_fs(void);
void Hello();


#endif
