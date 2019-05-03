#include<stdio.h>
struct avl
{
    struct avl* left;
    struct avl* right;
    int data,bal,height;
};
/* bal->balancing factor =  height of left subtree - height of right subtree
 * height - height of that node
 */

 /*Functions
  * Balance() - check whether tree is balanced
  * CalculateBal() - To calculate the bal, height
  * Insert() - Insert new node
  * Delete() - Delete given node
  * LeftRotate() - Perform Simple left rotation
  * RightRotate() - Perform Simple Right rotation
  * LeftRight() - Perform Left-Right rotation
  * RightLeft() - Perform Right-Left rotation
  */
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
                    break;
            case 4: exit(-1);

        }

    }
}
void Insert(struct avl** root ,int data,struct avl** parent)
{
    int h;
    struct avl* temp = (struct avl*)malloc(sizeof(struct avl));             // Temporary node
        temp->data = data;
        temp->height = 0;
        temp->bal = 0;
        temp->left = NULL;
        temp->right = NULL;
    if(*root == NULL)
    {
        *root = temp;                                //attach the new node
        return;
    }
    struct avl* rt = *root;
    struct avl* par = *parent;
    if(rt->data >= data)                             //traverse left subtree, because data is smaller than root
             Insert(&(rt->left),data,&rt);
    else
             Insert(&(rt->right),data,&rt);          //traverse right subtree, because data is larger than root

    /*After new node inserted
     * Update the height and bal, while moving upwards to the root
     */
          CalculateBal(&rt);                         //Update height and balancing factor
          Balance(&rt,&par);                        //check whether tree is balanced


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
    struct avl *xsucc;
    struct avl* rt = *root;
    struct avl* parent = *par;
    struct avl* parent1 = *par;

    if(rt->data<data)                                       //data larger
            if(rt->right != NULL)
               {
                 parent = *root;
                 Delete(&(rt->right),data,&parent);         //Traverse Right subtree
                }
            else                                             //item not found,cuz no right child
                printf("Item not found");
    else if(rt->data > data)                                //data smaller
           {
               if(rt->left != NULL)
                   {
                     parent = *root;
                     Delete(&(rt->left),data,&parent);      //Traverse Left subtree
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

        /*If two child present for node to be deleted
          then, find indorder successor of node copy that data.
          After that deleting node will have either one or no child
          */
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
            printf("Inorder successor :%d",xsucc->data);
            rt = xsucc;                 //node with either 1 or 0 child (inoder succusor)

        }

        /*No child for deleting node*/
        if(rt->left == NULL && rt->right ==NULL)
        {

            if(parent != NULL)              //parent is NULL if root element
            {
                if(parent->left == rt)
                parent->left = NULL;
                else
                parent->right = NULL;
            }

            free(rt);
            rt = NULL;
          
            return;
        }

        //Only Left child
        if(rt->left != NULL&& parent != NULL)
        {

                if(parent->left == rt)
                    parent->left = rt->left;
                else
                    parent->right = rt->left;

            free(rt);
            rt = NULL;
            return;
        }

        //Only Right child
        if(rt->right != NULL&&parent != NULL)
        {
            if(parent->left == rt)
                parent->left = rt->right;
            else
                parent->right = rt->right;

            free(rt);
            rt = NULL;
            return;

        }
        return;                             //return after deleting

    }
    printf(" balancing");
    CalculateBal(&rt);                      //Update

    Balance(&rt,&parent1);                  //check for balance

    return;

}
void CalculateBal(struct avl** root)
{
    int h;
    struct avl* rt = *root;
    if(rt->left == NULL && rt->right == NULL)               //no child
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
                     rt->bal = -h-1;                        //negative value, right subtree larger
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
                    rt->height = ++h;                       //positive value, left subtree larger
                }
                else
                {
                    h = rt->right->height;
                    rt->height = ++h;
                }
        rt->bal = rt->left->height - rt->right->height;     //calculating bal
        }
}

void Balance(struct avl** node,struct avl** parent)
{
    char c;
    struct avl* par = *parent;
    struct avl* temp = *node;
    struct avl* pivot;
    int bal = temp->bal;

    if(bal == -2)
    {
        pivot = temp->right;                        //pivot is right child of root if bal is -2
        if(pivot->bal<0)
           {
            c = 'R';
             printf("Left rotation : %d",temp->data);
             LeftRotate(&temp,&par,c);                //when pivot is negative
           }
        else
           {
             printf("Right Left rotation %d",temp->data);
             RightLeft(&temp,&par);                     //when pivot is positive
           }
    }
    if(bal == 2)
    {
        pivot = temp->left;                        	 //pivot is left child of root if bal is 2
        if(pivot->bal>0)
           {
               c= 'L';
             printf("Right rotation : %d",temp->data);
             RightRotate(&temp,&par,c);                 //when pivot is positive
           }
        else
            {
                printf("Left right rotation %d",temp->data);
                LeftRight(&temp,&par);                  //when pivot is negative

            }
    }
}
void LeftRotate(struct avl** root,struct avl** parent,char c)
{
    struct avl* par = *parent;
    struct avl* rt = *root;

    struct avl* pivot = rt->right;
    struct avl* Y = pivot->left;

    rt->right = NULL;                       //disconnect from pivot
    pivot->left = rt;

    if(Y != NULL)
        rt->right = Y;

    if(par!=NULL)
    {
        if(c== 'L')
            par->left = pivot;
        if(c == 'R')                       //connect pivot with parent
            par->right = pivot;

    }
    else                                    //left rotation of root element
    {
        printf("ROOT");
        ROOT = pivot;                       //make pivot as root
    }

    printf("\npivot left %d pivot right: %d ",pivot->left->data,pivot->right->data);

    CalculateBal(&rt);                          //first child node bal is calculated
    CalculateBal(&pivot);

}
void RightRotate(struct avl** root,struct avl** parent,char c)
{
    struct avl* par = *parent;
    struct avl* rt = *root;

    struct avl* pivot = rt->left;
    struct avl* Y = pivot->right;

    rt->left = NULL;                        //disconnect from pivot
    pivot->right = rt;

    if(Y != NULL)
        rt->left = Y;

    if(par!=NULL)
    {
        if(c == 'L')
            par->left = pivot;
        if(c == 'R')
            par->right = pivot;                   //connect pivot with parent
    }
    else                                           //right rotation of root element
    {
        printf("ROOT");
        ROOT = pivot;                            //make pivot as root
    }

    CalculateBal(&rt);                          //first child node bal is calculated
    CalculateBal(&pivot);

}
void LeftRight(struct avl** root,struct avl** parent)
{
    char c ='L';
    struct avl *rt1 = *root, *rt2 = *root ;
    struct avl* par = *parent;

    struct avl* pivot = rt1->left;                  //pivot is left child of root

    LeftRotate(&pivot,&rt1,c);                      //Left rotating from pivot

    RightRotate(&rt2,&par,c);                       //Right rotate from root

}
void RightLeft(struct avl** root,struct avl** parent)
{
    char c ='R';
    struct avl *rt1 = *root,*rt2 = *root;        //rt changes afer first rotation so two pointer used
    struct avl* par = *parent;

    struct avl* pivot = rt1->right;                 //pivot is right child of root

    RightRotate(&pivot,&rt1,c);                    //Right rotating from pivot

    LeftRotate(&rt2,&par,c);                        //Left rotate from root

}


