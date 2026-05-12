// 线下排队
#include "app.h"

Person off_line_queue[OFF_LINE_SIZE];//线下排队队列
int off_line_front = 0;//线下排队队头
int off_line_rear = 0;//线下排队队尾

//初始化线下排队队列
void init_off_line_queue() {
    for (int i = 0; i < OFF_LINE_SIZE; i++) {
        off_line_queue[i].number = 0;
        off_line_queue[i].name = NULL;
        off_line_queue[i].admission = NULL;
        off_line_queue[i].sub = 0;
        off_line_queue[i].if_sub = 0;
        off_line_queue[i].next = NULL;
    }
}

//线下排队挂号
void add_off_line(int number, char *name, char *admission, int sub) {

    off_line_queue[off_line_rear].number = number;
    off_line_queue[off_line_rear].name = strdup(name);
    off_line_queue[off_line_rear].admission = strdup(admission);
    off_line_queue[off_line_rear].sub = sub; //设置是否需要复诊
    off_line_queue[off_line_rear].if_sub = 0; //默认不是复诊排队
    off_line_queue[off_line_rear].next = NULL;
    off_line_rear = (off_line_rear + 1) % OFF_LINE_SIZE; //循环队列
}