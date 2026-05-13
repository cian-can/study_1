//科室对应患者排队显示
#include "app.h"

Admission *admission_queue[ADMISSION_SIZE];//就诊科室预约显示


//初始化就诊科室预约显示
void init_admission_queue() {
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        admission_queue[i] = (Admission *)malloc(sizeof(Admission));
        admission_queue[i]->head = NULL; //初始化链表头指针
        admission_queue[i]->tail = NULL; //初始化链表尾指针
        admission_queue[i]->count = 0;
        admission_queue[i]->call_number = 0;
    }
    admission_queue[0]->name = "内科";
    admission_queue[1]->name = "外科";
    admission_queue[2]->name = "儿科";
    admission_queue[3]->name = "妇科";
    admission_queue[4]->name = "眼科";
    admission_queue[5]->name = "耳鼻喉科";
    admission_queue[6]->name = "口腔科";
    admission_queue[7]->name = "皮肤科";
    admission_queue[8]->name = "骨科";
    admission_queue[9]->name = "神经科";
    admission_queue[10]->name = "心血管科";
    admission_queue[11]->name = "肿瘤科";
    admission_queue[12]->name = "消化科";
    admission_queue[13]->name = "内分泌科";
    admission_queue[14]->name = "肾内科";
    admission_queue[15]->name = "血液科";
    admission_queue[16]->name = "呼吸科";
    admission_queue[17]->name = "精神科";
    admission_queue[18]->name = "康复科";
    admission_queue[19]->name = "急诊科";
}

//打印就诊科室
void print_all_admissions() {
    printf("医院科室列表：\n");
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        printf("%s\n", admission_queue[i]->name);
    }
}

//查看有没有对应科室
int find_admission(char *admission) {
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        if (strcmp(admission_queue[i]->name, admission) == 0) {
            return i; //找到对应科室
        }
    }
    return -1; //没有找到对应科室
}

//将患者信息添加到对应科室的链表中，并且更新预约人数和叫号顺序
void add_admission_queue(Person *person) {
    int index = find_admission(person->admission);
    //还要修改，等复诊功能完善后再修改
    if (index == -1) {
        printf("没有找到对应科室，无法添加患者信息！\n");
        return;
    }
    Admission *admission = admission_queue[index];
    if (admission->count >= admission_number_per_day) {
        printf("该科室预约已满，无法添加患者信息！\n");
        return;
    }
    if (admission->head == NULL) {
        admission->head = person;
        admission->tail = person;
    } else {
        admission->tail->next = person;
        admission->tail = person;
    }
    admission->count++;
    admission->call_number++;
}

//将合并后的队列添加到add_admission_queue函数中
void add_pesions_admisssion_queue(){
    while(1)
    {
        if(all_off_line_front != all_off_line_rear) //合并后的队列不为空
        {
            add_admission_queue(&all_off_line_queue[all_off_line_front]);
            all_off_line_front = (all_off_line_front + 1) % OFF_LINE_SIZE;
        }
        else
        {
            break; //合并后的队列为空，添加完成
        }
    }
}

//显示总体排队情况
void display_queue_status() {
    printf("总体排队情况：\n");
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        printf("%s科室：%d人排队，当前叫号顺序：%d\n", admission_queue[i]->name, admission_queue[i]->count, admission_queue[i]->call_number);
    }
}

//叫号
void call_number() {
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        if (admission_queue[i]->count > 0) {
            admission_queue[i]->call_number++;
            printf("请%s科室的患者，取号顺序为%d的%s前来就诊！\n", admission_queue[i]->name, admission_queue[i]->call_number, admission_queue[i]->head->name);
            //将叫号的患者从链表中移除
            Person *temp = admission_queue[i]->head;
            admission_queue[i]->head = admission_queue[i]->head->next;
            free(temp);
            admission_queue[i]->count--;
        }
    }
}

//释放内存
void free_admission_queue() {
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        Person *current = admission_queue[i]->head;
        while (current != NULL) {
            Person *temp = current;
            current = current->next;
            free(temp);
        }
        free(admission_queue[i]);
    }
}