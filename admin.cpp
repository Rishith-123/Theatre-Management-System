#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

string a_username="admin";
int a_pw=2003;
map<string,int> mpsplay;

class splay_tree{
    struct node{
    	int id;
        string movie;
        int timings;
        string genre;
        node *left;
        node *right;
        node(){
            left=right=NULL;
        }
    };

    node *root;
    node *nullnode;
	void makempty(node *&t);
    void Insert(node *&t,int m,string mov,int ti,string gen);
    void Delete(node *&t,int m);
    void Print(node *&t);
    void Splay(node *&t,int &m);
    void single_rotate_left(node *&t);
    void single_rotate_right(node *&t);
    void edit_del_details(node *&t,int &m);
    void display_details(node *&t);
	int find(node *&t,string &movi);

    public:
        void Insert(int &m,string mov,int ti,string gen){
            Insert(root,m,mov,ti,gen);
        }

       void edit_del(int &i){
       		edit_del_details(root,i);
	   }
		
		
        void Print(){
            Print(root);
        }
        
        void display(){
        	display_details(root);
		}

        splay_tree(){
            nullnode=new node;
            nullnode->left=nullnode->right=NULL;
            root=nullnode;
        }

        ~splay_tree(){
            makempty(root);
            delete root;
        }

        void makempty(){
            makempty(root);
        }
        
        int id_find(string movi){
        	int mid=find(root,movi);
        	cout<<mid;
        	return mid;
		}
};

void splay_tree::display_details(node *&t){
	if(t != nullnode){
			
			cout<<"\n\n\t\t\t\t\t\t      ~~~Movie Details~~~ "<<endl;
			cout<<endl;
			cout<<"\t\t\t\t\t\t      Id : "<<t->id<<endl;
			cout<<"\t\t\t\t\t\t      Movie Name : "<<t->movie<<endl;
			cout<<"\t\t\t\t\t\t      Duration: "<<t->timings<<endl;
			cout<<"\t\t\t\t\t\t      Genre: "<<t->genre<<endl;
			cout<<endl;
			display_details(t->left);
			display_details(t->right);
	}
	
	
}

void splay_tree::Print(node *&t){
    if(t!=nullnode){
        Print(t->left);
        
		fstream fp;
		fp.open("mdetails.txt",ios::app);
		fp<<t->id<<"\t"<<t->movie<<"\t"<<t->timings<<"\t"<<t->genre<<"\n";
		Print(t->right);
    }
}

void splay_tree::makempty(node *&t){
    if(t!=NULL){
        makempty(t->left);
        makempty(t->right);
        delete t;
    }
    t=NULL;
}

void splay_tree::Splay(node *&t,int &m){
    node *ltmax,*rtmin;
    node header;
    ltmax=&header;
	rtmin=&header;

    while(m!=t->id){
        if(m<t->id){
            if(t->left==nullnode){
                break;
            }
            if(t->left->left!=nullnode && m<t->left->id){
                single_rotate_left(t);
            }

            rtmin->left=t;
            rtmin=t;
            t=t->left;
        }

        else if(m>t->id){
            if(t->right==nullnode){
                break;
            }
            if(t->right->right!=nullnode && m>t->right->id){
                single_rotate_right(t);
            }

            ltmax->right=t;
            ltmax=t;
            t=t->right;
        }
    }

    ltmax->right=t->left;
    rtmin->left=t->right;
    t->left=header.right;
    t->right=header.left;
}

void splay_tree::Insert(node *&t,int m,string mov,int ti,string gen){

    node *newnode=NULL;
    if(newnode==NULL){
        newnode=new node;
        newnode->id=m;
        newnode->movie=mov;
        newnode->timings=ti;
        newnode->genre=gen;
        newnode->left=newnode->right=nullnode;
    }

    if(root==nullnode){
        root=newnode;
        newnode->left=newnode->right=nullnode;
    }

    else{
        Splay(root,m);
        if(m<root->id){
            newnode->right=root;
            newnode->left=root->left;
            root->left=nullnode;
            root=newnode;
        }

        else if(m>root->id){
            newnode->left=root;
            newnode->right=root->right;
            root->right=nullnode;
            root=newnode;
        }
    }
    newnode=NULL;
}

void splay_tree::Delete(node *&t,int m){
    node *newtree;
    Splay(root,m);
    if(root->id!=m){
        return ;
    }

    if(root->left==nullnode){
        newtree=root->right;
        delete root;
    }

    else{
        newtree=root->left;
        Splay(newtree,m);
        newtree->right=root->right;
        delete root;
    }

    root=newtree;
}

void splay_tree::single_rotate_left(node *&k2){
    node *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;

    k2=k1;
}

void splay_tree::single_rotate_right(node *&k2){
    node *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;

    k2=k1;
}

void splay_tree::edit_del_details(node *&t,int &i){
        int op = 1,a;
		string movie,gen;
		int duration,id;
		Splay(root,i);
		if(root->id == i){
					while(op == 1){
						cout<<"\t\t\t\t\t\t     _______________\n";
						cout<<"\t\t\t\t\t\t    |               | \n";
						cout<<"\t\t\t\t\t\t    |      EDIT     | \n";
						cout<<"\t\t\t\t\t\t    |_______________|\n\n";
			            cout<<"\n\t\t\t\t\t\t      [1] Edit Movie Name"<<endl;
						cout<<"\t\t\t\t\t\t      [2] Edit Movie Duration"<<endl;
						cout<<"\t\t\t\t\t\t      [3] Edit Movie Genre"<<endl;
						cout<<"\t\t\t\t\t\t      [4] Delete Movie"<<endl;
						cout<<"\t\t\t\t\t\t      [5] Display"<<endl;
						cout<<"\t\t\t\t\t\t      [6] Go Back"<<endl;
						
						cout<<"\n\n\t\t\t\t\t\t      Enter your choice:";
						cin>>a;
						switch(a){
							case 1:
								cout<<"\n\t\t\t\t\t\t      Enter new movie name:";
								cin>>movie;
								t->movie = movie;
								cout<<"\n\t\t\t\t\t\t      :) Movie Updated (:\n";
								break;
							case 2:
								cout<<"\n\t\t\t\t\t\t      Enter new duration :";
								cin>>duration;
								t->timings = duration;
								cout<<"\n\t\t\t\t\t\t      :) Duration Updated (:\n";
								break;
							case 3:
								cout<<"\n\t\t\t\t\t\t      Enter new genre :";
								cin>>gen;
								t->genre = gen;
								cout<<"\n\t\t\t\t\t\t      :) Genre Updated (:\n";
								break;
							case 4:
								Delete(root,i);
								cout<<"\n\t\t\t\t\t\t      :) Movie has been deleted (:\n";
								break;
							case 5:
								display();
			                    break;
							case 6:
								op = 0;
			                    break;
						}
						
					}
						
		}
		
		
}

int splay_tree::find(node *&t,string &movi){
	if(movi==t->movie){
		
		return t->id;
	}
	else{
		find(t->left,movi);
		find(t->right,movi);
	}
}
