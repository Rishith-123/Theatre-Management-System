//AVL Tree

#include <bits/stdc++.h>
#include<fstream>

using namespace std;
map<string,int> mpavl;
int tmp;
static int adduser =1000;
class avl_tree{
    struct node{
        string uname;
        string password;
        int id;
        string name;
        int age;
        long long phone;
        string place;
        node *left;
        node *right;
        int height;
        node(int i,string n,int a,long long ph,string p,string un,string pw){
		id=i;
		name=n;
		age=a;
		phone=ph;
		place=p;
		uname=un;
		password=pw;
		left=NULL;
		right=NULL;
		height=-1;
		}
    };

    node *root=NULL;
    int Findmin(node *&t);
    int Height(node *t);
    void Print(node *t);
    void Insert(node *&t,int i,string n,int a,long long ph,string p,string un,string pw);
    void Delete(node *&t,int i);
    void Balance(node *&t);
    void single_rotate_left(node *&t);
    void single_rotate_right(node *&t);
    void double_rotate_left(node *&t);
    void double_rotate_right(node *&t);
    void customer_details();


    public:
        void Insert(int i,string n,int a,long long ph,string p,string un,string pw){
            Insert(root,i,n,a,ph,p,un,pw);
        }
		void Print(){
            Print(root);
        }

        avl_tree(){
            root=NULL;
        }
        
        void customer_dashboard(){
			customer_details();
		}
		
	    int search_user(node *&t,string u,string p){
			if(t != NULL){
				if(t->uname == u && t->password == p){
					tmp = t->id;
					return 1;
				}
				search_user(t->left,u,p);
				search_user(t->right,u,p);
			}
		}
		
		void search(node *&t,string u,string p){
			if(t != NULL){
				if(t->uname == u && t->password == p){
					cout<<"\n\t\t\t\t\t\t      ~~~Your Details~~~ "<<endl;
					cout<<"\n\t\t\t\t\t\t      Id : "<<t->id<<endl;
					cout<<"\t\t\t\t\t\t      Name : "<<t->name<<endl;
					cout<<"\t\t\t\t\t\t      Age: "<<t->age<<endl;
					cout<<"\t\t\t\t\t\t      Place: "<<t->place<<endl;
					cout<<"\t\t\t\t\t\t      Phone: "<<t->phone<<endl;
					cout<<endl;
				}
				search(t->left,u,p);
				search(t->right,u,p);
			}
	   }
	   
	void edit_user(node *&t,string u,string p){
		if(t!=NULL){
			if(t->uname == u && t->password == p){
				int op = 1,a;
				string u_nme,p_nme;
				while(op == 1){
					cout<<"\n\t\t\t\t\t\t      [1] Edit Username"<<endl;
					cout<<"\t\t\t\t\t\t      [2] Edit Password"<<endl;
					cout<<"\t\t\t\t\t\t      [3] Go Back"<<endl;
					cout<<"\t\t\t\t\t\t      Enter your Choice: ";
					cin>>a;
					switch(a){
						case 1:
							cout<<"\n\t\t\t\t\t\t      Enter Your new Username:"<<endl;
							cin>>u_nme;
							t->uname = u_nme;
							cout<<"\n\t\t\t\t\t\t      :) Usename Updated (:\n";
							break;
						case 2:
							cout<<"\n\t\t\t\t\t\t      Enter the new Password:"<<endl;
							cin>>p_nme;
							t->password = p_nme;
							cout<<"\n\t\t\t\t\t\t      :) Password Updated (:\n";
							break;
						
						case 3:
							op = 0;
		                    customer_details();
					}
				}
			}
			edit_user(t->left,u,p);
			edit_user(t->right,u,p);
		}
	}
};

int avl_tree::Height(node *t){
    return (t==NULL ? -1 : t->height);
}
int avl_tree::Findmin(node *&t){
    if(t==NULL)
        return 0;

    else if(t->left==NULL){
        return t->id;
    }

    else{
       return Findmin(t->left);
    }
}


void avl_tree::Insert(node *&t,int i,string n,int a,long long ph,string p,string un,string pw){
    if(t==NULL){
        t=new node(i,n,a,ph,p,un,pw);
    }

    else if(i<t->id){
        Insert(t->left,i,n,a,ph,p,un,pw);
        if(Height(t->left)-Height(t->right)==2){
            if(i<t->left->id){
                single_rotate_left(t);
            }

            else{
                double_rotate_left(t);
            }
        }
    }

    else if(i>t->id){
        Insert(t->right,i,n,a,ph,p,un,pw);
        if(Height(t->right)-Height(t->left)==2){
            if(i>t->right->id){
                single_rotate_right(t);
            }

            else{
                double_rotate_right(t);
            }
        }
    }

    else{
        //cout<<"Duplicates not allowed"<<endl;
        return ;
    }

    t->height=max(Height(t->left),Height(t->right))+1;
}

void avl_tree::single_rotate_left(node *&k2){
    node *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;

    k2->height=max(Height(k2->left),Height(k2->left))+1;
    k1->height=max(Height(k1->left),Height(k1->right))+1;

    k2=k1;
}


void avl_tree::single_rotate_right(node *&k2){
    node *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    k2->height=max(Height(k2->left),Height(k2->left))+1;
    k1->height=max(Height(k1->left),Height(k1->right))+1;
    k2=k1;
}

void avl_tree::double_rotate_left(node *&k2){
    single_rotate_right(k2->left);
    single_rotate_left(k2);
}


void avl_tree::double_rotate_right(node *&k2){
    single_rotate_left(k2->right);
    single_rotate_right(k2);
}

void avl_tree::Print(node *t){
	if(t!=NULL){
		fstream fp;
		fp.open("udetails.txt",ios::app);
		fp<<t->uname<<"\t"<<t->password<<"\t"<<t->id<<"\t"<<t->name<<"\t"<<t->age<<"\t"<<t->phone<<"\t"<<t->place<<"\n";
		Print(t->left);
		Print(t->right);
	}
}

void avl_tree::Delete(node *&t,int x){
   if(t==NULL){
   	return;
   }
	else if(x<t->id){
		Delete(t->left,x);
	}
	else if(x>t->id){
		Delete(t->right,x);
	}
	else if(t->left!=NULL && t->right!=NULL){
			t->id=Findmin(t->right);
			Delete(t->right,t->id);
		}
		
	else{
		node *oldnode=t;
		t=(t->left==NULL)?t->right:t->left;
		delete oldnode;
	}
	Balance(t);
}

void avl_tree::customer_details(){
	int num;
	int cp = 1;
	string u_name, pass;
	cout<<endl;
	cout<<"\n\t\t\t\t\t\t      Enter your Username:";
	cin>>u_name;
	cout<<"\n\t\t\t\t\t\t      Enter your Password:";
	cin>>pass;
	cout<<endl;
	
	if(search_user(root,u_name,pass)){
		while(cp==1){
			cout<<"\n\t\t\t\t\t\t      [1] View Your Details "<<endl;
			cout<<"\t\t\t\t\t\t      [2] Edit Your Details "<<endl;
			cout<<"\t\t\t\t\t\t      [3] Go Back"<<endl;
			cout<<"\t\t\t\t\t\t      Enter your Choice: ";
			cin>>num;
			if(num == 1){
				search(root,u_name,pass);
			}
			
			if(num == 2){
				int m;
				char t;
				cout<<"\n\t\t\t\t\t\t      [1] Delete your account "<<endl;
				cout<<"\t\t\t\t\t\t      [2] Edit Existing account "<<endl;
				cout<<"\t\t\t\t\t\t      Enter your choice: ";
				cin>>m;
				if(m == 1){
					cout<<"\n\t\t\t\t\t\t      Do you want to delete your account permentently(Y/N) :";
					cin>>t;
					if(t == 'Y'){
						Delete(root,tmp);
						cout<<tmp<<"\n";
						cp = 0;
					}
					else{
						customer_details();
					}
				}
				else if(m == 2){
					edit_user(root,u_name,pass);
					cp=0;
				}
			}
			
			if(num == 3){
				cp = 0;
			}
	   }
	}
	
	else{
		cout<<"\n\t\t\t\t\t\t      :( Your Username or password  is incorrect :("<<endl;
		cout<<endl;
		int h;
		cout<<"\n\t\t\t\t\t\t      Press any key to continue and 0 to Go Back: ";
		cin>>h;
		if(h == 1){
			customer_details();
		}
	}
}

void avl_tree::Balance(node *&t){
	if(t==NULL){
		return;
	}
	else if(Height(t->left)-Height(t->right)==2){
		if(Height(t->left->left)>Height(t->left->right)){
			single_rotate_left(t);
		}
		else{
			double_rotate_left(t);
		}
	}
	else if(Height(t->right)-Height(t->left)==2){
		if(Height(t->right->right)>Height(t->right->left)){
			single_rotate_right(t);
		}
		else{
			double_rotate_right(t);
		}
	}
	t->height=max(Height(t->left),Height(t->right))+1;
}

