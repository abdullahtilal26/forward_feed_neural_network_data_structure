#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

struct node{
    int data;
    node *llink;
    node *rlink;
    int heightt;
};

class bt{
    public:
    node *root;

    public:

    //default constructor
    bt(){
        root=0;
    }

    //inorder_traversal
    void inorder_traversal(){
        inorder(root);

    }
    void inorder(node *p){
    
        if(p!=0){
           
            inorder(p->llink);
            cout<<p->data<<" ";
            inorder(p->rlink);
        }
    }

    //preorder traversal
    void preoorder_traversal(){
        preorder(root);
    }
    void preorder(node *p){
        if(p!=0){
            cout<<p->data<<" ";
            preorder(p->llink);
            preorder(p->rlink);
        }
    }
    
    //postorder traversal
    void postorder_traversal(){
        postorder(root);
    }
    void postorder(node *p){
        if(p!=0){
            postorder(p->llink);
            postorder(p->rlink);
            cout<<p->data<<" ";
        }
    }
    int leaves(node *p){
        if(p==0)
            return 0;
        else if(p->llink==0&&p->rlink==0)
            return 1;
        else
        {
            return leaves(p->llink)+leaves(p->rlink);
        }
        
    }
    int total_nodes(node *p){
        int count=0;
        if(p==0)
            return 0;
        else if(p->llink!=0&&p->rlink!=0)
            count++;
        
        count=count +(total_nodes(p->llink)+total_nodes(p->rlink));
        return count;
        
    }
    //height
    int height(node *p){
        if(p==0){
            return 0;
        }
        else
        {
            return (1+ max(height(p->llink),height(p->rlink)));
        }
            
    }
    int size(node *p){
        if(p==0){
            return 0;
        }
        else
        {
            return (1+ (size(p->llink)+size(p->rlink)));
        }
            
    }
    //max height
    int max(int l,int r){
        if(l>=r){
             return l;
        }  
        else{
            return r;
        }  
    }

    //level traversal
    bool print_level(node *root,int level){
        if(root==0){
            return false;
        }
        if(level==1){
            cout<<root->data<<" ";
            return true;
        }
        bool left=print_level(root->llink,level-1);
        bool right=print_level(root->rlink,level-1);
        
        return(left||right);
    }

    void levelOrder(node * root) {
        int level=1;
        
        while(print_level(root,level))
            level++;

    }

    
    int sizee(node *p){
        if(p==0){
            return 0;
        }
        else
        {
            return (1+sizee(p->llink)+sizee(p->rlink));
        }
            
    }

    //copy tree
    void copy_tree(node*(&tocopy_root),node *othercopy_root){
       // node *n=tocopy_root;
       
        if(othercopy_root==0){
            tocopy_root=0;
            cout<<"check2";
        }
        else{
            cout<<"check3";
            tocopy_root=new node;
            tocopy_root->data=othercopy_root->data;
            cout<<"mcopying "<<tocopy_root->data<<endl;
            copy_tree(tocopy_root->llink,othercopy_root->llink);
            copy_tree(tocopy_root->rlink,othercopy_root->rlink);
        }
    }

    //destroy
    void destroy(node *p){
        if(p!=0){
            destroy(p->llink);
            destroy(p->rlink);
            delete p;
            p=0;
        }
    }
    
    //copy constructor
    bt(const bt &rhs){
        if(rhs.root==0){
            root=0;
        }
        else{
            copy_tree(root,rhs.root);
        }
    }

    //destructor
    ~bt(){
        destroy(root);
    }

    //assignment operator
    const bt& operator=(const bt &rhs){
        if(this!=&rhs){
            if(root!=0){
                destroy(root);
            }

            if(rhs.root==0){
                root=0;
            }
            else
            {   
                cout<<"check1";
                copy_tree(root,rhs.root);
                
            }
            
            
        }
        return *this;
    }

    bool search(int n){
        if(root==0){
            return false;
        }
        else{
            node *current=root;
            while(current!=0){
                if(current->data==n){
                    return true;
                }
                else if(current->data>n){
                    current=current->llink;
                }
                else{
                    current=current->rlink;
                }
            }
        }
    }

    void insert(int n){
       
        node *newnode=new node;
        newnode->data=n;
        newnode->llink=0;
        newnode->rlink=0;

        if(root==0){
            root=newnode;
        }
        else{
             node *current;
             node *prev;
             current=root;

            while (current!=0)
            {
                prev=current;
                if(current->data==n){
                    cout<<"element exist";
                }
                else if(current->data>n){
                    current=current->llink;
                }else
                {
                    current=current->rlink;
                }
                
            }

            if(prev->data>n)
                prev->llink=newnode;
            else
            {
                prev->rlink=newnode;
            }
       
        }
    }

    //delete with the address provided
    void deletefromtree(node* &p){
        cout<<"p : "<<p<<" ";
        if(p==0){
            cout<<"element to delete donot exist";
        }
        else if(p->llink==0&&p->rlink==0){
            node *temp=p;
            p=0;
            delete temp;
        }
        else if(p->llink==0){
            node *temp=p;
            p=temp->rlink;
            delete temp;

        }
        else if(p->rlink==0){
            node *temp=p;
            p=p->llink;
            delete temp;
        }
        else
        {
            node *current=p->llink;
            node *prev=0;
            while (current->rlink!=0)
            {
                prev=current;
                current=current->rlink;
            }
            
            p->data=current->data;

            if (prev==0)
            {
                p->llink=current->llink;

            }
            else
            {
                prev->rlink=current->llink;
            }
            delete current;
               
        }
        
    }

    void delete_node(int n){
        node *current;
        node *prev;
        bool found =false;
        if(root==0){
            cout<<"cannot delete from empty tree";
        }
        else
        {
            current=root;
            prev=0;
            while (current!=0&&found!=true){

                if(current->data==n){
                    found=true;
                }
                else{

                    prev=current;
                    if(current->data>n){
                        current=current->llink;
                    }
                    else
                    {
                        current=current->rlink;
                    }
                    
                }  
            }

            if(current==0){
                cout<<"item not found"<<endl;
            }
            else if(found==true)
            {   cout<<"current: "<<current<<" value: "<<current->data;
                //cout<<"root: "<<root<<" llink"<</*prev->llink<<*/" rlink: "<<prev->rlink;
               // cout<<"--"<<root->llink;
               // cout<<n<<prev->data;
                if(current==root){
                    cout<<" root: "<<root;
                    deletefromtree(root);
                }    
                else if(prev->data>n){
                   // cout<<"2";
                    cout<<" llink: "<<prev->llink;
                    deletefromtree(prev->llink);
                }
                else if(prev->data<n)
                {  // cout<<"3";
                    cout<<" rlink: "<<prev->rlink;
                    deletefromtree(prev->rlink);
                }
                
            }
            else
            {
                cout<<"why r u here"<<endl;
            }
            
            

        }
        
    }  

    bool breath_first_search(int value){
        queue< node *> q;
            q.push(root);
            while(q.empty()==false){
                node *ans=q.front();
                q.pop();
                cout<<ans->data;
                if(ans->data==value)
                    return true;
                else{
                    if(ans->llink!=0)
                        q.push(ans->llink);
                    if(ans->rlink!=0)
                        q.push(ans->rlink);

                }
            }
            return false;
    } 

    bool depth_first_search(int value){
        stack<node *> stck;
        stck.push(root);
        while(stck.empty()==false){
            node *ans=stck.top();
            stck.pop();
            cout<<ans->data<<" ";
            if(ans->data==value)
                return true;
            else
            {
                if(ans->rlink!=0)
                     stck.push(ans->rlink);
                if(ans->llink!=0)
                    stck.push(ans->llink);
                   
                
            }
                   
        }
         return false;    
    }

    node* newnode(int value){
        node *newnodee=new node;
        newnodee->data=value;
        newnodee->llink=0;
        newnodee->rlink=0;
        newnodee->heightt=1;
        return newnodee;
    }

    int getbalance(node *nodee)  
    {  
        if (nodee== 0)  
            return 0;  
        return height(nodee->llink) - height(nodee->rlink);  
    }  

    node* rightRotate(node *y)  
    {  
        node *x = y->llink;  
        node *T2 = x->rlink;  
    
        x->rlink = y;  
        y->llink = T2;  

        y->heightt = max(height(y->llink), 
                        height(y->rlink)) + 1;  
        x->heightt = max(height(x->llink), 
                        height(x->rlink)) + 1;  
        return x;  
    }  
  
 
node* leftRotate(node *x)  
{  
    node *y = x->rlink;  
    node *T2 = y->llink;  

    y->llink = x;  
    x->rlink = T2;  

    x->heightt = max(height(x->llink),     
                    height(x->rlink)) + 1;  
    y->heightt = max(height(y->llink),  
                    height(y->rlink)) + 1;  
    return y;  
}  
    node* avl_insert(node *nodee,int value){

        if(nodee==0){
            return (newnode(value));
        }

        if(value<nodee->data)
            nodee->llink=avl_insert(nodee->llink,value);
        else if (value>nodee->data)
        {
            nodee->rlink=avl_insert(nodee->rlink,value);
        }
        else{
            return nodee;
        }

        nodee->heightt=1+(max(height(nodee->llink),height(nodee->rlink)));
        
        int balance=getbalance(nodee);

        if(balance>1&&value<nodee->llink->data){
            return rightRotate(nodee);
        }
        if (balance<-1 && value>nodee->rlink->data)
        {
            return leftRotate(nodee);
        }
        if(balance>1&& value>nodee->llink->data){
            nodee->llink=leftRotate(nodee->llink);
            return rightRotate(nodee);
        }
        if(balance<-1&& value<nodee->rlink->data){
            nodee->rlink=rightRotate(nodee->rlink);
            return leftRotate(nodee);
        }
        
        return nodee;
    }
};

int main(){
    bt tr;
    tr.insert(10);
    tr.insert(5);
    tr.insert(15);
    tr.insert(2);
    tr.insert(7);
    cout<<tr.height(tr.root);
    cout<<tr.sizee(tr.root);
    //cout<<tr.breath_first_search(1)<<endl;
    cout<<tr.depth_first_search(15)<<endl;

    cout<<"avl tree";
    bt tree;
    tree.avl_insert(tree.root,10);
    tree.avl_insert(tree.root,5);
    tree.avl_insert(tree.root,15);
    tree.avl_insert(tree.root,4);
    tree.avl_insert(tree.root,2);
    tree.avl_insert(tree.root,1);
    tree.inorder_traversal();
    //cout<<"sd";
    //return 0;

   /* bt b1;
    b1.insert(60);

    b1.insert(50);
    b1.insert(70);

    b1.insert(30);
    b1.insert(53);
    b1.insert(80);

    b1.insert(35);
    b1.insert(57);
    b1.insert(75);

    b1.insert(32);
    b1.insert(40);
    b1.insert(77);

    b1.insert(48);

    b1.insert(45);
    cout<<"height"<<b1.height(b1.root);
    cout<<"leaves "<<b1.leaves(b1.root);
    cout<<"nodes "<<b1.total_nodes(b1.root);
    cout<<"size: "<<b1.size(b1.root);
    //cout<<b1.root->llink->data<<" *-* "<<b1.root->rlink->data<<endl;
    b1.inorder_traversal();
    cout<<endl;
    b1.delete_node(50);
    b1.inorder_traversal();*/
    // b1.preoorder_traversal();
    // b1.postorder_traversal();
    //okay testes//****************

    //cout<<b1.search(3)<<endl;
            // cout<<"b2 start";
            // bt b2;
            // b2=b1;
            // //b2=b1;
            // cout<<"*";
            // cout<<b2.root->data<<" *-* "<<b2.root->llink->data<<" *-* "<<b2.root->rlink->data<<endl;
            // cout<<"\\";
    //cout<<b2.search(2)<<endl;
   // b1.destroy(b1.root);
   //cout<<b1.search(1);
    
    //b2.inorder((b2.root));
    return 1;
}
