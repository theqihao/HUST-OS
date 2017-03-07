#ifndef MYFILE_H
#define MYFILE_H

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
#define BlockSize 1024
#define MaxPerInode 1024
#define MaxPerDir (BlockSize / sizeof(Dir))
// begin address, segment
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
    char name[32];
    int inum;
};

FILE *fs;
SuperBlock sb;

// cur
Inode cur_inode;
int cur_inum;
char pwd[128];
int cur_fnum;
Dir cur_files[MaxPerDir];




// op
int init();
int init_root();
int mkfile(int pa_inum, char *name, int type);
int get_inum();
int init_dir(int pa_inum, int new_inum);
int init_file(int inum);
int show();



int open_dir(int inum);
char* get_namei();





void Hello();
#endif
