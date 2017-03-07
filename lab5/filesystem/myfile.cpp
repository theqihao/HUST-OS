#include "myfile.h"

FILE *fs;
SuperBlock sb;

// cur
Inode cur_inode;
int cur_inum;
char pwd[128];
vector<Dir> cur_dirs;


int init(void) {
    //  init filesystem
    fs = fopen("fs", "r+");
  //  fseek(fs, BlockSeg, SEEK_SET);
    // init sperblock
  //  sb = (SuperBlock *)malloc(sizeof(SuperBlock));
  //  memset(sb, 0, sizeof(SuperBlock));
    // root dir

    cur_inum = 0;
    if (open_dir(cur_inum) == -1) {
        init_root();
    }
    return 0;
}

int init_root() {
    // init superBlock
    memset(sb.inode_map, 0, sizeof(sb.inode_map));
    memset(sb.block_map, 0, sizeof(sb.block_map));
    sb.inode_map[0] = true;
    sb.inode_used = 1;
    sb.block_map[0] = true;
    sb.block_used = 1;

    cur_inode.size = sizeof(Dir);
    cur_inode.block_num = 1;
    cur_inode.blocks[0] = 0;
    cur_inode.type = 1;
    strcpy(pwd, "/");
    strcpy(cur_inode.name, pwd);
    Dir dir;
    dir.inode = 0;
    strcpy(dir.name, ".");
    cur_dirs.push_back(dir);
    return 0;
}

int open_dir(int inum) {
    // read
    fseek(fs, InodeSeg + (inum  * sizeof(Inode)), SEEK_SET);
    fread(&cur_inode, sizeof(Inode), 1, fs);




    // cur_inode.type = 1;
    // strcpy(cur_inode.name, pwd);
    if (cur_inode.blocks == 0) {
        return -1;
    }

}

char* get_namei(int inum) {
    /*Inode inode;
    FILE *fp = fopen("fs", "r");
    fseek(fs, InodeSeg + (inum * sizeof(Inode)), 0);
    fread(&inode, sizeof(Inode), 1, fp);
    fclose(fp);
    return inode.name;
    */
}


void Hello() {
    cout << "hello " << endl;
}
