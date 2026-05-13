//测试函数
#include "app.h"

//测试添加线上预约挂号信息
void test_add_on_line() {
    for(int i = 0; i < ON_LINE_SIZE; i++) {
        char name[50];
        sprintf(name, "患者%d", i + 1);

        // 分配内存！！！这是你最缺的一步
        on_line_queue[i].name = malloc(strlen(name) + 1);
        on_line_queue[i].admission = malloc(strlen("a1") + 1);
        on_line_queue[i].time = malloc(strlen("2024-06-01 10:00") + 1);

        // 复制字符串
        strcpy(on_line_queue[i].name, name);
        strcpy(on_line_queue[i].admission, "a1");
        strcpy(on_line_queue[i].time, "2024-06-01 10:00");

        on_line_queue[i].number = i + 1;
        on_line_queue[i].tag = 0;
    }
}
//测试签到线上预约挂号
void test_sign_in_on_line() {
    for(int i = 0; i < ON_LINE_SIZE - 1; i++) {
        // 先把线上的内容复制到签到队列
        sign_up_queue[sign_up_rear].number = on_line_queue[i].number;

        // 分配内存！！！
        sign_up_queue[sign_up_rear].name = malloc(strlen(on_line_queue[i].name) + 1);
        sign_up_queue[sign_up_rear].admission = malloc(strlen(on_line_queue[i].admission) + 1);

        // 复制
        strcpy(sign_up_queue[sign_up_rear].name, on_line_queue[i].name);
        strcpy(sign_up_queue[sign_up_rear].admission, on_line_queue[i].admission);

        sign_up_queue[sign_up_rear].sub = 0;

        // 队尾移动
        sign_up_rear = (sign_up_rear + 1) % ON_LINE_SIZE;
    }
}

//打印签到队列
void print_sign_up_queue() {
    printf("=============签到队列：\n");
    int i = sign_up_front;

        // 空队列判断
    if(i == sign_up_rear) {
        printf("当前无已签到患者\n");
        return;
    }
    while(i != sign_up_rear) {
        if (sign_up_queue[i].number != 0) {
            printf("取号顺序：%d\t姓名：%s\t科室：%s\t是否需要复诊：%d\n",
                   sign_up_queue[i].number, sign_up_queue[i].name, sign_up_queue[i].admission, sign_up_queue[i].sub);
        }
        i = (i + 1) % ON_LINE_SIZE;
    }
}