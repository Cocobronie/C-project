/*
README
来自b站:https://www.bilibili.com/video/BV11p4y1i7JH?spm_id_from=333.880.my_history.page.click
实现一个基于C语言的图书管理系统
学习目的：
     1、了解基于命令行交互的项目实现
     2、了解项目实现的基本步骤
*/

/***********************************************************************************************************************************
    // 补充知识：指针如何变成变量
        int* p = NULL;
        int a = 1;
    // （1） 用变量的地址
        p = &a;
        printf("%d\n",*p);  //1
        *p = 1001;
        printf("%d\n",*p);  //1101
    // （2） 动态内存申请
        p = (int*) malloc(sizeof (int));
        *p = 1003;
        printf("%d\n",*p);    //1003
***********************************************************************************************************************************/

#include <string.h>
#include <stdio.h>
// <stdlib.h> 声明了数值与字符串转换函数, 伪随机数生成函数, 动态内存分配函数, 进程控制函数等公共函数
#include <stdlib.h>


//-----------------------------------3、数据的处理:用什么数据结构---->链表---------------------------------------------

        struct bookInfo
        {
            char name[20];   //书名
            float price;     //书籍的价格
            int num;         //书的数量
        };

       struct Node
       {
           struct bookInfo data;
           struct  Node* next;
       };

       struct Node* list = NULL;    //全局链表

       //创建表头
       struct Node* createhead()
       {

           //动态申请内存
           struct Node* headNode = (struct Node*)malloc(sizeof (struct Node));
           //变量的基本规则--->使用前必须初始化
           headNode->next = NULL;
           return headNode;
       }

       //创建结点：为插入做准备
       //把用户的数据作为结构体变量
       struct Node* createNode(struct bookInfo data)
       {
           struct Node* newNode = (struct Node*)malloc(sizeof (struct Node));
           newNode->data = data;
           newNode->next = NULL;
           return newNode;
       }

       //打印链表
       void printList(struct Node* headNode)
       {
           struct Node* p = headNode->next;
           printf("书名\t价格\t数量\n");
           while (p)
           {
               //剥洋葱
                printf("%s\t%.1f\t%d\n",p->data.name,p->data.price,p->data.num);
                p = p->next;
           }
       }

       //插入：头插法
       void insertNodeByHead(struct Node* headNode,struct bookInfo data)
       {
           struct Node* newNode = createNode(data);
           newNode->next = headNode->next;
           headNode->next = newNode;
       }

       //删除：指定书籍名字删除
       void deleteNodeByName(struct Node* headNode,char *bookname)
       {
           struct Node* posLefNode = headNode;  //目标结点前驱
           struct Node* posNode = headNode->next;   //目标结点
           while (posNode != NULL && strcmp(posNode->data.name , bookname))
           {
                posLefNode = posNode;
                posNode = posNode->next;
           }

           //讨论查找结果
           if(posNode == NULL)
               return;
           else
           {
               printf("删除成功\n");
               posLefNode->next = posNode->next;
               free(posNode);
               posNode = NULL;
           }
       }


        //查找：指定书籍名字查找
       struct Node* searchByname(struct Node* headNode,char* bookname)
       {
           struct Node* posNode = headNode->next;
           while (posNode && strcmp(posNode->data.name,bookname))
           {
               posNode = posNode->next;
           }
           return  posNode;
       }

       //冒泡排序
       void bubbleSortList(struct Node* headNode)
       {

           for(struct Node* p = headNode->next; p!=NULL ;p = p->next)
           {
               for(struct Node* q = headNode->next; q!=NULL ;q = q->next)
               {
                   if(q->data.price > q->next->data.price)
                   {
                       //交换值
                       struct bookInfo tempdata = q->data;
                       q->data = q->next->data;
                       q->next->data = tempdata;
                   }
                   else
                   {
                       //printf("okk\n");
                       break;
                   }

                }

           }

       }

//---4、对 list 做文件操作：当我们第一次打开系统的时候，将文件中的信息读入 list ,当我们运行完程序之后，将我们的信息同步到文件中去
               //文件存操作
               void saveInfoToFile(const char* filename,struct Node* headNode)
               {
                   //打开文件（以可读方式）
                   FILE *fp = fopen(filename,"w");
                   struct Node* p = headNode->next;
                   while (p)
                   {
                       fprintf(fp,"%s\t%.1f\t%d\t\n",p->data.name,p->data.price,p->data.num);
                       p = p->next;
                   }

                   //关闭文件
                   fclose(fp);
               }

               //文件读操作
               void readInfoFromFile(const char* filename,struct Node* headNode)
               {
                   FILE *fp = fopen(filename,"r");     //第一次打开时文件不存在
                   //不存在就创建文件
                   if(fp ==NULL)
                   {
                       fp = fopen(filename,"w+");
                   }

                   struct bookInfo tempdata;

                   while (fscanf(fp,"%s%f%d\n",tempdata.name,&tempdata.price,&tempdata.num)!=EOF)
                   {
                       insertNodeByHead(headNode , tempdata);
                   }

                   fclose(fp);
               }


//1、--------------------------------------写界面--->菜单--->模块---------------------------------------------------------------------------------------------
        void makeMenu()
        {
            printf("------------------------------------\n");
            printf("图书管理系统\n");
            printf("\t0.退出系统\n");
            printf("\t1.登记书籍\n");
            printf("\t2.浏览书籍\n");
            printf("\t3.借阅书籍\n");
            printf("\t4.归还书籍\n");
            printf("\t5.书籍排序\n");
            printf("\t6.删除书籍\n");
            printf("\t7.查找书籍\n");
            printf("------------------------------------\n");
            printf("请输入(0~7):");
        }

//2.-----------------------------------------------做交互------------------------------------------------------------
        void keyDown()
        {
            int userkey = 0;
            struct bookInfo tempBook;   //产生一个临时的变量存储书籍信息
            struct Node* result = NULL;//查找结果
            scanf("%d", &userkey);
            switch (userkey)
            {
            case 0:
                printf("【 退出 】\n");
                printf("退出成功\n");
                system("pause");
                exit(0);
                break;
            case 1:
                printf("【 登记 】\n");
                printf("请输入书籍信息(name,price,num):");
                scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num);    //注意这个 “tempBook.name” 前面没有“&”！！
                insertNodeByHead(list,tempBook);
                saveInfoToFile("bookinfo.txt",list);        //保存到文件
                break;
            case 2:
                printf("【 浏览 】\n");
                printList(list);
                break;
            case 3:
                printf("【 借阅 】\n"); //书籍存在可以借阅，书籍的数量-1，不存在借阅失败
                printf("请输入借阅的书名：");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result==NULL)
                {
                    printf("没有相关书籍");
                }
                else
                {
                    if(result->data.num>0)
                    {
                        result->data.num--;
                        printf("借阅成功\n");
                    }
                }
                break;
            case 4:
                printf("【 归还 】\n"); // 当前书籍的数量+1
                printf("请输入归还的书名：");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result==NULL)
                {
                    printf("该书来源非法");
                }
                else
                {
                        result->data.num++;
                        printf("归还成功\n");
                }
                break;
            case 5:
                printf("【 排序 】\n");
                bubbleSortList(list);
                printList(list);
                printf("排序成功\n");
                break;
            case 6:
                printf("【 删除 】\n");
                printf("请输入删除书名:");
                scanf("%s",tempBook.name);
                deleteNodeByName(list,tempBook.name);
                break;
            case 7:
                printf("【 查找 】\n");
                printf("请输入要查询的书名：");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result == NULL)
                {
                    printf("未找到\n");
                }
                else
                {
                    printf("书名\t价格\t数量\t\n");
                    printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.num);
                }
                break;
            default:
                printf("【 error 】\n");
                break;
            }
        }


int main()
{
    list = createhead();
    readInfoFromFile("bookinfo.txt",list);  //当系统运行时读入文件
    while (1)
        {
            makeMenu();
            keyDown();
            system("pause");
            system("cls");
        }


    system("pause");    //system（）就是调用（DOS）系统命令（和shell命令）,pause ，即DOS命令集合中的暂停命令；
    return  0;
}

