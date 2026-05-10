#ifndef APP_H
#define APP_H

#define ON_LINE_SIZE 20  //线上预约挂号数量
#define OFF_LINE_SIZE 40 //线下排队数量

typedef struct 
{
    int number;//取号顺序
    char *name;//患者名字
    char *admission;//就诊科室
    char *time;//推荐就诊时间
    int tag;//是否签到 签到 1 ，未签到 0
}on_line;//线上预约信息名片

on_line on_line_queue[ON_LINE_SIZE];//线上预约挂号数组

typedef struct person
{
    int number;//取号顺序
    char *name;//患者名字
    char *admission;//就诊科室
    int sub;//是否需要复诊 0 不需要 1 需要
    int if_sub;//是否是复诊排队 0 不是 1 是
    struct person *next;//指向下一个节点的指针
}Person;//线下挂号信息名片



#endif //APP.H