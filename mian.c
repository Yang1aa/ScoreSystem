#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 声明科目字符数组
char a[30] = "EnglishScore";
char b[30] = "MathScore";
char c[30] = "DataStructorScore";
char d[30] = "PhysicsScore";
char *subject[10] = {
    a,
    b,
    c,
    d,
};

// 声明一个student结构体
typedef struct Student

{
    char Num[20];         // 学号
    char Name[20];        // 姓名
    char sex[10];         // 性别
    char birth[15];       // 生日
    float Score[4];       // 分数
    float sum;            // 分数和
    float Average;        // 平均分
    struct Student *next; // 指针
} Student;

// 登录和账号、密码的检验
void passWord()
{
    char Id[10];
    char id[10] = "sudo";
    char Key[10] = "1234";
    char key[10];

    printf("请输入用户名：");
    scanf("%s", Id);
    while (strcmp(Id, id) != 0)
    {
        printf("无此用户，请重新登录！\n");
        printf("请输入用户名：");
        scanf("%s", Id);
    }
    printf("请输入密码：");
    scanf("%s", key);
    while (strcmp(key, Key))
    {
        printf("密码错误，请重新输入！\n");
        printf("请输入密码：");
        scanf("%s", key);
    }
}

// 求平均分数
float Avg(Student *p)
{
    return (p->Score[0] + p->Score[1] + p->Score[2] + p->Score[3] + p->Score[4]) / 5;
}

// 求总分数
float Sum(Student *p)
{
    return (p->Score[0] + p->Score[1] + p->Score[2] + p->Score[3] + p->Score[4]);
}

// 按学号查询
Student *SearchByNum(char id[], Student *head)
{
    Student *p1;
    // 如果p1不为空一直循环
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (strcmp(p1->Num, id) == 0)
        {
            // 如果找到返回这个指针
            return p1;
        }
    }
    // 没找到返回NULL
    return NULL;
}

// 按姓名查询
Student *SearchByName(char name[], Student *head)
{
    Student *p1;
    // 如果p1不为空一直循环
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (strcmp(p1->Name, name) == 0)
        {
            // 如果找到返回这个指针
            return p1;
        }
    }
    // 没找到返回NULL
    return NULL;
}

// 输出全部学生信息
void Display(Student *head)
{
    Student *p1;
    p1 = head;
    printf("%10s%10s%6s%15s%15s%15s%20s%15s%15s%15s\n", "Id", "Name", "sex", "birth" ,subject[0], subject[1], subject[2], subject[3], "AverageScore", "SumScore");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        printf("%10s%10s%6s%15s%15.2f%15.2f%20.2f%15.2f%15.2f%15.2f\n", p1->Num, p1->Name, p1->sex, p1->birth, p1->Score[0], p1->Score[1], p1->Score[2], p1->Score[3], p1->Average, p1->sum);
    }
    printf("\n");
}

// 输出单一学生信息
void DisplaySingle(Student *p)
{
    printf("%10s%10s%6s%15s%15s%15s%20s%15s%15s%15s\n", "Id", "Name", "sex", "birth" ,subject[0], subject[1], subject[2], subject[3], "AverageScore", "SumScore");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%10s%6s%15s%15.2f%15.2f%20.2f%15.2f%15.2f%15.2f\n", p->Num, p->Name, p->sex, p->birth ,p->Score[0], p->Score[1], p->Score[2], p->Score[3], p->Average, p->sum);
}

// 信息读入
Student *ReadInfo()
{
    // 文件指针
    FILE *fp;
    // 学生指针
    Student *head, *p1, *p2;

    // 采用二进制读入Data.txt的文件，如果Data.txt为空执行if，否则执行else
    if ((fp = fopen("Data.txt", "rb")) == NULL)
    {
        printf("\n");
        printf("您还没写入学生信息!\n");
        printf("\n");
        return NULL;
    }
    else
    {
        // 申请内存块，大小为student结构体的内存大小
        head = p2 = p1 = (Student *)malloc(sizeof(Student));
        // 将文件中的二进制数据读取到该缓冲区中p1中  读取的基本单元字节大小sizeof(Student) 读取的基本单元个数为1 文件指针fp;
        fread(p1, sizeof(Student), 1, fp);
        // 如果文件没有读完一直读取 feof如果遇到文件结束，函数值为非零值，否则函数值为0
        while (!feof(fp))
        {
            // 将内容存储到p1
            p1 = (Student *)malloc(sizeof(Student));
            // 继续读取
            fread(p1, sizeof(Student), 1, fp);
            // 数据采用指针存储,将p1接到p2的next域中
            p2->next = p1;
            // 如果读完，结束
            if (feof(fp))
            {
                break;
            }
            // 没读完，p2指针向后移动继续循环
            p2 = p1;
        }
    }
    // p2指针赋空
    p2->next = NULL;
    // 关闭文件
    fclose(fp);
    // 返回头指针
    return head;
}

// 添加信息
Student *Insert(Student *head)
{

    Student *p, *p1, *p2, *q;
    // 输入添加学生的信息
    p2 = p1 = (Student *)malloc(sizeof(Student));
    printf("请输入学号:");
    scanf("%s", p1->Num);
    q = SearchByNum(p1->Num, head);
    if (q)
    {
        printf("学生已存在,不可重复添加!\n");
        return head;
    }
    printf("请输入姓名:");
    scanf("%s", p1->Name);
    printf("请输入性别:");
    scanf("%s", p1->sex);
    printf("请输入出生年月日:");
    scanf("%s", p1->birth);
    for (int i = 0; i < 4; i++)
    {
        printf("请输入成绩%s:", subject[i]);
        scanf("%f", &p1->Score[i]);
    }
    p1->Average = Avg(p1);
    p1->sum = Sum(p1);

    // 将p移动到链表末尾
    for (p = head; p != NULL; p = p->next)
    {
    }
    // 如果起初没有存入，则把P1作为头结点存入
    if (head == NULL)
    {
        head = p1;
    }
    else
    {
        p = p1;
    }
    printf("是否继续?(y/n)");
    // getchar吃回车这个字符
    getchar();
    // 如果不添加，将p1->next域赋空
    if (getchar() == 'n')
    {
        p1->next = NULL;
    }
    // 否则
    else
    {
        while (1)
        {
            p1 = (Student *)malloc(sizeof(Student));
            printf("请输入学号:");
            scanf("%s", p1->Num);
            printf("请输入姓名:");
            scanf("%s", p1->Name);
            printf("请输入性别:");
            scanf("%s", p1->sex);
            printf("请输入出生年月日:");
            scanf("%s", p1->birth);
            for (int i = 0; i < 4; i++)
            {
                printf("请输入成绩%s:", subject[i]);
                scanf("%f", &p1->Score[i]);
            }
            p1->Average = Avg(p1);
            p1->sum = Sum(p1);
            // 将p1接到p2尾部
            p2->next = p1;
            // p2后移
            p2 = p1;
            printf("是否继续?(y/n)");
            getchar();
            if (getchar() == 'n')
            {
                p1->next = NULL;
                break;
            }
        }
    }
    return head;
}

// 修改信息
Student *Modify(Student *head)
{
    Student *p;
    int model;

    printf("1.按学号修改\n");
    printf("2.按姓名修改\n");
    // 输入1为按学号修改  输入2为按姓名修改
    scanf("%d", &model);
    // 如果输入数字不为1或2提示输入错误,直到输入正确
    while (model != 1 && model != 2)
    {
        printf("请输入正确的模式号！\n");
        printf("1.按学号修改\n");
        printf("2.按姓名修改\n");
        scanf("%d", &model);
    }

    // 如果按学号修改
    while (model == 1)
    {
        char id[20];
        printf("请输入要修改的学生的学号:");
        scanf("%s", id);
        p = SearchByNum(id, head);
        // 如果没找到给出提示
        if (p == NULL)
        {
            printf("学生不存在!\n");
        }
        // 找到输入修改信息
        else
        {
            printf("你要修改的学生信息是:\n");
            DisplaySingle(p);
            printf("-- 请按提示输入修改信息--\n");
            printf("请输入学号:");
            scanf("%s", p->Num);
            printf("请输入姓名:");
            scanf("%s", p->Name);
            printf("请输入性别:");
            scanf("%s", p->sex);
            printf("请输入出生年月日:");
            scanf("%s", p->birth);
            for (int i = 0; i < 4; i++)
            {
                printf("请输入成绩%s:", subject[i]);
                scanf("%f", &p->Score[i]);
            }
            p->Average = Avg(p);
            p->sum = Sum(p);
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar() == 'n')
        {
            break;
        }
    }

    while (model == 2)
    {
        char name[20];
        printf("请输入要修改的学生的姓名:");
        scanf("%s", name);
        p = SearchByName(name, head);
        if (p == NULL)
        {
            printf("学生不存在!\n");
        }
        else
        {
            printf("你要修改的学生信息是:\n");
            DisplaySingle(p);
            printf("-- 请按提示输入修改信息--\n");
            printf("请输入学号:");
            scanf("%s", p->Num);
            printf("请输入姓名:");
            scanf("%s", p->Name);
            printf("请输入性别:");
            scanf("%s", p->sex);
            printf("请输入出生年月日:");
            scanf("%s", p->birth);
            for (int i = 0; i < 4; i++)
            {
                printf("请输入成绩%s:", subject[i]);
                scanf("%f", &p->Score[i]);
            }
            p->Average = Avg(p);
            p->sum = Sum(p);
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar() == 'n')
        {
            break;
        }
    }

    return head;
}

// 删除信息
Student *Delete(Student *head)
{
    int model;
    Student *p, *p1;

    printf("1.按学号删除\n");
    printf("2.按姓名删除\n");
    scanf("%d", &model);
    while (model != 1 && model != 2)
    {
        printf("请输入正确的模式号！\n");
        printf("1.按学号删除\n");
        printf("2.按姓名删除\n");
        scanf("%d", &model);
    }
    // 按学号删除
    while (model == 1)
    {
        char id[20];
        printf("请输入要删除的学生的学号:");
        scanf("%s", id);
        p = SearchByNum(id, head);
        if (p == NULL)
        {
            printf("学生不存在!\n");
        }
        else
        {
            printf("你要删除的学生信息为:\n");
            DisplaySingle(p);
            printf("是否真的要删除?(y/n)");
            getchar();
            if (getchar() == 'y')
            {
                // 如果为第一个结点
                if (p == head)
                {
                    head = head->next;
                }
                // 如果为非头结点
                else
                {
                    // 找到要删除结点的前驱
                    for (p1 = head; p1->next != p; p1 = p1->next)
                    {
                    }
                    // 将要删除的前驱结点next域指向要删除结点的后继
                    p1->next = p->next;
                }
            }
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar() == 'n')
        {
            break;
        }
    }
    // 按姓名删除
    while (model == 2)
    {
        char name[20];
        printf("请输入要删除的学生的姓名:");
        scanf("%s", name);
        p = SearchByName(name, head);
        if (p == NULL)
        {
            printf("学生不存在!\n");
        }
        else
        {
            printf("你要删除的学生信息为:\n");
            DisplaySingle(p);
            printf("是否真的要删除?(y/n)");
            getchar();
            if (getchar() == 'y')
            {
                if (p == head)
                {
                    head = NULL;
                }
                else
                {
                    for (p1 = head; p1->next != p; p1 = p1->next)
                    {
                    }
                    p1->next = p->next;
                }
            }
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar() == 'n')
        {
            break;
        }
    }
    return head;
}

// 按姓名显示学生信息
void SelectByName(Student *head)
{
    Student *p;
    while (1)
    {
        char name[20];
        printf("请输入要查询的学生的姓名:");
        scanf("%s", name);
        getchar();
        p = SearchByName(name, head);
        if (p == NULL)
        {
            printf("学生不存在!\n");
        }
        else
        {
            printf("你要查询的学生信息为:\n");
            DisplaySingle(p);
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n')
        {
            break;
        }
    }
}

// 按学号顺序排序
Student *SortById(Student *head)
{
    Student *p1, *p2, *Next;
    Student tmp;
    if (head == NULL)
    {
        printf("没有学生信息！\n");
    }
    else
    {
        // 冒泡排序/交换排序p1为头节点，p2为头结点下一个结点
        for (p1 = head; p1->next != NULL; p1 = p1->next)
        {
            for (p2 = p1->next; p2 != NULL; p2 = p2->next)
            {
                // 按从小到大排序
                if (strcmp(p1->Num, p2->Num) > 0)
                {
                    // 让temp存放p2的地址
                    tmp = *p2;
                    // 让p2存放p1的地址,也就是p2变为p1
                    *p2 = *p1;
                    // 再将存放p2的temp赋值给p1
                    *p1 = tmp;
                    // 将p2->next的指针存放到Next
                    Next = p2->next;
                    // 将p2的next指针指向p1
                    p2->next = p1->next;
                    // 将p1的next指向起初p1的next
                    p1->next = Next;
                }
            }
        }
    }
    return head;
}

// 按姓名顺序排序
Student *SortByName(Student *head)
{
    Student *p1, *p2, *Next;
    Student tmp;
    if (head == NULL)
    {
        printf("没有学生信息！\n");
    }
    else
    {
        // 冒泡排序/交换排序p1为头节点，p2为头结点下一个结点
        for (p1 = head; p1->next != NULL; p1 = p1->next)
        {
            for (p2 = p1->next; p2 != NULL; p2 = p2->next)
            {
                // 按从小到大排序
                if (strcmp(p1->Name, p2->Name) > 0)
                {
                    // 让temp存放p2的地址
                    tmp = *p2;
                    // 让p2存放p1的地址,也就是p2变为p1
                    *p2 = *p1;
                    // 再将存放p2的temp赋值给p1
                    *p1 = tmp;
                    // 将p2->next的指针存放到Next
                    Next = p2->next;
                    // 将p2的next指针指向p1
                    p2->next = p1->next;
                    // 将p1的next指向起初p1的next
                    p1->next = Next;
                }
            }
        }
    }
    return head;
}

// 按总成绩顺序排序
Student *SortBySum(Student *head)
{
    Student *p1, *p2, *Next;
    Student tmp;
    if (head == NULL)
    {
        printf("没有学生信息！\n");
    }
    else
    {
        for (p1 = head; p1->next != NULL; p1 = p1->next)
        {
            for (p2 = p1->next; p2 != NULL; p2 = p2->next)
            {
                // 总成绩按从大到小
                if (p1->sum < p2->sum)
                {
                    tmp = *p2;
                    *p2 = *p1;
                    *p1 = tmp;
                    Next = p2->next;
                    p2->next = p1->next;
                    p1->next = Next;
                }
            }
        }
    }
    return head;
}

// 排序学生信息
Student *Sort(Student *head)
{
    int model;

    printf("1.按学号排序\n");
    printf("2.按总成绩排序\n");
    printf("3.按姓名排序\n");
    scanf("%d", &model);
    switch (model)
    {
    case 1:
        head = SortById(head);
        Display(head);
        break;
    case 2:
        head = SortBySum(head);
        Display(head);
        break;
    case 3:
        head = SortByName(head);
        Display(head);
        break;
    default:
        printf("请输入正确的模式！\n");
        break;
    }
    return head;
}

// 显示每门课程中及格的学生信息
void DisplayByBigAver(Student *head)
{
    Student *p1;
    float grade = 60;
    int i, j, num = 0;
    // 控制换行显示
    int flag1 = 0;
    // 判断是否有不及格同学
    int flag2 = 0;
    // 声明各科平均分
    float aver[4];
    // 声明各科总分
    float sum[4] = {0, 0, 0, 0};

    for (i = 0; i < 4; i++)
    {
        // 求每一科的总分，平均分
        for (p1 = head; p1 != NULL; p1 = p1->next)
        {
            sum[i] += p1->Score[i];
            num++;
        }
        aver[i] = sum[i] / num;
        p1 = head;
    }
    // printf("各科平均分：\n");
    // for (i = 0; i < 4; i++)
    // {
    //     printf("Score%s: %.2f ", subject[i], aver[i]);
    // }
    // printf("\n");
    printf("----------------------------\n");
    printf("以下同学加权平均分及格同学信息：\n");
    p1 = head;
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        // 如果加权平均分大于60
        if (p1->Average >= grade)
        {
            printf("%8s%8s%8.2f", p1->Num, p1->Name, p1->Average);
            flag1 = 1;
            flag2 = 1;
        }
        // 否则，flag为0表示不换行
        else
        {
            flag1 = 0;
        }
        // flag为1表示换行
        if (flag1 == 1)
        {
            printf("\n");
        }
    }
    // 如果没有及格同学输出
    if (flag2 == 0)
    {
        printf("无学生信息!\n");
    }
}

// 显示每门课程中不及格的学生信息
void DisplayBySmallAver(Student *head)
{
    Student *p1;
    float grade = 60;
    int i, j, num = 0;
    // 控制换行显示
    int flag1 = 0;
    // 判断是否有不及格同学
    int flag2 = 0;
    // 声明各科平均分
    float aver[4];
    // 声明各科总分
    float sum[4] = {0, 0, 0, 0};

    for (i = 0; i < 4; i++)
    {
        // 求每一科的总分，平均分
        for (p1 = head; p1 != NULL; p1 = p1->next)
        {
            sum[i] += p1->Score[i];
            num++;
        }
        aver[i] = sum[i] / num;
        p1 = head;
    }
    // printf("各科平均分：\n");
    // for (i = 0; i < 4; i++)
    // {
    //     printf("Score%s: %.2f ", subject[i], aver[i]);
    // }
    // printf("\n");
    printf("----------------------------\n");
    printf("以下同学加权平均不分及格同学信息：\n");
    p1 = head;
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        // 如果加权平均分小于60
        if (p1->Average < grade)
        {
            printf("%8s%8s%8.2f", p1->Num, p1->Name, p1->Average);
            flag1 = 1;
            flag2 = 1;
        }
        // 否则，flag为0表示不换行
        else
        {
            flag1 = 0;
        }
        // flag为1表示换行
        if (flag1 == 1)
        {
            printf("\n");
        }
    }
    // 如果没有不及格同学输出
    if (flag2 == 0)
    {
        printf("无学生信息!\n");
    }
}

// 显示成绩在90分以上的学生信息
void DisplayByHighScore(Student *head)
{
    int i;
    int flag1 = 0;
    int flag2 = 0;
    Student *p1;
    p1 = head;
    printf("----------------------------\n");
    printf("以下同学单门课程在90分以上：\n");
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (p1->Score[0] >= 90 ||
            p1->Score[1] >= 90 ||
            p1->Score[2] >= 90 ||
            p1->Score[3] >= 90)
        {
            printf("%8s%8s", p1->Num, p1->Name);
            flag2 = 1;
            flag1 = 1;
        }
        else
        {
            flag1 = 0;
        }
        if (flag1 == 1)
        {
            printf("\n");
        }
    }
    if (flag2 == 0)
    {
        printf("无学生信息!\n");
    }
}

// 每门科目中不及格的学生信息
void DisplayByLowScore(Student *head)
{
    Student *p1;
    p1 = head;
    int i;
    int flag1 = 0;
    int flag2 = 0;
    printf("----------------------------\n");
    printf("以下同学单门课程不及格：\n");
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (p1->Score[0] < 60 ||
            p1->Score[1] < 60 ||
            p1->Score[2] < 60 ||
            p1->Score[3] < 60 ||
            p1->Score[4] < 60)
        {
            printf("%8s%8s", p1->Num, p1->Name);
            flag1 = 1;
            flag2 = 1;
        }
        else
        {
            flag1 = 0;
        }
        if (flag1 == 1)
        {
            printf("\n");
        }
    }
    if (flag2 == 0)
    {
        printf("无学生信息!\n");
    }
}

// 显示学生信息通过不同条件
void DisplayBy(Student *head)
{
    int model;
    printf("0.显示加权平均分及格的学生信息\n");
    printf("1.显示加权平均分不及格的学生信息\n");
    printf("2.显示成绩在90分以上的学生信息\n");
    printf("3.每门科目中不及格的学生信息\n");
    scanf("%d", &model);
    switch (model)
    {
    case 0:
        DisplayByBigAver(head);
        break;
    case 1:
        DisplayBySmallAver(head);
        break;
    case 2:
        DisplayByHighScore(head);
        break;
    case 3:
        DisplayByLowScore(head);
        break;
    default:
        break;
    }
}

// 将学生信息存入文件中
void WriteInfo(Student *head)
{
    FILE *fp;
    Student *p1;
    p1 = head;
    // 打开文件采用二进制写入
    if ((fp = fopen("Data.txt", "wb")) == NULL)
    {
        // 失败输出不能打开
        printf("不能打开文件!\n");
        return;
    }
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        // 如果返回不为1,提示写入错误,这里的1是写入数
        if (fwrite(p1, sizeof(Student), 1, fp) != 1)
        {
            printf("写入文件错误!\n");
        }
    }
    // 关闭文件
    fclose(fp);
}

int main()
{
    int model, i = 0;
    Student *head;
    // 调用登录和账号、密码的检验函数
    passWord();
    printf("\n------ 欢迎来到学生成绩管理系统------\n");
    head = ReadInfo();
    while (1)
    {
        if (i > 0)
        {
            printf("-----------欢迎回来！------------\n");
        }
        if (!head)
        {
            printf("还没有录入学生信息，请先输入信息！\n");
            head = Insert(head);
        }

        printf("\t1. 录入学生成绩\n");
        printf("\t2. 修改学生成绩\n");
        printf("\t3. 删除学生成绩\n");
        printf("\t4. 按姓名查询学生成绩\n");
        printf("\t5. 成绩排序\n");
        printf("\t6. 按不同方式显示学生成绩\n");
        printf("\t7. 显示全部学生信息\n");
        printf("\t8. 退出\n");
        printf("--------------------------\n");
        printf("请选择模式(1-7):");
        scanf("%d", &model);
        switch (model)
        {
        case 1:
            head = Insert(head);
            break;
        case 2:
            head = Modify(head);
            break;
        case 3:
            head = Delete(head);
            break;
        case 4:
            SelectByName(head);
            break;
        case 5:
            head = Sort(head);
            break;
        case 6:
            DisplayBy(head);
            break;
        case 7:
            Display(head);
            break;
        case 8:
            return 0;
            break;
        default:
            printf("请输入正确的模式号！\n");
        }
        // 将信息写入文件
        WriteInfo(head);
        // i++退出循环
        i++;
    }
}
