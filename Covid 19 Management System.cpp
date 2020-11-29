//     HEADER FILE USED IN PROJECT

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


//     CLASS USED IN PROJECT

class cluster
{
	int postcodeno;
	char name[50];
	
	int confirm;
	int suspect;
	int death;
	int recover;
	
public:
	void create_cluster();	//function to get data from user
	void show_cluster() const;	//function to show data on screen
	void modify();	//function to add new data
	
	void updatecase(int,int,int,int);	//function to accept amount and add to new cases 
	
	void removecase(int);	//function to accept amount and subtract from suspected cases
	void report() const;	//function to show data in tabular format
	int retpostcodeno() const;	//function to return account number
	
	int retsuspectcase() const; //functio to return suspected case
	
};         //class ends here


void cluster::create_cluster()
{
	cout<<"\nEnter The Postal Code no. Please : ";
	cin>>postcodeno;
	
	cout<<"\nEnter The name of Cluster : ";
	cin.ignore();
	cin.getline(name,50);
	
	cout<<"\n\nEnter The Suspected case : ";
	cin>>suspect;
	
	cout<<"\n\nEnter The Confirmed case :";
	cin>>confirm;
	
	cout<<"\n\nEnter The Death case :";
	cin>>death;
	
	cout<<"\n\nEnter The Recovered case :";
	cin>>recover;
	
	cout<<"\n\n\nCluster Created..";
}


void cluster::show_cluster() const
{
	
	cout<<"\nCluster. : "<<name;
	
	cout<<"\n\nSuspected case : "<<suspect;
	
	
	cout<<"\n\nConfirmed case : "<<confirm;
	
		
	cout<<"\n\nDeath case : "<<death;
	
	
	cout<<"\n\nRecovered case : "<<recover;	
	
}


void cluster::modify()
{
	cout<<"\nThe name of Cluster. : "<<name;
	cout<<"\n\nEnter The Suspected case : ";
	cin>>suspect;
	
	cout<<"\n\nModify The Confirmed case : ";
	cin>>confirm;
	
	
	cout<<"\n\nModify The Death case : ";
	cin>>death;
	
	cout<<"\n\nModify The Recovered case : ";
	cin>>recover;
	
	
}


void cluster::updatecase(int susp,int conf,int dth,int rec)
{
	suspect+=susp;
	confirm+=conf;
	death+=dth;
	recover+=rec;
	
}


void cluster::removecase(int neg)
{
	
	suspect-=neg;
}
	
	
void cluster::report() const
{
	cout<<postcodeno<<setw(10)<<" "<<name<<setw(10)<<" "<<suspect<<setw(10)<<" "<<confirm<<setw(10)<<" "<<death<<setw(10)<<" "<<recover<<endl;
}

	
int cluster::retpostcodeno() const
{
	return postcodeno;
}


int cluster::retsuspectcase() const
{
	return suspect;
}



//    	function declaration

void write_cluster();	//function to write record in binary file
void display_sp(int);	//function to display cluster details given by user
void modify_cluster(int);	//function to modify record of file
void delete_cluster(int);	//function to delete record of file
void display_all();		//function to display all cluster details
void deposit_withdraw(int, int); // function to add/remove cases for given cluster
void intro();	//introductory screen function




//    	THE MAIN FUNCTION OF PROGRAM

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW CLUSTER";
		cout<<"\n\n\t02. ADD CASE";
		cout<<"\n\n\t03. REMOVE CASE";
		cout<<"\n\n\t04. CLUSTER ENQUIRY";
		cout<<"\n\n\t05. ALL CLUSTER-WISE CASE LIST";
		cout<<"\n\n\t06. REMOVE CLUSTER";
		cout<<"\n\n\t07. MODIFY CLUSTER DETAILS";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_cluster();
			break;
		case '2':
			cout<<"\n\n\tEnter The Cluster's Postal Code Please : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The Cluster's Postal Code Please : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The Cluster's Postal Code Please  : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The Cluster's Postal Code Please  : "; cin>>num;
			delete_cluster(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The Cluster's Postal Code Please  : "; cin>>num;
			modify_cluster(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using COVID19 MANAGEMENT SYSTEM";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}



//    	function to write in file

void write_cluster()
{
	cluster postcode;
	ofstream outFile;
	outFile.open("cluster.dat",ios::binary|ios::app);
	postcode.create_cluster();
	outFile.write(reinterpret_cast<char *> (&postcode), sizeof(cluster));
	outFile.close();
}


//    	function to read specific record from file

void display_sp(int n)
{
	cluster postcode;
	bool flag=false;
	ifstream inFile;
	inFile.open("cluster.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nCLUSTER DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&postcode), sizeof(cluster)))
	{
		if(postcode.retpostcodeno()==n)
		{
			postcode.show_cluster();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n Cluster does not exist";
}



//    	function to modify record of file

void modify_cluster(int n)
{
	bool found=false;
	cluster postcode;
	fstream File;
    File.open("cluster.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&postcode), sizeof(cluster));
		if(postcode.retpostcodeno()==n)
		{
			postcode.show_cluster();
			cout<<"\n\nEnter The New Details of Cluster"<<endl;
			postcode.modify();
			int pos=(-1)*static_cast<int>(sizeof(cluster));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&postcode), sizeof(cluster));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}



//    	function to delete record of file

void delete_cluster(int n)
{
	cluster postcode;
	ifstream inFile;
	ofstream outFile;
	inFile.open("cluster.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&postcode), sizeof(cluster)))
	{
		if(postcode.retpostcodeno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&postcode), sizeof(cluster));
		}
	}
    inFile.close();
	outFile.close();
	remove("cluster.dat");
	rename("Temp.dat","cluster.dat");
	cout<<"\n\n\tRecord Deleted ..";
}



//    	function to display all states deposit list

void display_all()
{
	cluster postcode;
	ifstream inFile;
	inFile.open("cluster.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tCOVID 19 AFFECTED CLUSTER LIST\n\n";
	cout<<"==========================================================================================================\n";
	cout<<"Postal Code no.      NAME         SUSPECT       CONFIRM       DEATH      RECOVER \n";
	cout<<"===========================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&postcode), sizeof(cluster)))
	{
		postcode.report();
	}
	inFile.close();
}



//    	function to add and remove cases

void deposit_withdraw(int n, int option)
{
	
	int neg;
	int susp;
	int conf;
	int dth;
	int rec;
	bool found=false;
	cluster postcode;
	fstream File;
    File.open("cluster.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&postcode), sizeof(cluster));
		if(postcode.retpostcodeno()==n)
		{
			postcode.show_cluster();
			if(option==1)
			{
				cout<<"\n\n\tTO ADD NEW POSITIVE CASES ";
				cout<<"\n\nEnter The new Suspected cases : ";
				cin>>susp;
				cout<<"\n\nEnter The new Confirmed Positive cases : ";
				cin>>conf;
				cout<<"\n\nEnter The new Death cases : ";
				cin>>dth;
				cout<<"\n\nEnter The new Recovered cases : ";
				cin>>rec;
				postcode.updatecase(susp,conf,dth,rec); //updating the new cases
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO REMOVE NEGATIVE CASES ";
								
									
				cout<<"\n\nEnter The  Confirmed Negative cases : ";
				cin>>neg;
				int balance=postcode.retsuspectcase()-neg;
				
				if(balance<0 )
				    cout<<"Improper value,Confirmed negative cases are greater than suspected case ";
				else
					postcode.removecase(neg);	
		      }
			int pos=(-1)*static_cast<int>(sizeof(postcode));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&postcode), sizeof(cluster));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}




//    	INTRODUCTION FUNCTION

void intro()
{
	cout<<"\n\n\n\t\t\t\tWELCOME \n\n\n\t\t\t\t  TO";
	cout<<"\n\n\n\t\t\tCOVID19 MANAGEMENT SYSTEM";
	cout<<"\n\n\n\nMADE BY    : Ahmed Nafiz";
	cout<<"\n\nUniversity : Bangladesh Army University of Science and Technology";
	cin.get();
}

//    			END OF PROJECT

