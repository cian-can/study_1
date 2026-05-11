#include "app.h"

on_line on_line_queue[ON_LINE_SIZE];//线上预约挂号数组

Person sign_up_queue[ON_LINE_SIZE];//签到排队队列
int sign_up_front = 0;//签到排队队头
int sign_up_rear = 0;//签到排队队尾

//初始化线上预约挂号数组
void init_on_line_queue() {
    for (int i = 0; i < ON_LINE_SIZE; i++) {
        on_line_queue[i].number = 0;
        on_line_queue[i].name = NULL;
        on_line_queue[i].admission = NULL;
        on_line_queue[i].time = NULL;
        on_line_queue[i].tag = 0;
    }
}

//添加线上预约挂号信息
void add_on_line(int number, char *name, char *admission, char *time) {
    for (int i = 0; i < ON_LINE_SIZE; i++) {
        if (on_line_queue[i].number == 0) { //找到第一个空位
            on_line_queue[i].number = number;
            on_line_queue[i].name = strdup(name);
            on_line_queue[i].admission = strdup(admission);
            on_line_queue[i].time = strdup(time);
            on_line_queue[i].tag = 0; //默认未签到
            break;
        }
    }
}

//查看数组未编号位置
int find_empty_on_line() {
    for (int i = 0; i < ON_LINE_SIZE; i++) {
        if (on_line_queue[i].number == 0) {
            return i; //返回第一个空位的索引
        }
    }
    return -1; //没有空位
}
//签到线上预约挂号
void sign_in_on_line(int number,int sub) {
    for (int i = 0; i < ON_LINE_SIZE; i++) {
        if (on_line_queue[i].number == number) {
            on_line_queue[i].tag = 1; //签到成功
            //将签到的患者信息加入签到排队队列
            sign_up_queue[sign_up_rear].number = on_line_queue[i].number;
            sign_up_queue[sign_up_rear].name = strdup(on_line_queue[i].name);
            sign_up_queue[sign_up_rear].admission = strdup(on_line_queue[i].admission);
            sign_up_queue[sign_up_rear].sub = sub; //设置是否需要复诊
            sign_up_queue[sign_up_rear].if_sub = 0; //默认不是复诊排队
            sign_up_queue[sign_up_rear].next = NULL;
            sign_up_rear = (sign_up_rear + 1) % ON_LINE_SIZE; //循环队列
            break;
        }
    }
}