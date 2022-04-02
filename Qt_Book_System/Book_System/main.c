/*
README
����bվ:https://www.bilibili.com/video/BV11p4y1i7JH?spm_id_from=333.880.my_history.page.click
ʵ��һ������C���Ե�ͼ�����ϵͳ
ѧϰĿ�ģ�
     1���˽���������н�������Ŀʵ��
     2���˽���Ŀʵ�ֵĻ�������
*/

/***********************************************************************************************************************************
    // ����֪ʶ��ָ����α�ɱ���
        int* p = NULL;
        int a = 1;
    // ��1�� �ñ����ĵ�ַ
        p = &a;
        printf("%d\n",*p);  //1
        *p = 1001;
        printf("%d\n",*p);  //1101
    // ��2�� ��̬�ڴ�����
        p = (int*) malloc(sizeof (int));
        *p = 1003;
        printf("%d\n",*p);    //1003
***********************************************************************************************************************************/

#include <string.h>
#include <stdio.h>
// <stdlib.h> ��������ֵ���ַ���ת������, α��������ɺ���, ��̬�ڴ���亯��, ���̿��ƺ����ȹ�������
#include <stdlib.h>


//-----------------------------------3�����ݵĴ���:��ʲô���ݽṹ---->����---------------------------------------------

        struct bookInfo
        {
            char name[20];   //����
            float price;     //�鼮�ļ۸�
            int num;         //�������
        };

       struct Node
       {
           struct bookInfo data;
           struct  Node* next;
       };

       struct Node* list = NULL;    //ȫ������

       //������ͷ
       struct Node* createhead()
       {

           //��̬�����ڴ�
           struct Node* headNode = (struct Node*)malloc(sizeof (struct Node));
           //�����Ļ�������--->ʹ��ǰ�����ʼ��
           headNode->next = NULL;
           return headNode;
       }

       //������㣺Ϊ������׼��
       //���û���������Ϊ�ṹ�����
       struct Node* createNode(struct bookInfo data)
       {
           struct Node* newNode = (struct Node*)malloc(sizeof (struct Node));
           newNode->data = data;
           newNode->next = NULL;
           return newNode;
       }

       //��ӡ����
       void printList(struct Node* headNode)
       {
           struct Node* p = headNode->next;
           printf("����\t�۸�\t����\n");
           while (p)
           {
               //�����
                printf("%s\t%.1f\t%d\n",p->data.name,p->data.price,p->data.num);
                p = p->next;
           }
       }

       //���룺ͷ�巨
       void insertNodeByHead(struct Node* headNode,struct bookInfo data)
       {
           struct Node* newNode = createNode(data);
           newNode->next = headNode->next;
           headNode->next = newNode;
       }

       //ɾ����ָ���鼮����ɾ��
       void deleteNodeByName(struct Node* headNode,char *bookname)
       {
           struct Node* posLefNode = headNode;  //Ŀ����ǰ��
           struct Node* posNode = headNode->next;   //Ŀ����
           while (posNode != NULL && strcmp(posNode->data.name , bookname))
           {
                posLefNode = posNode;
                posNode = posNode->next;
           }

           //���۲��ҽ��
           if(posNode == NULL)
               return;
           else
           {
               printf("ɾ���ɹ�\n");
               posLefNode->next = posNode->next;
               free(posNode);
               posNode = NULL;
           }
       }


        //���ң�ָ���鼮���ֲ���
       struct Node* searchByname(struct Node* headNode,char* bookname)
       {
           struct Node* posNode = headNode->next;
           while (posNode && strcmp(posNode->data.name,bookname))
           {
               posNode = posNode->next;
           }
           return  posNode;
       }

       //ð������
       void bubbleSortList(struct Node* headNode)
       {

           for(struct Node* p = headNode->next; p!=NULL ;p = p->next)
           {
               for(struct Node* q = headNode->next; q!=NULL ;q = q->next)
               {
                   if(q->data.price > q->next->data.price)
                   {
                       //����ֵ
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

//---4���� list ���ļ������������ǵ�һ�δ�ϵͳ��ʱ�򣬽��ļ��е���Ϣ���� list ,���������������֮�󣬽����ǵ���Ϣͬ�����ļ���ȥ
               //�ļ������
               void saveInfoToFile(const char* filename,struct Node* headNode)
               {
                   //���ļ����Կɶ���ʽ��
                   FILE *fp = fopen(filename,"w");
                   struct Node* p = headNode->next;
                   while (p)
                   {
                       fprintf(fp,"%s\t%.1f\t%d\t\n",p->data.name,p->data.price,p->data.num);
                       p = p->next;
                   }

                   //�ر��ļ�
                   fclose(fp);
               }

               //�ļ�������
               void readInfoFromFile(const char* filename,struct Node* headNode)
               {
                   FILE *fp = fopen(filename,"r");     //��һ�δ�ʱ�ļ�������
                   //�����ھʹ����ļ�
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


//1��--------------------------------------д����--->�˵�--->ģ��---------------------------------------------------------------------------------------------
        void makeMenu()
        {
            printf("------------------------------------\n");
            printf("ͼ�����ϵͳ\n");
            printf("\t0.�˳�ϵͳ\n");
            printf("\t1.�Ǽ��鼮\n");
            printf("\t2.����鼮\n");
            printf("\t3.�����鼮\n");
            printf("\t4.�黹�鼮\n");
            printf("\t5.�鼮����\n");
            printf("\t6.ɾ���鼮\n");
            printf("\t7.�����鼮\n");
            printf("------------------------------------\n");
            printf("������(0~7):");
        }

//2.-----------------------------------------------������------------------------------------------------------------
        void keyDown()
        {
            int userkey = 0;
            struct bookInfo tempBook;   //����һ����ʱ�ı����洢�鼮��Ϣ
            struct Node* result = NULL;//���ҽ��
            scanf("%d", &userkey);
            switch (userkey)
            {
            case 0:
                printf("�� �˳� ��\n");
                printf("�˳��ɹ�\n");
                system("pause");
                exit(0);
                break;
            case 1:
                printf("�� �Ǽ� ��\n");
                printf("�������鼮��Ϣ(name,price,num):");
                scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num);    //ע����� ��tempBook.name�� ǰ��û�С�&������
                insertNodeByHead(list,tempBook);
                saveInfoToFile("bookinfo.txt",list);        //���浽�ļ�
                break;
            case 2:
                printf("�� ��� ��\n");
                printList(list);
                break;
            case 3:
                printf("�� ���� ��\n"); //�鼮���ڿ��Խ��ģ��鼮������-1�������ڽ���ʧ��
                printf("��������ĵ�������");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result==NULL)
                {
                    printf("û������鼮");
                }
                else
                {
                    if(result->data.num>0)
                    {
                        result->data.num--;
                        printf("���ĳɹ�\n");
                    }
                }
                break;
            case 4:
                printf("�� �黹 ��\n"); // ��ǰ�鼮������+1
                printf("������黹��������");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result==NULL)
                {
                    printf("������Դ�Ƿ�");
                }
                else
                {
                        result->data.num++;
                        printf("�黹�ɹ�\n");
                }
                break;
            case 5:
                printf("�� ���� ��\n");
                bubbleSortList(list);
                printList(list);
                printf("����ɹ�\n");
                break;
            case 6:
                printf("�� ɾ�� ��\n");
                printf("������ɾ������:");
                scanf("%s",tempBook.name);
                deleteNodeByName(list,tempBook.name);
                break;
            case 7:
                printf("�� ���� ��\n");
                printf("������Ҫ��ѯ��������");
                scanf("%s",tempBook.name);
                result = searchByname(list,tempBook.name);
                if(result == NULL)
                {
                    printf("δ�ҵ�\n");
                }
                else
                {
                    printf("����\t�۸�\t����\t\n");
                    printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.num);
                }
                break;
            default:
                printf("�� error ��\n");
                break;
            }
        }


int main()
{
    list = createhead();
    readInfoFromFile("bookinfo.txt",list);  //��ϵͳ����ʱ�����ļ�
    while (1)
        {
            makeMenu();
            keyDown();
            system("pause");
            system("cls");
        }


    system("pause");    //system�������ǵ��ã�DOS��ϵͳ�����shell���,pause ����DOS������е���ͣ���
    return  0;
}

