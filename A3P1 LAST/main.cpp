#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

struct student
{
    char id[9];
    char name[49];
    char address[49];
};
struct index
{
    char PK[9];
    int offset;
};

struct node
{
    index itree;
    node *left;
    node *right;

};
node *root;
ostream&operator<<(ostream &ou,student &s)
{
    ou<< "ID : " <<s.id<<endl;
    ou<<"Name : "<<s.name<<endl;
    ou<<"Address : "<<s.address<<endl;
    return ou;
}
istream&operator>>(istream &in,student &s)
{
    cout<<"Enter your ID : " ;
    in.getline(s.id,9);
    cout<<endl<<"Enter your name : ";
    in.getline(s.name,49);
    cout<<endl<<"Enter your address : ";
    in.getline(s.address,49);
    return in;
}
node* CreateNode(index x)
{
      struct node *n=(struct node*)malloc(sizeof(struct node));
       n->itree.offset=x.offset;
       strcpy(n->itree.PK,x.PK);
       n->left=n->right=NULL;
       return n;
}

void inorder(node *root)
{
    if(root==NULL)
        return;
    else
        {
            inorder(root->left);
            cout<<root->itree.PK<<" ";
            inorder(root->right);
        }
}
node* InsertTree(node *n,index i)
{
    if(n==NULL)
    {
       return CreateNode(i);
    }
    else
    {
        if(atoi(n->itree.PK)>atoi(i.PK))
        {
            n->left=InsertTree(n->left,i);
        }
        else if(atoi(n->itree.PK)<atoi(i.PK))
        {
            n->right=InsertTree(n->right,i);
        }
    }
    root=n;
    return n;
}

int BinarySearchTree(node *temp,char id[])
{
    temp=root;
    while (temp!= NULL)
    {
        if(temp==NULL||strcmp(temp->itree.PK,id)==0)
        {
            return temp->itree.offset;
        }
        else if(strcmp(temp->itree.PK,id)>0)
        {
            BinarySearchTree(temp->left,id);
        }
        else
        {
            BinarySearchTree(temp->right,id);
        }
    }
        return -1;
}

bool IsNull(node *n)
{
    if(n==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void saveindex(fstream &file,node *n)
{
    file.open("PrimaryIndex.txt",ios::in|ios::out);
    file.seekp(0,ios::end);
    if(IsNull(n))
    {
        return;
    }
    else
    {
    file<<n->itree.PK<<"|"<<n->itree.offset<<endl;
    file.write((char*)&n->itree.offset,sizeof(n->itree.offset));
    saveindex(file,n->right);
    saveindex(file,n->left);
    }
    root=n;
}
void deleteindex(char id[])
{
    node* n;
    int offs;
    offs=BinarySearchTree(n,id);
    if (offs==-1)
    {
        cout<<"ID not found"<<endl;
    }
    else
        {
            fstream file;
            file.open("Student.txt",ios::in|ios::out);
            file.seekp(offs,ios::beg);
            file.put('*');
            file.close();
        }
}

node* InsertFile(fstream &file)
{
    file.open("Student.txt",ios::in|ios::out);
    student s;
    index i;
    cin>>s;
    strcpy(i.PK,s.id);
    char *buffer=new char[130];
    strcpy(buffer,s.id);
    strcat(buffer,"|");
    strcat(buffer,s.name);
    strcat(buffer,"|");
    strcat(buffer,s.address);
    strcat(buffer,"|");
    short len=strlen(buffer);
    file.seekp(0,ios::end);
    i.offset=file.tellp();
    //node*n=NULL;
    root=InsertTree(root,i);
    file.write((char*)&len,sizeof(len));
    file.write(buffer,len);
    file.close();
    delete buffer;
    return root;
}
void Display(char id[])
{
    fstream file;
    int offs;
    student s;
    offs=BinarySearchTree(root,id);
    if(offs!=-1)
    {
        file.open("Student.txt",ios::in|ios::out);
        file.seekg(offs,ios::beg);
        file.read((char*)&s,sizeof(s));
        cout<<s.id<<"  PK  "<<endl<<s.name<<"   name "<<endl<<s.address<<"  address "<<endl;
    }
    return;
}

int main()
{
    index in,in1,in2;
    strcpy(in.PK,"1");
    fstream file;
    CreateNode(in);
    CreateNode(in1);
    CreateNode(in2);
    InsertFile(file);
    InsertFile(file);
    InsertFile(file);
    deleteindex("1");
    InsertTree(root,in);
    saveindex(file,root);
    inorder(root);
    return 0;
}
