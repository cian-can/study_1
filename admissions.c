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