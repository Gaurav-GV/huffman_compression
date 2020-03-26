
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct frequencytable{
    char character;
    long int frequency;
    struct frequencytable*link;
} Q;

typedef struct Tree{
    long int freq;
    char character;
    struct Tree*lnode,*rnode,*link;
}BTree;


Q*head1 = NULL;
BTree*head2 = NULL;

void insertinLL(char c, int freq)
{
     Q*tempnode = (Q*)malloc(sizeof(Q));
     Q*temp = head1;
     tempnode->character = c;
     tempnode->frequency = 1;
     tempnode->link = NULL;

            if (head1==NULL)
            {
                head1 = tempnode;
            }
            else
            {
                while(temp!=NULL)
                {
                    if (temp->character==c)
                    {
                        temp->frequency++;
                        break;
                    }
                    else
                    {
                        if (temp->link==NULL)
                        {
                            temp->link=tempnode;
                            break;
                        }
                        else
                            temp = temp->link;
                    }

                }

            }
}


void traverse(FILE*a,Q*head)
{
    int count = 0;
   char charac;
    if(a==NULL)
   {
       printf("Unable to open the file");
   }
   else{
        FILE*filepointer=a;
        charac=getc(filepointer);
    while((int)charac!=EOF)
    {
        printf("%C ",charac);
        insertinLL(charac,0);
        count++;
        charac = getc(filepointer);

   }
   printf("\nthe number of character is %d\n",count);
}
}

void printLL()
{
    Q*temp = head1;
    BTree*temp1 = head2;


    if(head1==NULL)
        printf("\nEmpty HEAD1\n");
    else
    {
         printf("\n     HEAD1     \n");
            printf("\nData     Frequency\n");
    while (temp!=NULL)
    {
        printf("%c------%ld\n",temp->character, temp->frequency);
        temp = temp->link;
    }
    }

/*    if(head2==NULL)
        printf("\nEmpty HEAD2\n");
        else
        {printf("\n     HEAD2     \n");
          printf("\nData     Frequency\n");
    while (temp1!=NULL)
    {
        printf("%C------%ld\n",temp1->character, temp1->freq);
        temp1 = temp1->link;
    }
    }*/
}

void swap(Q*a,Q*b)
{
    int ai;
    char ac;

    ai = a->frequency;
    a->frequency = b->frequency;
    b->frequency = ai;

    ac = a->character;
    a->character = b->character;
    b->character = ac;
}

void sortLL()
{
    Q*temp = head1;
    Q*temp1;
    while(temp->link!=NULL)
    {

        temp1 = temp;
        while(temp1!=NULL)
        {
            if(temp1->frequency<temp->frequency)
                {
                    swap(temp1,temp);
                }
            temp1 = temp1->link;
        }
        temp =temp->link;
    }
}

BTree*elementBTree()
{
    BTree*newelement = (BTree*)malloc(sizeof(BTree));
    newelement->lnode = newelement->rnode = newelement->link = NULL;
    newelement->freq = 0;
    newelement->character = 0;
    return newelement;
}

BTree* dequelowest()
{
    BTree*temphead1 = elementBTree();

    if(head2==NULL)
    {
        temphead1->freq = head1->frequency;
        temphead1->character = head1->character;
        head1 = head1->link;
    }
   else if(head1==NULL)
    {
        temphead1->freq = head2->freq;
        temphead1->character = head2->character;
        temphead1->lnode = head2->lnode;
        temphead1->rnode = head2->rnode;
        head2 = head2->link;
    }
    else
    {
        if(head1->frequency<=head2->freq)
        {
           temphead1->freq = head1->frequency;
           temphead1->character = head1->character;
           head1 = head1->link;
        }
        else
        {
            temphead1->freq = head2->freq;
            temphead1->character = head2->character;
            temphead1->lnode = head2->lnode;
            temphead1->rnode = head2->rnode;
            head2 = head2->link;
        }
    }
    return temphead1;
}

void insertinQ2(BTree*temp)
{
    BTree*temph = head2;
    if(head2 == NULL)
        {

            head2 = temp;
        }
    else
    {
        while(temph->link!=NULL)
        {
            temph = temph->link;
        }
        temph->link = temp;
    }
}

void createBT()
{
    BTree*temp1,*temp2;
    BTree*tempheadf = elementBTree();
    temp1 = dequelowest();
    //printf("\ntemp1\ncharacter1 = %c\nfrequency1 = %d\n",temp1->character,temp1->freq);
    temp2 = dequelowest();
    //printf("\ntemp2\ncharacter2 = %c\nfrequency2 = %d\n",temp2->character,temp2->freq);

    tempheadf->freq = temp1->freq+temp2->freq;

    tempheadf->lnode = temp1;
    tempheadf->rnode = temp2;

    tempheadf->character = 0;

    insertinQ2(tempheadf);

}


int oneelement()
{
    Q*temp1 = head1;
    BTree*temp2 = head2;
    int count1 = 0;
    int count2 = 0;

    while(temp1!=NULL)
    {
        temp1 = temp1->link;
        count1++;
    }
    while(temp2!=NULL)
    {
        temp2 = temp2->link;
        count2++;
    }
    if((count1+count2)<=1)
        return 1;
    else
        return 0;
}

void inorder(BTree*t)
{
        if(head2==NULL)
        {
            printf("ERROR");
        }
    if (t!=NULL)
    {
        inorder(t->lnode);
        if(t->lnode==NULL&&t->rnode==NULL)
        printf("%c",t->character);
        inorder(t->rnode);
    }
    else
    {

    }
}

void main()
{
    FILE*a;
    a=fopen("c.pdf","r");
    traverse(a,head1);
    sortLL();

printLL();
    while(oneelement()==0)
    {

        createBT();

    }

    printf("\n------------------------------------------\n");
inorder(head2);
printf("\n------------------------------------------\n");

    fclose(a);
}
