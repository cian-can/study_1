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

    while(1)
    {
        if(off_line_front != off_line_rear) //线下排队队列不为空
        {
            all_off_line_queue[all_off_line_rear] = off_line_queue[off_line_front];
            all_off_line_rear = (all_off_line_rear + 1) % OFF_LINE_SIZE;
            off_line_front = (off_line_front + 1) % OFF_LINE_SIZE;
        }
        else if(sign_up_front != sign_up_rear) //签到队列不为空
        {
            all_off_line_queue[all_off_line_rear].number = sign_up_queue[sign_up_front].number;
            all_off_line_queue[all_off_line_rear].name = strdup(sign_up_queue[sign_up_front].name);
            all_off_line_queue[all_off_line_rear].admission = strdup(sign_up_queue[sign_up_front].admission);
            all_off_line_queue[all_off_line_rear].sub = sign_up_queue[sign_up_front].sub;
            all_off_line_queue[all_off_line_rear].if_sub = sign_up_queue[sign_up_front].if_sub;
            all_off_line_queue[all_off_line_rear].next = NULL;
            all_off_line_rear = (all_off_line_rear + 1) % OFF_LINE_SIZE;
            sign_up_front = (sign_up_front + 1) % ON_LINE_SIZE;
        }
        else
        {
            break; //两个队列都为空，合并完成
        }
    }
}