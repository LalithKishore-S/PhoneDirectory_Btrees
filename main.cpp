#include <iostream>
#include <vector>
#include <string>
#include <limits>
typedef struct Phonenode
{
    std::string name;
    std::string phno;
}Phonenode;
typedef struct node
{
    std::vector <Phonenode> keys;
    std::vector <node *>child;
    bool isleaf;

}node;
using namespace std;

void Insert_directory(node *&,Phonenode);
int height(node *);
void printlevel(node *,int );
void levelorder(node *);
Phonenode  search_data(node *,string key);
void Modify(node *&,string key);
bool isempty(Phonenode a);

int main()
{

    node * root=NULL;
    Phonenode a;
    string name,phno;
    char contin;
    int choice;
    cout<<"Enter the datas:\n";
    do
    {
        cout<<"Enter the name:\n";
        getline(cin,name);
        cout<<"Enter the phno:\n";
        getline(cin,phno);
        a.name=name;
        a.phno=phno;
        Insert_directory(root,a);
        cout<<"Do you wish to continue(y/n):\n";
        cin>>contin;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        levelorder(root);
    }while(contin=='y');
    cout<<endl;
    do
    {
        cout<<"Enter the operation you wish to perform :\n1.New entry\n2.Delete data\n3.Retrieve data\n4.Modify data\n5.View all data(B tree structure)";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice)
        {
        case 1:
            cout<<"Enter the name:\n";
            getline(cin,name);
            cout<<"Enter the phno:\n";
            getline(cin,phno);
            a.name=name;
            a.phno=phno;
            Insert_directory(root,a);
            break;
        case 3:
            a.name="";
            a.phno="";
            cout<<"Enter the name to be searched:\n";
            getline(cin,name);
            a=search_data(root,name);
            if(isempty(a)==0)
               cout<<a.name<<" : "<<a.phno<<endl;
            else
               cout<<"There is no data for the given name:"<<name<<"\n";
            break;
        case 4:
            cout<<"Enter the name of the data whose data is to be modified:\n";
            getline(cin,name);
            Modify(root,name);
            break;
        case 5:
            levelorder(root);
            break;
        default:
            cout<<"Enter a valid choice:\n";
        }
        cout<<"Do you wish to continue(y/n):\n";
        cin>>contin;
        cout<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while(contin=='y');
}

void Insert_directory(node *&root,Phonenode a)
{
    if(root==NULL)
    {
        node *temp=new node();
        temp->keys.push_back(a);
        temp->child.push_back(NULL);
        temp->child.push_back(NULL);
        temp->isleaf=1;
        root=temp;
    }
    else
    {
        if(root->isleaf==1)
        {
            if(root->keys.size()!=2)
            {
                int index;
                for(int i=0;i<root->keys.size();i++)
                {
                   if(a.name.compare(root->keys[i].name)>=0)
                   {
                       index=i+1;
                       continue;
                   }
                   else
                   {
                      if(i==0)
                          index=0;
                      else
                          index=i;
                   }
                }
                root->keys.insert(root->keys.begin()+index,a);
                root->child.push_back(NULL);
            }
            else
            {
                int index;
                for(int i=0;i<root->keys.size();i++)
                {
                   if(a.name.compare(root->keys[i].name)>=0)
                   {
                       index=i+1;
                       continue;
                   }
                   else
                   {
                      if(i==0)
                          index=0;
                      else
                          index=i;
                   }
                }
                root->keys.insert(root->keys.begin()+index,a);
                root->child.push_back(NULL);
                int median=3/2;
                node *temp=new node;
                temp->keys.push_back(root->keys[median]);
                temp->child.push_back(NULL);
                temp->child.push_back(NULL);
                temp->isleaf=0;
                node *temp2=new node;
                node *temp3=new node;
                for(int i=0;i<median;i++)
                {
                    temp2->keys.push_back(root->keys[i]);
                    if(temp2->keys.size()==1)
                    {
                        temp2->child.push_back(NULL);
                        temp2->child.push_back(NULL);
                    }
                    else
                        temp2->child.push_back(NULL);
                }
                for(int i=median+1;i<3;i++)
                {
                    temp3->keys.push_back(root->keys[i]);
                    if(temp2->keys.size()==1)
                    {
                        temp3->child.push_back(NULL);
                        temp3->child.push_back(NULL);
                    }
                    else
                        temp3->child.push_back(NULL);
                }
                temp2->isleaf=temp3->isleaf=1;
                temp->child[0]=temp2;
                temp->child[1]=temp3;
                root=temp;
            }
        }
        else
        {
            int index;
            for(int i=0;i<root->keys.size();i++)
            {
                if(a.name.compare(root->keys[i].name)>=0)
                {
                    index=i+1;
                    continue;
                }
                else
                {
                    if(i==0)
                        index=0;
                    else
                        index=i;
                }
            }
            Insert_directory(root->child[index],a);
        }
    }
}
int height(node *root)
{
    if(root==NULL)
        return -1;
    else
        return 1+height(root->child[0]);
}
void printlevel(node *root,int level)
{
    if(root==NULL)
        return;
    if(level==1)
    {
        for(int i=0;i<root->keys.size();i++)
        {
            cout<<root->keys[i].name<<" : "<<root->keys[i].phno<<" / ";
        }
        cout<<"          ";
    }
    else
    {
        for(int i=0;i<root->child.size();i++)
        {
           printlevel(root->child[i],level-1);
        }
    }
}
void levelorder(node *root)
{
    int h=height(root);
    for(int i=1;i<=h+1;i++)
    {
       printlevel(root,i);
       cout<<endl;
    }
}
Phonenode search_data(node * root,string key)
{
    if(root!=NULL)
    {
        int index;
        for(int i=0;i<root->keys.size();i++)
        {
            if(key==root->keys[i].name)
                return root->keys[i];
            else
            {
                if(key.compare(root->keys[i].name)>0)
                    index=i+1;
                else
                {
                    index=i;
                }
            }
        }
        return search_data(root->child[index],key);
    }
    else
    {
        Phonenode a;
        a.name=a.phno="";
        return a;
    }
}
node * search_ptr(node *root,string key)
{
    if(root!=NULL)
    {
        int index;
        for(int i=0;i<root->keys.size();i++)
        {
            if(key==root->keys[i].name)
                return root;
            else
            {
                if(key.compare(root->keys[i].name)>0)
                    index=i+1;
                else
                {
                    index=i;
                }
            }
        }
        return search_ptr(root->child[index],key);
    }
    else
        return NULL;
}
void Modify(node *&root,string key)
{
    int choice;
    string name,phno;
    node *ptr=root;
    node * temp1=search_ptr(root,key);
    if(temp1==NULL)
    {
        cout<<"There is no data under the name : "<<key<<"and hence modification cannot be performed:\n";
        return;
    }
    cout<<"Enter the section to be modified:\n1.name\n2.phno\n";
    cin>>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice)
    {
    case 1:
        cout<<"Enter the new name:\n";
        getline(cin,name);
        for(int i=0;i<temp1->keys.size();i++)
        {
           if(key==temp1->keys[i].name)
              temp1->keys[i].name=name;
        }
        break;
    case 2:
        cout<<"Enter the new phno:\n";
        getline(cin,phno);
        for(int i=0;i<temp1->keys.size();i++)
        {
           if(key==temp1->keys[i].name)
              temp1->keys[i].phno=phno;
        }
        break;
    default:
        cout<<"Enter a valid option:\n";
    }
}
bool isempty(Phonenode a)
{
    if(a.name=="" && a.phno=="")
        return 1;
    else
        return 0;
}
