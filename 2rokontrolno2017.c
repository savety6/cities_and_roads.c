#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    printf("hay")
    return 0;
}


void load_newcomers(QueueNode *root)
{
   FILE * fp = fopen("newcomers.bin","rb");
   if(fp==NULL){perror("gre6ka1");}
   QueueNode *end=root;

   if(root!=NULL)
    while(end->next!=NULL)
        end = end->next;

   while(feof(fp)!=EOF)
   {
        QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
        if(fread(&temp->node,sizeof(Cage),1,fp)!=1){
           perror("gre6ka2");free(temp);
           break;
        }
        if(root==NULL)
        {root=temp;
        end=temp;
        }
        else {end->next=temp;
        end=end->next;
        }
   }
   fclose(fp);
}
int animal_typecnt(QueueNode *root, char * animalType)
{
    QueueNode *curr=root;
    int count=0;
    for(;curr!=NULL;curr=curr->next)
        if(strcmp(animalType,curr->node.type)==0)count++;
    return count;
}
StackNode *deworming(QueueNode *root)
{
    QueueNode *curr = root;
    StackNode *stack=NULL;
    int maxAge=root->node.age;
    int tempAge=0;
    //namirame naj staroto jivotno
    //namirame sledva6tiq po vuzrast i dobavqme vsi4ki negovi v steka
    int flag = 1;
    while(flag==1)
    {
        flag=0;
        tempAge=0;
      for(curr=root;curr!=NULL;curr=curr->next)
        {
            if(curr->node.age>tempAge && curr->node.age<maxAge){tempAge=curr->node.age;flag=1;}
        }
       maxAge=tempAge;
       for(curr=root;curr!=NULL;curr=curr->next)
    {
        if(curr->node.age==maxAge)
        {
          StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
          if(temp==NULL){perror("gre6ka nqkoq si");return stack;}
          temp->next=stack;
          temp->node=curr->node;
          stack=temp;
        }
    }
    return stack;
}
void store_animals(FILE *fp,StackNode *root)
{
    StackNode *curr;
    for(curr=root;curr!=NULL;curr=curr->next)
    {
        fprintf(fp,"%s %s\n",curr->node.type,curr->node.id);
    }
}
