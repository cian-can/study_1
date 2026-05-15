#include "app.h"

on_line on_line_queue[ON_LINE_SIZE]; // 线上预约挂号数组

Person sign_up_queue[ON_LINE_SIZE]; // 签到排队队列
int sign_up_front = 0;              // 签到排队队头
int sign_up_rear = 0;               // 签到排队队尾

// 初始化线上预约挂号数组
void init_on_line_queue()
{
    for (int i = 0; i < ON_LINE_SIZE; i++)
    {
        on_line_queue[i].number = 0;
        on_line_queue[i].name = NULL;
        on_line_queue[i].admission = NULL;
        on_line_queue[i].time = NULL;
        on_line_queue[i].tag = 0;
    }
}
//初始化签到队列
void init_sign_up_queue() {
    for (int i = 0; i < ON_LINE_SIZE; i++) {
        sign_up_queue[i].number = 0;
        sign_up_queue[i].name = NULL;
        sign_up_queue[i].admission = NULL;
        sign_up_queue[i].sub = 0;
        sign_up_queue[i].if_sub = 0;
        sign_up_queue[i].next = NULL;
    }
}

// 添加线上预约挂号信息
void add_on_line(int number, char *name, char *admission, char *time)
{
    for (int i = 0; i < ON_LINE_SIZE; i++)
    {
        if (on_line_queue[i].number == 0)
        { // 找到第一个空位
            on_line_queue[i].number = number;
            on_line_queue[i].name = strdup(name);
            on_line_queue[i].admission = strdup(admission);
            on_line_queue[i].time = strdup(time);
            on_line_queue[i].tag = 0; // 默认未签到
            break;
        }
    }
}

// 查看数组未编号位置
int find_empty_on_line()
{
    for (int i = 0; i < ON_LINE_SIZE; i++)
    {
        if (on_line_queue[i].number == 0)
        {
            return i; // 返回第一个空位的索引
        }
    }
    return -1; // 没有空位
}
// 签到线上预约挂号
bool sign_in_on_line(int number)
{
    for (int i = 0; i < ON_LINE_SIZE; i++)
    {
        if (on_line_queue[i].number == number)
        {
            if(on_line_queue[i].tag == 1) {
                return false; // 已经签到过了
            }
            on_line_queue[i].tag = 1; // 签到成功
            // 将签到的患者信息加入签到排队队列
            sign_up_queue[sign_up_rear].number = on_line_queue[i].number;
            sign_up_queue[sign_up_rear].name = strdup(on_line_queue[i].name);
            sign_up_queue[sign_up_rear].admission = strdup(on_line_queue[i].admission);
            sign_up_queue[sign_up_rear].sub = 0;
            sign_up_queue[sign_up_rear].if_sub = 0; // 默认不是复诊排队
            sign_up_queue[sign_up_rear].next = NULL;
            sign_up_rear = (sign_up_rear + 1) % ON_LINE_SIZE; // 循环队列
            break;
        }
    }
    //  // 安全排序
    // int len = (sign_up_rear - sign_up_front + ON_LINE_SIZE) % ON_LINE_SIZE;
    // if (len <= 0) return true;

    // Person temp[ON_LINE_SIZE];
    // int idx = sign_up_front;
    // for (int i = 1; i <= len; i++) {
    //     temp[i] = sign_up_queue[idx];
    //     idx = (idx + 1) % ON_LINE_SIZE;
    // }
    // heap_sort_sign_up_queue(temp, len);

    // idx = sign_up_front;
    // for (int i = 1; i <= len; i++) {
    //     sign_up_queue[idx] = temp[i];
    //     idx = (idx + 1) % ON_LINE_SIZE;
    // }
    return true; // 签到成功
}

// 建最大堆
void creat(Person *queue, int len, int root)
{
    int child;
    Person temp = queue[root];
    child = 2 * root;

    while (child <= len)
    {
        // 找更大的孩子
        if (child < len && queue[child].number < queue[child + 1].number) {
            child++;
        }
        // 父节点更大，停止
        if (temp.number >= queue[child].number) {
            break;
        }
        // 孩子上浮
        queue[child / 2] = queue[child];
        child *= 2;
    }
    queue[child / 2] = temp;
}


// 堆排序将签到队列按照大小顺序排序
void heap_sort_sign_up_queue(Person *sign_up_queue, int size)
{
    // 构建最大堆
    if(size <= 1) {
        return; // 不需要排序
    }
    for (int i = size / 2; i > 0; i--)
    {
        creat(sign_up_queue, size, i);
    }
    for (int i = size; i > 1; i--)
    {
        // 交换位置
        Person temp = sign_up_queue[1];
        sign_up_queue[1] = sign_up_queue[i];
        sign_up_queue[i] = temp;
        creat(sign_up_queue, i-1, 1);
    }
}