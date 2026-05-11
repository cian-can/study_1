#include "app.h"
//打印开始选择界面
void menu_printf_all(){
    printf("欢迎使用医院挂号系统！\n");
    printf("1. 线上预约挂号\n");
    printf("2. 线下排队挂号\n");
    printf("3. 签到\n");
    printf("4. 退出系统\n");
}

//打印线上预约界面
void menu_printf_on_line(){
    printf("线上预约挂号\n");
    printf("请输入患者姓名：");
    char name[50];
    scanf("%s", name);
    printf("请输入就诊科室：");
    char admission[50];
    scanf("%s", admission);
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    int number = 0;
    printf("当前时间：%d年%d月%d日 %d点%d分\n", tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min);
    if(find_empty_on_line() == -1) 
    {
        printf("预约已满\n"); return;
    }
    else
    {
        number = find_empty_on_line(); //获取上一个预约的取号顺序
    }
    
    char aim_time[100];
    printf("推荐就诊时间为：");
    int minute = 00;
    if(number % 2 != 0)
    {
        minute = 30;
    }
    else
    {
        minute = 00;
    }
    if(number <10) {
        sprintf(aim_time, "%d年%d月%d日上午%d点%d分",tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday + 1,  8 + number / 2,minute);
        printf("%s \n",aim_time);
    }
else if(number >10 ){
    sprintf(aim_time, "%d年%d月%d日下午%d点%d分",tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday + 1, 14 + number / 2, minute);
        printf("%s\n", aim_time);
    }
    else{
        printf("预约失败\n");
    }
    add_on_line(number + 1, name, admission, aim_time);
    printf("预约成功！您的取号顺序是：%d\n", number + 1);
}

