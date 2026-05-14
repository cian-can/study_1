//测试函数
#include "app.h"

//测试添加线上预约挂号信息
void test_add_on_line() {
    add_on_line(1, "张三", "内科", "2024-06-01 09:00");
    add_on_line(2, "李四", "外科", "2024-06-01 10:00");
    add_on_line(3, "王五", "儿科", "2024-06-01 11:00");
    add_on_line(4, "赵六", "妇科", "2024-06-01 13:00");
    add_on_line(5, "钱七", "眼科", "2024-06-01 14:00");
    add_on_line(6, "孙八", "耳鼻喉科", "2024-06-01 15:00");
    add_on_line(7, "周九", "口腔科", "2024-06-01 16:00");
    add_on_line(8, "吴十", "皮肤科", "2024-06-01 17:00");
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