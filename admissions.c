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
    // admission_queue[5]->name = "耳鼻喉科";
    // admission_queue[6]->name = "口腔科";
    // admission_queue[7]->name = "皮肤科";
    // admission_queue[8]->name = "骨科";
    // admission_queue[9]->name = "神经科";
    // admission_queue[10]->name = "心血管科";
    // admission_queue[11]->name = "肿瘤科";
    // admission_queue[12]->name = "消化科";
    // admission_queue[13]->name = "内分泌科";
    // admission_queue[14]->name = "肾内科";
    // admission_queue[15]->name = "血液科";
    // admission_queue[16]->name = "呼吸科";
    // admission_queue[17]->name = "精神科";
    // admission_queue[18]->name = "康复科";
    // admission_queue[19]->name = "急诊科";
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

    if (!person || !person->admission) return;
    int index = find_admission(person->admission);
    //还要修改，等复诊功能完善后再修改
    if (index == -1) {
        printf("没有找到对应科室，无法添加患者信息！\n");
        return;
    }
    
    Admission *ad = admission_queue[index];
    if (ad->count >= admission_number_per_day) {
        printf("%s 今日号源已满！\n", ad->name);
        return;
    }

    // 新建节点（避免原队列被释放）
    Person *new_p = (Person*)malloc(sizeof(Person));
    new_p->number = person->number;
    new_p->name = strdup(person->name);
    new_p->admission = strdup(person->admission);
    new_p->sub = person->sub;
    new_p->if_sub = person->if_sub;
    new_p->next = NULL;

    if (ad->head == NULL) {
        ad->head = new_p;
        ad->tail = new_p;
    } else {
        ad->tail->next = new_p;
        ad->tail = new_p;
    }

    ad->count++;
    if (ad->call_number == 0) ad->call_number = 1;
}

//把合并队列批量加入科室
void add_patients_admission_queue() {
    while (1) {
        if (all_off_line_front != all_off_line_rear) {
            add_admission_queue(&all_off_line_queue[all_off_line_front]);
            all_off_line_front = (all_off_line_front + 1) % MAX_ALL_NUMBER;
        } else {
            break;
        }
    }
}

//显示总体排队情况
void display_queue_status() {
      printf("\n===== 各科室排队情况 =====\n");
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        Admission *ad = admission_queue[i];
        printf("%-10s : 排队 %2d 人 | 当前叫号 %d\n",
               ad->name, ad->count, ad->call_number);
    }
}

//叫号
void call_number() {
        int called = 0;
    for (int i = 0; i < ADMISSION_SIZE; i++) {
        Admission *ad = admission_queue[i];
        if (ad->count > 0) {
            Person *p = ad->head;
            printf("\n【叫号】%s -> 当前号码：%d | 患者：%s\n",
                   ad->name, ad->call_number, p->name);

            // 移除链表头
            ad->head = ad->head->next;
            if (ad->head == NULL) ad->tail = NULL;

            // 释放节点内存
            free(p->name);
            free(p->admission);
            free(p);

            ad->count--;
            ad->call_number++;
            called = 1;
        }
    }
    if (!called) {
        printf("\n所有科室暂无排队患者！\n");
    }
}

//释放内存
void free_admission_queue() {
   for (int i = 0; i < ADMISSION_SIZE; i++) {
        Person *cur = admission_queue[i]->head;
        while (cur != NULL) {
            Person *tmp = cur;
            cur = cur->next;
            free(tmp->name);
            free(tmp->admission);
            free(tmp);
        }
        free(admission_queue[i]);
    }
}