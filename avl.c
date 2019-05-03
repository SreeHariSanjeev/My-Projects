#include<stdio.h>
struct avl
{
    struct avl* left;
    struct avl* right;
    int data,bal,height;
};
struct avl* ROOT = NULL;
int main()
{
    struct avl *parent = NULL,*parent1 = NULL;

    int ch,data;
    printf("1.Insert\n2.Delete\n3.Traverse\n4.Exit");
    while(1)
    {
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("Enter the number: ");
                    scanf("%d",&data);
                    Insert(&ROOT,data,&parent1);
                    break;
            case 2: printf("\nEnter the number: ");
                    scanf("%d",&data);
                    Delete(&ROOT,data,&parent);
                    break;
            case 3: Traverse(ROOT);

        }

    }
}
void Insert(struct avl** root ,int data,struct avl** parent)
{
    int h;
    struct avl* temp = (struct avl*)malloc(sizeof(struct avl));
    temp->data = data;
        temp->height = 0;
        temp->bal = 0;
        temp->left = NULL;
        temp->right = NULL;
    if(*root == NULL)
    {
        printf("root null");
        *root = temp;
        return;
    }
    struct avl* rt = *root;
    struct avl* par = *parent;
    if(rt->data >= data)
             Insert(&(rt->left),data,&rt);

    else
             Insert(&(rt->right),data,&rt);

          CalculateBal(&rt);
          Balance(&rt,&par);
             /*if(par != NULL)
          printf("par %d rt: %d ",par->data,rt->data);*/


}
void Traverse(struct avl* root)
{
    if(root != NULL)
    {
        printf("data: %d height: %d  bal: %d\n",root->data,root->height,root->bal);
        Traverse(root->left);
        Traverse(root->right);
    }
}
void Delete(struct avl** root,int data,struct avl** par)
{
    int h;
    //struct avl  *rt = (struct avl*)malloc(sizeof(struct avl));
    struct avl *xsucc;

    //search(*root,&rt,data,&parent,&found);
    struct avl* rt = *root;
    struct avl* parent = *par;
    if(rt->data<data)
            if(rt->right != NULL)
               {
                 parent = *root;
                 Delete(&(rt->right),data,&parent);
                 printf("\n parent: %d",rt->data);
                 printf(" Right");
               }
            else                        //item not found
                printf("Item not found");
    else if(rt->data > data)
           {

               if(rt->left != NULL)
                   {
                     parent = *root;
                     Delete(&(rt->left),data,&parent);
                     printf("\n parent: %d",rt->data);
                     printf(" Left");
                   }
                else
                    printf("Item not found");
           }

     if(rt->data == data){
            printf("%d found",rt->data);
        if(parent == NULL)             //If root element is deleted we can't traverse the tree
        {
            free(rt);
            *root = NULL;           //set root to null to avoid garbage value
            return;
        }

        if(rt->left != NULL && rt->right != NULL)
        {

            parent = rt;
            xsucc = rt->right;
            while(xsucc->left != NULL)
            {
                parent = xsucc;
                xsucc = xsucc->left;
            }
            rt->data = xsucc->data;
            printf("sc:%d",xsucc->data);
            rt = xsucc;                 //node with either 1 or 0 child (inoder succusor)

            printf("two child");
        }
        if(rt->left == NULL && rt->right ==NULL)
        {

            if(parent != NULL)              //parent is NULL if root element
            {
                printf("Paren %d",parent->data);

                if(parent->left == rt)
                parent->left = NULL;
                else
                parent->right = NULL;
            }

            free(rt);
            rt = NULL;
             printf("no child");
            return;
        }

        if(rt->left != NULL&& parent != NULL)
        {

                if(parent->left == rt)
                    parent->left = rt->left;
                else
                    parent->right = rt->left;

            free(rt);
            rt = NULL;
            printf("left child");
            return;
        }
        if(rt->right != NULL&&parent != NULL)
        {
            printf("Right child");
            if(parent->left == rt)
                parent->left = rt->right;
            else
                parent->right = rt->right;

            free(rt);
            rt = NULL;
            return;

        }
        return;

    }
    printf(" balancing");
    if(rt->left == NULL && rt->right == NULL)
    {
        rt->height = 0;
        rt->bal = 0;
        return;
    }

    if(rt->right == NULL || rt->left ==NULL)                //only one child
        {
            if(rt->right != NULL)
                   {
                     rt->height = rt->right->height + 1;
                     h = rt->right->height;
                     rt->bal = -h-1;                        //negative value
                   }
                else                                        //Left child present
                    {
                        rt->height = rt->left->height + 1;
                         rt->bal = rt->left->height +1;
                    }
        }
        else                                                //two child
        {
            if(rt->left->height> rt->right->height)
                {
                    h = rt->left->height;
                    rt->height = ++h;
                }
                else
                {
                    h = rt->right->height;
                    rt->height = ++h;
                }
        rt->bal = rt->left->height - rt->right->height;
        }
        Balance(&rt);

    return;


}
void CalculateBal(struct avl** root)
{
    int h;
    struct avl* rt = *root;
    if(rt->left == NULL && rt->right == NULL)
    {
        rt->height = 0;
        rt->bal = 0;
        return;
    }

    if(rt->right == NULL || rt->left ==NULL)                //only one child
        {
            if(rt->right != NULL)
                   {
                     rt->height = rt->right->height + 1;
                     h = rt->right->height;
                     rt->bal = -h-1;                        //negative value
                   }
                else                                        //Left child present
                    {
                        rt->height = rt->left->height + 1;
                         rt->bal = rt->left->height +1;
                    }
        }
        else                                                //two child
        {
            if(rt->left->height> rt->right->height)
                {
                    h = rt->left->height;
                    rt->height = ++h;
                }
                else
                {
                    h = rt->right->height;
                    rt->height = ++h;
                }
        rt->bal = rt->left->height - rt->right->height;
        }
}
void Balance(struct avl** node,struct avl** parent)
{
    struct avl* par = *parent;
    struct avl* temp = *node;
    struct avl* pivot;
    int bal = temp->bal;
    if(bal == -2)
    {
        pivot = temp->right;
        if(pivot->bal<0)
           {
             printf("Left rotation : %d",temp->data);
             LeftRotate(&temp,&par);
           }
        else
           {
             printf("Right Left rotation %d",temp->data);
           }
    }
    if(bal == 2)
    {
        pivot = temp->left;
        if(pivot->bal>0)
           {
             printf("Right rotation : %d",temp->data);
             RightRotate(&temp);
           }
        else
            {
                printf("Left right rotation %d",temp->data);
            }
    }
}
void LeftRotate(struct avl** root,struct avl** parent)
{
    struct avl* par = *parent;
    struct avl* rt = *root;
    //struct avl* RT = *root;

    struct avl* pivot = rt->right;
    struct avl* Y = pivot->left;

    rt->right = NULL;           //disconnect
    pivot->left = rt;

    if(Y != NULL)
        rt->right = Y;

    if(par!=NULL)
    {
      par->right = pivot;                   //connect pivot with parent
      printf(" parn %d",par->data);
    }
    else                                //left rotation of root element
    {
        ROOT = pivot;                  //make pivot as root
    }

    //rt = pivot;
    printf("\npivot left %d pivot right: %d ",pivot->left->data,pivot->right->data);

    CalculateBal(&rt);                          //first child node bal is calculated
    CalculateBal(&pivot);

    printf("\n pivbal: %d rtbal: %d",pivot->bal,rt->bal);

}
void RightRotate(struct avl** root)
{

}
void LeftRight(struct avl** root)
{

}
void RightLeft(struct avl** root)
{

}

