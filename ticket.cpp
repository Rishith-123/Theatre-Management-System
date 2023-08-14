#include <bits/stdc++.h>
#include<fstream>
#include <sstream>
#include "user.cpp"
#include "admin.cpp"
using namespace std;

string access_type,username;
string bookings;
int seatsquan;
string tickets[10];
int tickcheck;

string usertemp,sttemp,seattemp;
int midtemp;

ofstream file;
ifstream fp;

class leftistree{
		struct node{
		int id;
		node *left;
		node *right;
		string show_time;
		string seats[8][8];
		int booked;
		int npl;
		node(int &ele,string show_time){
			id=ele;
			npl=0;
			this->show_time=show_time;
			string alp="ABCDEFGH";
			
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					string s="";
					s=s+alp[i];
					stringstream ss;
					ss << j ;
					string str ;
					ss >> str;
					s=s+str;
					seats[i][j]=s;
				}
			}
			left=right=NULL;
		}
	};
	private:
	node* root;
	
	bool isempty()const{
		return root==NULL;
	}
	void display(node *t){
		if(t!=NULL){
			display(t->left);
			cout<<"\n\t\t\t\t\t            Movie ID:   "<<t->id<<endl;
			cout<<"\t\t\t\t\t            Show Time: "<<t->show_time<<endl;
			
			seatsquan=0;
			fp.open("bookings.txt",ios::in);
			while(!fp.eof()){
				fp>>usertemp>>midtemp>>sttemp>>seattemp;
				if(t->id==midtemp && t->show_time==sttemp){
					tickets[seatsquan++]=seattemp;
				}
			}
			fp.close();
			for(int i=0;i<8;i++){
				cout<<"\t\t\t\t\t";
				for(int j=0;j<8;j++){
					tickcheck=0;
					for(int k=0;k<seatsquan;k++){
						if(t->seats[i][j]==tickets[k]){
							cout<<"x\t";
							tickcheck=1;
							break;
						}
					}
					if(tickcheck==0) cout<<"["<<t->seats[i][j]<<"]"<<"\t";
				}
				cout<<endl<<endl;
			}
			display(t->right);
		}	
	}
	
	node* merge(node *h1,node *h2){
		if(h1==NULL)
			return h2;
		if(h2==NULL)
			return h1;
		if(h1->show_time<h2->show_time){
			return merge1(h1,h2);
		}
		else{
			return merge1(h2,h1);
		}
	}
	
	node* merge1(node *h1,node *h2){
		if(h1->left==NULL)
				h1->left=h2;
		else{
			h1->right=merge(h1->right,h2);
			if(h1->left->npl<h1->right->npl)
				swapchildren(h1);
			h1->npl=h1->right->npl+1;
		}
		return h1;
	}
	
	void swapchildren(node *t){
		node *temp=t->left;
		t->left=t->right;
		t->right=temp;
	}
	
	void show(node *t,int mid){
		if(t!=NULL){
			
			if(t->id==mid){
				cout<<"\t\t\t\t\t\t\t      "<<t->show_time<<endl;
			}
			
			show(t->left,mid);
			
			show(t->right,mid);
		}
	}
	
	void indivishow(node *t,int mid,string st){
		if(t!=NULL){
			
			if(t->id==mid && t->show_time==st){
				for(int i=0;i<8;i++){
					cout<<"\t\t\t\t\t";
					for(int j=0;j<8;j++){
						tickcheck=0;
						for(int k=0;k<seatsquan;k++){
							if(t->seats[i][j]==tickets[k]){
								cout<<"x\t";
								tickcheck=1;
								break;
							}
						}
						if(tickcheck==0) cout<<"["<<t->seats[i][j]<<"]"<<"\t";
					}
					cout<<endl<<endl;
				}
				return;
			}
			
			indivishow(t->left,mid,st);
			
			indivishow(t->right,mid,st);
		}
	}
	
	void Print(node *&t){
	    if(t!=NULL){
	        Print(t->left);
	        
			fstream fp;
			fp.open("shows.txt",ios::app);
			fp<<t->id<<"\t"<<t->show_time<<"\n";
			Print(t->right);
	    }
	}
	
	public:
		leftistree(){
			root=NULL;
		}
		void Insert(int &x,string st){
			root=merge(new node(x,st),root);
		}
		void Deletemin(){
			if(isempty()){
				cout<<"\n\t\t\t\t\t            No shows are inserted yet\n";
			}
			else{
				node *newnode=root;
				root=merge(root->left,root->right);
				delete newnode;
			}
		}
//		T& findmin()const{
//			if(!isempty()){
//				return root->element;
//			}
//		}
		void Display(){
			display(root);
		}
		
		void show(int mid){
			show(root,mid);
		}
		
		void indivishow(int mid,string st){
			indivishow(root,mid,st);
		}
		
		void Print(){
            Print(root);
        }
};

void adminline(){
	cout<<"\n\t--------------------------------------------**!!ADMIN ONLY!!**-----------------------------------------------\n\n";
}

void userline(){
	cout<<"\n\t--------------------------------------------**!!USER ONLY!!**-----------------------------------------------\n\n";
}

void designup()
{
	cout<<"\n\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	cout<<"\n\t:::::::::::::::::::::::                                                      ::::::::::::::::::::::::::";
	cout<<"\n\t            		       ";
	
}
void designdown()
{
	cout<<"\t:::::::::::::::::::::::                                                      ::::::::::::::::::::::::::";
	cout<<"\n\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::::::";
	cout<<"\n\n";
}


void startPage()
{
	cout<<endl<<ifstream("startPage.txt").rdbuf();
}

void endPage()
{
	cout<<endl<<ifstream("exitPage.txt").rdbuf();
}

int main(){
	//object creation
	leftistree obj;  splay_tree splobj;  avl_tree avlobj;
	
	int n=1,a,x,furtherbook=1;
	
	int mid,nooftick,id=1000,add=1000,duration,count,check,flag;
	
	string admin_verify;
	int admin_pass;
	
	string st,movie,genre;
	
	
	
	string pl,nam,unm,ps;
    long long pho;
    int ag,uid;
    
    //fetching user details from file to avl tree - start
    fp.open("udetails.txt",ios::in);
    while(!fp.eof()){
		fp>>unm>>ps>>uid>>nam>>ag>>pho>>pl;
		if(!fp.eof()){
			mpavl[unm]++;
			avlobj.Insert(uid,nam,ag,pho,pl,unm,ps);
			adduser++;
		}
	}
	fp.close();
	//fetching user details from file to avl tree - end
	
	//Fetching movies to splay tree from file - start
	fp.open("mdetails.txt",ios::in);
	
	while(!fp.eof()){
    	fp>>id>>movie>>duration>>genre;
		if(!fp.eof()){
		mpsplay[movie]++;
		splobj.Insert(id,movie,duration,genre);
		if(add<id) add=id;
		}
 	}
	
	fp.close();
	//Fetching movies to splay tree from file - end
	
	id=++add;
	
	//fetching show details to leftist tree from file - start
	fp.open("shows.txt",ios::in);
	if(fp) {
      while(!fp.eof()){
		fp>>mid>>st;
		if(!fp.eof()){
			obj.Insert(mid,st);
		}
		}
   } 
   fp.close();
   //fetching show details to leftist tree from file - end
	
	//infinite loop
	while(1){
		
		//admin or user login
		startPage();
		cout<<"\t\t\t\t\t*****Please specify the selection***** \n\n\t\t\t\t\t\t\t[A]Admin\n \t\t\t\t\t\t\t[B]User\n \t\t\t\t\t\t\t[C]Exit\n"<<endl;
		cout<<"\t\t\t\t\t     Enter Your Selection: ";
	
		cin>>access_type;
		cout<<endl;
		
		//if the access is of admin's
		if(access_type=="Admin"){
			adminline();
			n=1;
			
			cout<<"\t\t\t\t\t     Enter username[Admin]: ";
			cin>>admin_verify;
			if(admin_verify==a_username){
				cout<<"\t\t\t\t\t     Enter password[Admin]: ";
				cin>>admin_pass;
				if(admin_pass==a_pw){
					system("CLS");
					designup();
					cout<<"\t\t    !!WELCOME ADMIN!!\n";
					designdown();
				} 
					
				else{
					cout<<"\n\t\t\t\t\t            :( Password Incorrect ):\n\n";
					continue;
				}
			}
			else{
				cout<<"\n\t\t\t\t\t            :( Admin name incorrect ):\n";
				continue;
			}
			while(n){
				cout<<"\t\t\t\t\t\t     ***************\n";
				cout<<"\t\t\t\t\t\t    *               * \n";
				cout<<"\t\t\t\t\t\t    *      MENU     * \n";
				cout<<"\t\t\t\t\t\t    *               *\n";
				cout<<"\t\t\t\t\t\t     ***************\n\n";
				cout<<"\t\t\t\t\t\t      <1> Add Movies\n"<<
				      "\t\t\t\t\t\t      <2> Edit or Delete Movies\n"<<
					  "\t\t\t\t\t\t      <3> Insert new shows\n"<<
					  "\t\t\t\t\t\t      <4> Delete shows\n"<<
					  "\t\t\t\t\t\t      <5> Display\n"<<
					  "\t\t\t\t\t\t      <6> Log-out\n";
				cout<<"\n\n\t\t\t\t\t\t      Enter your choice: ";	  
				cin>>a;
				switch(a){
					
					case 1: //splay
						cout<<"\n\n\t\t\t\t\t\t      Enter the movie name: ";
		    			cin>>movie;
		    			cout<<"\t\t\t\t\t\t      Enter the duration:";
		    			cin>>duration;
		    			cout<<"\t\t\t\t\t\t      Enter genre:";
		    			cin>>genre;
		    			
		    			check=1;
		    			
						count=mpsplay.size();
						for(int i=0;i<count;i++){
							if(mpsplay.find(movie)!=mpsplay.end()){
								cout<<"\n\n\t\t\t\t\t\t      *!!Movie already inserted!!*\n\n";
								check=0;
								break;
							}
						}
						if(check){
							cout<<"\n\n\t\t\t\t\t\t      :) Movie inserted (:\n\n";
							splobj.Insert(id,movie,duration,genre);
							mpsplay[movie]++;
							id++;
							break;
						}
						break;
					
					case 2:
						splobj.display();
						cout<<"\n\n\t\t\t\t\t\t      Enter the movie id to be edited/deleted:";
						cin>>id;
						splobj.edit_del(id);
						break;
					
					case 3:
						splobj.display();
						cout<<"\n\n\t\t\t\t\t\t      Enter the movie id: ";
						cin>>mid;
						cout<<"\t\t\t\t\t\t      Enter the show timings: ";
						cin>>st;
						obj.Insert(mid,st);
						cout<<"\n\t\t\t\t\t\t      :) Show Timing has been added successfully (:\n\n";
						file.open("shows.txt", ios::app);
						file<<mid<<"\t"<<st<<"\t"<<"\n";
						file.close();
						
						break;
					case 4:
						obj.Deletemin();
						//DELETEMIN NOT WORKING//
						cout<<"\n\t\t\t\t\t\t      :) Show Timing has been deleted successfully (:\n\n";
						break;
					case 5:
						obj.Display();
						break;	
					default:
						access_type="";
						n=0;
						system("CLS");
						//ADD FLUSH//
						break;
				}
			}
		}
		
		//if the access type is of user's
		else if(access_type=="User"){
			n=1;
			userline();
			while(n){
				if(username==""){
					cout<<"\n";
					cout<<"\t\t\t\t\t\t     ***************\n";
					cout<<"\t\t\t\t\t\t    *               * \n";
					cout<<"\t\t\t\t\t\t    *      MENU     * \n";
					cout<<"\t\t\t\t\t\t    *               *\n";
					cout<<"\t\t\t\t\t\t     ***************\n";
					cout<<"\n\t\t\t\t\t\t      <1> Register\n"<<
					      "\t\t\t\t\t\t      <2> Login\n";
					cout<<"\n\t\t\t\t\t\t      Enter your choice: ";
					cin>>a;
				}
				else if(username==unm){
					cout<<"\n";
					cout<<"\t\t\t\t\t\t     ***************\n";
					cout<<"\t\t\t\t\t\t    *               * \n";
					cout<<"\t\t\t\t\t\t    *      MENU     * \n";
					cout<<"\t\t\t\t\t\t    *               *\n";
					cout<<"\t\t\t\t\t\t     ***************\n";
					cout<<"\t\t\t\t\t\t      <1> View or Edit Details\n"<<
						  "\t\t\t\t\t\t      <2> Book Tickets\n"<<
						  "\t\t\t\t\t\t      <3> Log-out\n";
					cout<<"\n\t\t\t\t\t\t      Enter your choice: ";
					cin>>a;
					a=a+2;
				}
				switch(a){
					case 1:
						
						flag=0;
						cout<<"\n\t\t\t\t\t\t      Enter Username : ";
						cin>>unm;
						
						count=mpavl.size();
						for(int i=0;i<count;i++){
							if(mpavl.find(unm)!=mpavl.end()){
								cout<<"\n\t\t\t\t\t\t      ): Username already exist ):\n";
								flag=1;
								break;
							}
						}
						if(flag==0){
				    		cout<<"\t\t\t\t\t\t      Enter the password: ";
				    		cin>>ps;
							cout<<"\n\t\t\t\t\t\t      Enter the name: ";
							cin>>nam;
							cout<<"\t\t\t\t\t\t      Enter the age: ";
							cin>>ag;
							cout<<"\t\t\t\t\t\t      Enter the phone: ";
							cin>>pho;
							cout<<"\t\t\t\t\t\t      Enter the place: ";
							cin>>pl;
							avlobj.Insert(adduser,nam,ag,pho,pl,unm,ps);
							mpavl[unm]++;
							
							cout<<"\n\t\t\t\t\t\t      :) User has been created successfully (:\n";
							cout<<"\t\t\t\t\t\t         Your Id is: "<<adduser<<"\n\n";
							
							adduser++;
							system("CLS");
							
						}
				        break;
				    
				    case 2:
				    	flag=0;
						cout<<"\n\t\t\t\t\t\t      Enter Username : ";
						cin>>unm;
						cout<<"\t\t\t\t\t\t      Enter the password: ";
						cin>>ps;
						count=mpavl.size();
						for(int i=0;i<count;i++){
							if(mpavl.find(unm)!=mpavl.end()){
								flag=1;
								break;
							}
						}
						if(flag==0){
				    		cout<<"\n\t\t\t\t\t\t      :( Username not available! ): \n\n";
							
						}
						
						else{
							username=unm;
							system("CLS");
							designup();
							cout<<"\t\t    !!WELCOME "<<username<<"!!\n";
						
							designdown();
						}
				        break;
				    
				    case 3:
				    	avlobj.customer_dashboard();
						break;
						
					
					case 4:
						
						splobj.display();
						
						cout<<"\n\t\t\t\t\t\t      Enter the movie id:";
						
						cin>>mid;
						cout<<"\n\t\t\t\t\t\t      Available Show Timings are:\n";
						obj.show(mid);
						cout<<"\n\t\t\t\t\t\t      Enter the show timings:";
						cin>>st;
						
						
						//for file opening
						seatsquan=0;
						fp.open("bookings.txt",ios::in);
						while(!fp.eof()){
							fp>>usertemp>>midtemp>>sttemp>>seattemp;
							if(mid==midtemp && st==sttemp){
								tickets[seatsquan++]=seattemp;
							}
						}
						fp.close();
						cout<<"\n\t\t\t\t      --------------------------------------------------------------";
						cout<<"\n\t\t\t\t                                SCREEN                              ";
						cout<<"\n\t\t\t\t      --------------------------------------------------------------\n";
						obj.indivishow(mid,st);
						
						cout<<"\n\t\t\t\t\t\t      Do you want to book tickets?(1/0): ";
						cin>>furtherbook;
						if(furtherbook==0) break;
						
						cout<<"\n\t\t\t\t\t\t      Cost of each Ticket: Rs. 200/-\n";
						
						cout<<"\n\t\t\t\t\t\t      Enter the number of tickets:";
						cin>>nooftick;
						
						file.open("bookings.txt", ios::app);

						cout<<"\n\t\t\t\t\t\t      Enter the seat numbers:";
						for(int k=0;k<nooftick;k++){
							cin>>tickets[k];
							file<<unm<<"\t"<<mid<<"\t"<<st<<"\t"<<tickets[k]<<"\n";
						}
						file.close();
						
						//ticket display
						
						cout<<"\n\n\t\t\t ________________________________________________________________________\n";
						cout<<"\t\t\t|                                                                       |\n";
						cout<<"\t\t\t|   Dear Customer,                                                      |\n";
						cout<<"\t\t\t|                      Congratulation!! Your tickets has been booked.   |\n";
						cout<<"\t\t\t|                                                                       |\n";
						cout<<"\t\t\t|                  THE DETAILS:                                         |\n";
						cout<<"\t\t\t|                            MOVIE NAME: "<<mid<<"                           |\n";
						cout<<"\t\t\t|                            COST      : Rs. "<<nooftick*200<<"/-                      |\n";
						cout<<"\t\t\t|                            SHOW STARTS:"<<st<<"                        |\n";
						cout<<"\t\t\t|                            NUMBER OF TICKETS BOOKED: "<<nooftick<<"                |\n";
						cout<<"\t\t\t|                            THE SEAT NUMBERS ARE: ";
											for(int i=0;i<nooftick;i++) cout<<tickets[i]<<"  ";
						                                                          
						cout<<"             |\n";
						cout<<"\t\t\t|                                                     QR CODE           |\n";
						cout<<"\t\t\t|                                                       ..++>>>         |\n";
						cout<<"\t\t\t|                                                       ..__***         |\n";
						cout<<"\t\t\t|                                                       &%^>>>>         |\n";
						cout<<"\t\t\t|                                                       :::::::         |\n";
						cout<<"\t\t\t|_______________________________________________________________________|\n";
						
						
						break;	
					default:
						access_type="";
						n=0;
						unm="";
						system("CLS");
						cout<<"\n";
						break;
				}
			}
			
		}
		
		else if(access_type=="Exit") {
			system("CLS");
			endPage();
			//thank you visit again
			
			break;
		}
	}
	
	//for updating the movie details in the files
	file.open("mdetails.txt",ios::out | ios::trunc);
	splobj.Print();
	file.close();
	
	file.open("shows.txt",ios::out | ios::trunc);
	obj.Print();
	file.close();
	return 0;
}
