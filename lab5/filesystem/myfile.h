#ifndef __MYFILE_H_
#define __MYFILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <vector>
#include <iostream>

using namespace std;

// size
#define InodeNum 1024
#define BlockNum 1024 * 80
#define MaxPerInode 1024
// begin address
#define SuperSeg 0
#define InodeSeg sizeof(SuperBlock)
#define BlockSeg (InodeSeg + InodeNum * sizeof(Inode))
// 1: mkdir
// 0: touch
#define _DIR 1
#define _FILE 0

// struct
typedef struct _SuperBlock SuperBlock;
typedef struct _Inode Inode;
typedef struct _Dir Dir;

struct _SuperBlock {
    bool inode_map[InodeNum];
    bool block_map[BlockNum];
    int inode_used;
    int block_used;
};

struct _Inode {
    int block_num;
    int blocks[MaxPerInode];
    int size;
    int type;
};

struct _Dir {
    char name[64];
    int inum;
};



// op
int init(void);
int init_root();
int mkfile(int pa_inum, char *name, int type);
int get_inum();
int init_dir(int pa_inum, int new_inum);
int init_file(int inum);



int ls();




int open_dir(int inum);
char* get_namei();


void Hello();



#endif
