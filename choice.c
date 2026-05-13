//选择界面实现
#include "app.h"

//选择界面
void choice(){
    int choice;
    while (1) {
        menu_printf_all();
        init_admission_queue();
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                menu_printf_on_line();
                break;
            case 2:
                //线下排队挂号界面
                menu_printf_off_line();
                break;
            case 3:
                //签到界面
                menu_printf_sign_in();
                break;
            case 4:
                //显示总体排队情况
                printf_overall_queue();
                break;
            case 5:
                //叫号
                menu_printf_call_number();
                break;
            case 6:
                free_admission_queue();
                printf("感谢使用医院挂号系统！再见！\n");
                exit(0);
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
}