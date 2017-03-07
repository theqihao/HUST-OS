#include "myfile.h"
#define CMD_NUM 3

char* cmds[10] = {"ls", "touch", "mkdir"};
char arg[32];
char cmd[32];
int op = 1;

int main() {
    Hello();
    init();
    while (1) {
        op = 100;
        printf("\n%s$", pwd);
        scanf("%s", cmd);
        strcpy(arg, "unname");
        if (strcmp(cmd, "touch") == 0 || strcmp(cmd, "mkdir") == 0) {
            scanf("%s", arg);
        }
        for (int i = 0; i < CMD_NUM; i++) {
            if (strcmp(cmds[i], cmd) == 0) {
                op = i;
                break;
            }
        }
        switch (op) {
        case 0:
            printf("ls\n");

            break;
        case 1:
            printf("touch %s\n", arg);
            break;
        case 2:
            printf("mkdir\n");
            break;
        default:
            printf("no this cmd\n");
            break;
        }
    }
}


int init() {
    //  init filesystem
    fs = fopen("fs", "r+");
  //  fseek(fs, BlockSeg, SEEK_SET);
    // init sperblock
  //  sb = (SuperBlock *)malloc(sizeof(SuperBlock));
  //  memset(sb, 0, sizeof(SuperBlock));
    // root dir
//strcpy(pwd, "\/");
    //pwd = "/ds";
    strcpy(pwd, "/");
    cur_inum = 0;
    /*
    if (open_dir(cur_inum) == -1) {
        init_root();
    }
    */
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
    cur_inode.type = _DIR;
    strcpy(pwd, "/");
    Dir dir;
    dir.inum = 0;
    strcpy(dir.name, ".");
    cur_files[cur_fnum++] = dir;
    return 0;
}

// inum : parent's inum
int mkfile(int pa_inum, char *name, int type) {
    int new_inum = get_inum();
    if (type == _DIR) {
        init_dir(pa_inum, new_inum);
    } else {
        init_file(new_inum);
    }
    Dir dir;
    strcpy(dir.name, name);
    dir.inum = new_inum;
    cur_files[cur_fnum++] = dir;
}

int init_dir(int pa_inum, int new_inum) {

}

int init_file(int inum) {
    Inode inode;
    memset(inode.blocks, 0, sizeof(inode.blocks));
    inode.block_num = 0;
    inode.size = 0;
    inode.type = _FILE;
    fseek(fs, InodeSeg + (sizeof(Inode) * inum), SEEK_SET);
    fwrite(&inode, sizeof(Inode), 1, fs);
    return 0;
}

int show() {
    for (int i = 0; i < cur_fnum; i++) {

    }
}


int get_inum() {
    // check if used up
    if (sb.inode_used >= InodeNum) {
        printf("inode is used up\n");
        return -1;
    }
    // get an inode num
    for (int i = 0; i < InodeNum; i++) {
        if (sb.inode_map[i] == false) {
            sb.inode_map[i] == true;
            sb.inode_used++;
            return i;
        }
    }
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





/*
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
*/
