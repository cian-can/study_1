#ifndef APP_H
#define APP_H

//常用的库函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define ON_LINE_SIZE 20  //线上预约挂号数量
#define OFF_LINE_SIZE 40 //线下排队数量
#define ADMISSION_SIZE 20 //就诊科室数量
#define admission_number_per_day 20 //每天每个科室的预约数量

//定义结构体
typedef struct 
{
    int number;//取号顺序
    char *name;//患者名字
    char *admission;//就诊科室
    char *time;//推荐就诊时间
    int tag;//是否签到 签到 1 ，未签到 0
}on_line;//线上预约信息名片


typedef struct person
{
    int number;//取号顺序
    char *name;//患者名字
    char *admission;//就诊科室
    int sub;//是否需要复诊 0 不需要 1 需要
    int if_sub;//是否是复诊排队 0 不是 1 是
    struct person *next;//指向下一个节点的指针
}Person;//线下挂号信息名片

typedef struct admission
{
    char *name;//科室名字
    struct person *head;//存放每个患者信息的链表头指针
    struct person *tail;//存放每个患者信息的链表尾指针
    int count;//当前预约人数
    int call_number;//当前叫号顺序
}Admission;//就诊科室信息名片

//自定义函数初始化
void init_on_line_queue();//初始化线上预约挂号数组
void add_on_line(int number, char *name, char *admission, char *time);//添加线上预约挂号信息
void sign_in_on_line(int number,int sub);//签到线上预约挂号

void menu_printf_all();//打印开始选择界面
void menu_printf_on_line();//打印线上预约界面
void choice();//选择界面
int find_empty_on_line() ;//查看数组未编号位置

void print_all_admissions() ;//打印就诊科室
void init_admission_queue() ;//初始化就诊科室预约显示
int find_admission(char *admission) ;//查看有没有对应科室

// 全局变量声明（用extern）
extern on_line on_line_queue[ON_LINE_SIZE];//线上预约挂号数组
extern Person sign_up_queue[ON_LINE_SIZE];//签到排队队列
extern int sign_up_front, sign_up_rear;
extern Person  off_line_queue[OFF_LINE_SIZE];//线下排队队列
extern int off_line_front, off_line_rear;
extern Admission *admission_queue[ADMISSION_SIZE];//就诊科室预约显示
extern int admission_front[ADMISSION_SIZE];//就诊科室预约队头
extern int admission_rear[ADMISSION_SIZE];//就诊科室预约队尾

#endif //APP.H