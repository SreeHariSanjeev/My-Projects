#include<stdio.h>
struct avl
{
    struct avl* left;
    struct avl* right;
    int data,bal,height;
};
int main()
{
    struct avl *root = NULL,*parent = NULL;

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
                    Insert(&root,data);
                    break;
            case 2: printf("\nEnter the number: ");
                    scanf("%d",&data);
                    Delete(&root,data,&parent);
                    break;
            case 3: Traverse(root);

        }

    }
}
void Insert(struct avl** root ,int data)
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
    if(rt->data >= data)
         Insert(&(rt->left),data);
    else
         Insert(&(rt->right),data);


      if(rt->right == NULL || rt->left ==NULL)
            {
                if(rt->right != NULL)
                   {
                     rt->height = rt->right->height + 1;
                     h = rt->right->height;
                     rt->bal = -h-1;
                   }
                else
                    {
                         rt->height= rt->left->height + 1;
                         rt->bal = rt->left->height +1;
                    }
                //rt->height++;
            }
        else
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
                 //parent = *root;
                 Delete(&(rt->right),data,&parent);
                 printf("\n parent: %d",rt->data);
                 printf("\nRight");
               }
            else                        //item not found
                printf("Item not found");
    else if(rt->data > data)
           {

               if(rt->left != NULL)
                   {
                     //parent = *root;
                     Delete(&(rt->left),data,&parent);
                     printf("\n parent: %d",rt->data);
                     printf("\nLeft");
                   }
                else
                    printf("Item not found");
           }
    else
    {
        if(parent == NULL)             //If root element is deleted we can't traverse the tree
        {
            free(rt);
            *root = NULL;           //set root to null to avoid garbage value
            return;
        }

        if(rt->left != NULL && rt->right != NULL)
        {
            printf("\ntwo child");
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

        }
        if(rt->left == NULL && rt->right ==NULL)
        {
            printf("\nno child");
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
            return;
        }

        if(rt->left != NULL&& parent != NULL)
        {
            printf("\nleft child");
                if(parent->left == rt)
                    parent->left = rt->left;
                else
                    parent->right = rt->left;

            free(rt);
            rt = NULL;
            return;
        }
        if(rt->right != NULL&&parent != NULL)
        {
            printf("\nRight child");
            if(parent->left == rt)
                parent->left = rt->right;
            else
                parent->right = rt->right;

            free(rt);
            rt = NULL;
            return;

        }

    }

    if(rt->right == NULL || rt->left ==NULL)
        {
            if(rt->right != NULL)
                   {
                     rt->height = rt->right->height + 1;
                     h = rt->right->height;
                     rt->bal = -h-1;                        //negative value
                   }
                else                                        //Left child present
                    {
                        rt->left = rt->left->height + 1;
                         rt->bal = rt->left->height +1;
                    }
        }
        else
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
    if(rt->left == NULL && rt->right == NULL)
    {
        rt->height = 0;
        rt->bal = 0;
    }
    return;

    /*if(found == 0)
    {
        printf("Item not found");
        return;
    }*/

}
void search(struct avl* root,struct avl**rt,int data,struct avl** parent,int* found)
{
    *found = 0;
    *parent = NULL;
    while(1)
    {

        if(root->data == data)
        {
            *found = 1;
             break;
        }
        *parent = root;

        if(root->data<data)
            if(root->right != NULL)
                root = root->right;
            else                        //item not found
                break;
        else
            if(root->left != NULL)
                root = root->left;
            else
                break;
    }
    *rt = root;

}

