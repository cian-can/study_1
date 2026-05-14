// 线下排队
#include "app.h"

Person off_line_queue[OFF_LINE_SIZE];//线下排队队列
int off_line_front = 0;//线下排队队头
int off_line_rear = 0;//线下排队队尾

Person all_off_line_queue[OFF_LINE_SIZE];//线下排队和签到合并后的队列
int all_off_line_front = 0;//合并后队头
int all_off_line_rear = 0;//合并后队尾

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

//初始化合并队列
void init_all_off_line_queue() {
    for (int i = 0; i < OFF_LINE_SIZE; i++) {
        all_off_line_queue[i].number = 0;
        all_off_line_queue[i].name = NULL;
        all_off_line_queue[i].admission = NULL;
        all_off_line_queue[i].sub = 0;
        all_off_line_queue[i].if_sub = 0;
        all_off_line_queue[i].next = NULL;
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

//线下排队和签到队列合并
void merge_queues() {

    //合并前先清空合并队列
    all_off_line_front = 0;
    all_off_line_rear = 0;

        // 安全合并（不破坏原队列）
    int temp_off = off_line_front;
    int temp_sign = sign_up_front;
    while(1)
    {
         if (temp_off != off_line_rear) {
            all_off_line_queue[all_off_line_rear] = off_line_queue[temp_off];
            all_off_line_queue[all_off_line_rear].name = strdup(off_line_queue[temp_off].name);
            all_off_line_queue[all_off_line_rear].admission = strdup(off_line_queue[temp_off].admission);
            all_off_line_rear++;
            temp_off = (temp_off + 1) % OFF_LINE_SIZE;
        }
        else if (temp_sign != sign_up_rear) {
            all_off_line_queue[all_off_line_rear].number = sign_up_queue[temp_sign].number;
            all_off_line_queue[all_off_line_rear].name = strdup(sign_up_queue[temp_sign].name);
            all_off_line_queue[all_off_line_rear].admission = strdup(sign_up_queue[temp_sign].admission);
            all_off_line_queue[all_off_line_rear].sub = sign_up_queue[temp_sign].sub;
            all_off_line_rear++;
            temp_sign = (temp_sign + 1) % ON_LINE_SIZE;
        }
        else break;
    }
       // 排序（用临时数组适配1-based堆排序）
    int len = all_off_line_rear;
    if (len <= 0) return;

    Person temp[OFF_LINE_SIZE];
    for (int i = 0; i < len; i++) {
        temp[i + 1] = all_off_line_queue[i];
    }

    heap_sort_sign_up_queue(temp, len);

    for (int i = 0; i < len; i++) {
        all_off_line_queue[i] = temp[i + 1];
    }
}