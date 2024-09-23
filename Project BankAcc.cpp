#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

void createfiles(){ // function to create files before making accounts or searching. It makes sure that file exists before running the program
	fstream makefiles, makefilec;
	makefiles.open("Savings.txt", ios::app | ios::binary);
	makefilec.open("Checkings.txt", ios::app | ios::binary);
	makefiles.close();
	makefilec.close();
}

void space(){//just used for ending a line
	cout<<"                                            "<<endl;
}


void homepage(){//homepage of the program
			system("cls");
			cout<<"====================================================================="<<endl;
			cout<<"Welcome to the bank software"<<endl;
			cout<<"====================================================================="<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"Choose command to execute                                            "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"1. Make account                                                      "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"2. Display all account holders                                       "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"3. savings Account                                                   "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"4. checkings Account                                                 "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"5. Exit                                                              "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"Your command(1-5):";
		}
		
void specificuser(){//after user search
			cout<<"                                                                     "<<endl;
			cout<<"Choose command to execute                                            "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"1. Display Analytics                                                 "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"2. Withdraw money                                                    "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"3. Deposit money                                                     "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"4. Reset month for user                                              "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"5. Update and go back                                                "<<endl;
			cout<<"                                                                     "<<endl;
			cout<<"Your command(1-5):";
	   	    
	   }
	   
	   
	   
	   
		

class genericAccount{
	protected:
		//userinformation
		char Firstname[50] ,Lastname[50];
	    int phonenumber, UserId;
		//The varaibles for bank transaction
		double Balance,Annualinterestrate, Monthlyservicecharge, beginning_balance;
		int withdrawnum, depositnum;
		bool Accountstatus;
		
	public:
		 void setuserInfo(char *f, char *l, int phn, int uID, double b, double aiR, double Msc=0, double BegBal=0, int withnum=0, int depnum=0, bool As=true){
	    	strcpy(Firstname, f);
	    	strcpy(Lastname, l);
	    	phonenumber=phn;
	    	UserId=uID;
	    	Balance=b;
	    	Annualinterestrate=0.8;
	    	beginning_balance=BegBal;
	    	withdrawnum=0;
	    	depositnum=0;
	    	Accountstatus=true;
			}
	    
	     char* getFname(){//return first name of user
	     	return Firstname;
		 }	
		 
		 char* getLname(){//return last name of user
		 	return Lastname;
		 }
		 
		 int getUID(){//returns UID of user
		 	return UserId;
		 }
	     
	     //I have moved bool status to base class in order to use it in checkings class as well
		 bool status(){//checks if status of account is true or false 
			if (Balance<25){
				Accountstatus=false;
			}
			else{
				Accountstatus=true;
			}
		  }	
	    		
		 void display(){
			//displays some information when called
			cout<<"================================"<<endl;
			cout<<"first name          :"<<Firstname<<endl;
			cout<<"last name           :"<<Lastname<<endl;
			cout<<"UserId              :"<<UserId<<endl;
			cout<<"user phonenumber    :"<<phonenumber<<endl;
			cout<<"Annual interest rate:"<<Annualinterestrate<<endl;
			cout<<"Balance             :"<<Balance<<endl;
			
			if (Accountstatus==true){//instead of 0 and 1 active and inactive is returned
			cout<<"Account status:Active"<<endl;
		}else{
			cout<<"Account status:Frozen/Inactive"<<endl;
		}
			cout<<"================================"<<endl;
			
		}
		
		virtual int makeDeposit(double amountdeposit){
			Balance+=amountdeposit;
			depositnum+=1;		
		}
		virtual int makeWithdrawal(double amountwithdrawal){	
			Balance-=amountwithdrawal;
			withdrawnum+=1;
		}
		virtual double calcInt(){
			double monthlyinterestrate, monthlyinterest;
			monthlyinterestrate=(Annualinterestrate/12);
			monthlyinterest=Balance*monthlyinterestrate;
			cout<<"monthly interest            =$"<<monthlyinterest<<endl;
			Balance+=monthlyinterest;
		}
		virtual int monthlyProc(){
			cout<<"Balance before reset        =$"<<Balance<<endl;
			cout<<"Monthly service charge      =$"<<Monthlyservicecharge<<endl;
			Balance-=Monthlyservicecharge;
			cout<<"Balance After service charge=$"<<Balance<<endl;
			genericAccount::calcInt();
			cout<<"Final balance After interest=$"<<Balance<<endl;
			withdrawnum=0;
			depositnum=0;
			Monthlyservicecharge=0;
		}
		
		void setstartBal(){  //sets beginning balance of the month
	    	beginning_balance=Balance;
		}

		int analytics(){ //displays statistics when called
			cout<<"Current balance                       :$"<<Balance<<endl;
			cout<<"Balance at the beginning of the month :$"<<beginning_balance<<endl;
			cout<<"times withdrawn this month normal     :"<<withdrawnum<<endl;
			cout<<"times deposited this month            :"<<depositnum<<endl;
			if (Accountstatus==true){
			   cout<<"Account status                        :Active"<<endl;
			}else{
			   cout<<"Account status                        :Inactive"<<endl;
				
			}
			
		}
		
};




class savingsAccount : public genericAccount{

	public:
        
		int makeWithdrawal(double amountwithdrawal){//overriding virtual function
			double tempcheck=Balance-amountwithdrawal; //checks if balance is less than amount withdrawal
    	    if (Accountstatus==true && tempcheck>0 ){
    	        genericAccount::makeWithdrawal(amountwithdrawal);
			    cout<<"Transaction completed. Balance :$"<<Balance<<endl;
    	    	
    		}
		    else{
			    cout<<"transaction cannot be completed. Your account has been frozen/ set inactive. Deposit to make it active."<<endl;
			    if (tempcheck<0){
			    	cout<<"Cannot withdraw more than balance"<<endl;
				}
		   }
		   genericAccount::status();
	     }
	
	    int makeDeposit(double amountdeposit){//overriding virutal function
		    	genericAccount::makeDeposit(amountdeposit);
			    cout<<"Transaction completed. Balance :$"<<Balance<<endl;
			    genericAccount::status();
	        
    
	}
	
	    int	monthlyProc(){//overriding virtual function
		   if (withdrawnum>4){
		   	Monthlyservicecharge+=(withdrawnum-4); //$1 for every withdrawal above 4 is added to monthly service charge
		   }
		   genericAccount::monthlyProc();
		   genericAccount::setstartBal();
		   
	
		   
	}
		
	
		
	
};
class checkingsAccount: public genericAccount{
	public:
	    int makeWithdrawal(double amountwithdrawal){//overriding virtual function
	    double tempcheck2=Balance-amountwithdrawal;
	    if (Accountstatus==true){
	    	if(tempcheck2<0){
	    		Monthlyservicecharge+=15;
	    		cout<<"amount of withdrawal is greater than balance and will cause to go below 0. Withdrawal will not be made"<<endl;
	    		
			}
			else{
				genericAccount::makeWithdrawal(amountwithdrawal);
	
			    cout<<"Transaction completed. Balance :$"<<Balance<<endl;
				
			}
		}
		else{
			cout<<"Account is inactive/ frozen deposit balance to make it active again"<<endl;
		}
		genericAccount::status();
			
	    	
	    	
	    	
	    	
		
	    }
	    			 
        int monthlyProc(){//overriding virtual function
        	Monthlyservicecharge+=(5+(withdrawnum*0.10));
        	genericAccount::monthlyProc();
        	genericAccount::setstartBal();
        	
        
		}
		
		int makeDeposit(double amountdeposit){//added this function to avoid confusion during make deposit
		    	genericAccount::makeDeposit(amountdeposit);
			    cout<<"Transaction completed. Balance :$"<<Balance<<endl;
			    genericAccount::status();
			}
				
	
		
			
 	


};





int main(){
	createfiles();
	
	//used variables for taking information 
	char f[50], l[50];
	int pn, bid, wn, dn;
	double bal, aIR, msc, bbal;
	bool ac;
	
	//used objects
	savingsAccount savings;
	savingsAccount savingsup;
	checkingsAccount checkings;
	checkingsAccount checkingsup;
	//used variables for confirmations
	int button;
	int button2;
	char confirm;
	int UID;
	bool foundFlag=false;
	double amount;
	
	while(1){
		homepagearea:
		homepage();
		cin>>button;
		
		switch(button){
			case 1:{//create account 
				system("cls");
				createAccount:
				cout<<"==============================================="<<endl;
				cout<<"Create Account"<<endl;
				cout<<"==============================================="<<endl;
				
				cout<<"Enter Firstname            :";
				cin>>f;
				space();
				cout<<"Enter Lastname             :";
				cin>>l;
				space();
				cout<<"Assign ID                  :";
				cin>>bid;
				space();
				cout<<"Assign phone number        :";
				cin>>pn;
				space();
	            cout<<"Add Savings account balance:$";
	            cin>>bal;
	            space();
	            
	            savings.setuserInfo(f,l,pn,bid,bal,0.8,0,bal,0,0,true);//sets user info to protected variable
	            savings.status();//set active or inactive account of user according to balance 
	            
	            cout<<"Add checking account balance:$";
	            cin>>bal;
	            
	            checkings.setuserInfo(f,l,pn,bid,bal,0.8,0,bal,0,0,true);//same process as checking but balance is different
	            checkings.status(); //set active or inactive account of user according to balance 
	            
	            fstream savetofileS, savetofileC;
	            savetofileS.open("Savings.txt", ios::app | ios::binary);
	            savetofileC.open("Checkings.txt", ios::app | ios::binary);
	            
	            savetofileS.write(reinterpret_cast<char*>(&savings),sizeof(genericAccount));
	            savetofileC.write(reinterpret_cast<char*>(&checkings),sizeof(genericAccount));
	            
	            savetofileS.close();
	            savetofileC.close();
	            
	            cout<<"congratulations Account successfully created"<<endl;
	            space();
	            cout<<"Make another account?(y/n)";
	            cin>>confirm;
	            if (confirm=='y' or confirm=='Y'){
	            	goto createAccount;
				}
				else{
					goto homepagearea;
				}
	            
			}
			case 2:{//savings and checkings selection for display all users
				fstream lookupsavings;
				fstream lookupcheckings;
				system("cls");
				cout<<"Display all accounts: select"<<endl;
				cout<<"============================"<<endl;
				space();
				cout<<"1.Savings                   "<<endl;
				space();
				cout<<"2.Checkings                 "<<endl;
				space();
				cout<<"3.Exit to homepage          "<<endl;
				cout<<"Your command(1-3):";
				cin>>confirm;
				
				if (confirm=='1'){//reads savings file to class
					lookupsavings.open("Savings.txt", ios::in | ios::binary);
					while(lookupsavings.read(reinterpret_cast<char *>(&savings), sizeof(savings))){
						savings.display();
					    
						
					}
					lookupsavings.close();
					cout<<"go back?(y)";
					cin>>confirm;
					if (confirm=='y' or confirm=='Y'){
						goto homepagearea;
					}
					else{
						goto homepagearea;
					}
				}
				else if(confirm=='2'){//reads checkings file to class
					lookupcheckings.open("Checkings.txt", ios::in | ios::binary);
					while(lookupcheckings.read(reinterpret_cast<char *>(&checkings), sizeof(checkings))){
						
						checkings.display();
					
				}
				lookupcheckings.close();
				cout<<"go back?(y)";
					cin>>confirm;
					if (confirm=='y' or confirm=='Y'){
						goto homepagearea;
					}
					else{
						goto homepagearea;
					}
			}
			
			   else if(confirm=='3'){//else go homepage
			   	goto homepagearea;
			   }
			   else{
			   	goto homepagearea;
			   }
			
			
		}
//Beginning of nested case for saving-----------------------------------------------------------------------------------------------------------------------------------------------------------		
		case 3:{//savings load 
		    searcharea:
			cout<<"Enter BankID you want to load: ";
			cin>>UID;
			foundFlag=false;
			fstream searchsavings;
			searchsavings.open("Savings.txt", ios::in|ios::binary);
			//code for searching user in savings.txt
			while(searchsavings.read((char*)&savings, sizeof(savings))){
				
				if(savings.getUID()==UID){
					foundarea:
					system("cls");
					cout<<"========================================================================================="<<endl;
					cout<<"Account Name: "<<savings.getFname()<<" "<<savings.getLname()<<" UserID:"<<savings.getUID()<<endl;
					cout<<"========================================================================================="<<endl;
					foundFlag=true;
					
					break;
				   }
				   }
				   
				if(foundFlag==false){//goes to search or home if not found
					cout<<"UserID :"<<UID<<" doesnot exist"<<endl;
					cout<<"go back to 1.Search or 2.homepage?";
					    cin>>confirm;
					    if (confirm=='1'){
						    goto searcharea;
					}
					    else{
						    goto homepagearea;
					}
				}
				else{//nested selection for withdraw deposit monthly proc and save and exit
					specificuser();
					cin>>button2;
					//display analytics
					if (button2==1){
						savings.analytics();
						cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea;
					}
					    else{
						    goto foundarea;
					}
						
					}
					//amount withdraw
					else if(button2==2){
						cout<<"Enter amount to withdraw:$";
						cin>>amount;
						savings.savingsAccount::makeWithdrawal(amount);
						cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea;
					}
					    else{
						    goto foundarea;
					}
						
						
					}
					//amount deposit
					else if(button2==3){
						cout<<"Enter amount to deposit:$";
						cin>>amount;
						savings.savingsAccount::makeDeposit(amount);
							cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea;
					}
					    else{
						    goto foundarea;
					}
						
					}
					//reset month
					else if(button2==4){
						cout<<"Are you sure to reset the month? Service charge will be deducted and interest will be added to your account(y/n)";
						cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
					    	savings.savingsAccount::monthlyProc();
					    	cout<<"Month reset"<<endl;
					    	cout<<"go back?(y)";
					        cin>>confirm;
					        if (confirm=='y' or confirm=='Y'){
						        goto foundarea;
					}
					        else{
						        goto foundarea;
					}
					    	
					     
					
					}
					
				}
				//save and exit
				else if(button2==5){
					//write code to update and exit file.
					fstream savingsupdate;
					savingsupdate.open("Savings.txt", ios::in| ios::out | ios::binary);
					while(savingsupdate.read((char*)&savingsup, sizeof(savingsup))){
						if(savingsup.getUID()==savings.getUID()){
							savingsupdate.seekp(-sizeof(savingsup),ios::cur);
                            savingsupdate.write((char*)&savings, sizeof(savings));
							break;
						}
		
					
					
				}   
				savingsupdate.close();	
				goto homepagearea;
				
				
				
			}
			else{
				goto foundarea;
			}
				}
			}
//End of nested case for savings--------------------------------------------------------------------------------------------------------------------------------------------------------				
//Beginning of nested case for checkings------------------------------------------------------------------------------------------------------------------------------------------------				
		case 4:{//load checkings Account
		    searcharea2:
		    cout<<"Enter BankID you want to load: ";
			cin>>UID;
			foundFlag=false;
			fstream searchcheckings;
			searchcheckings.open("Checkings.txt", ios::in|ios::binary);
			while(searchcheckings.read((char*)&checkings, sizeof(checkings))){//search for user in checkings
				
				if(checkings.getUID()==UID){
					foundarea2:
					system("cls");
					cout<<"========================================================================================="<<endl;
					cout<<"Account Name: "<<checkings.getFname()<<" "<<checkings.getLname()<<" UserID:"<<checkings.getUID()<<endl;
					cout<<"========================================================================================="<<endl;
					foundFlag=true;
					
					break;
				   }
				   }
				   
				if(foundFlag==false){//go to home or search
					cout<<"UserID :"<<UID<<" doesnot exist"<<endl;
					cout<<"go back to 1.Search or 2.homepage?";
					    cin>>confirm;
					    if (confirm=='1'){
						    goto searcharea2;
					}
					    else{
						    goto homepagearea;
					}
				}
				else{//
					specificuser();
					cin>>button2;
					if (button2==1){//display analytics
						checkings.analytics();
						cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea2;
					}
					    else{
						    goto foundarea2;
					}
						
					}
					else if(button2==2){//amount to withdraw
						cout<<"Enter amount to withdraw:$";
						cin>>amount;
						checkings.checkingsAccount::makeWithdrawal(amount);
						cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea2;
					}
					    else{
						    goto foundarea2;
					}
						
						
					}
					else if(button2==3){//deposit code
						cout<<"Enter amount to deposit:$";
						cin>>amount;
						checkings.checkingsAccount::makeDeposit(amount);
							cout<<"go back?(y)";
					    cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
						    goto foundarea2;
					}
					    else{
						    goto foundarea2;
					}
						
					}
					else if(button2==4){//reset month for user
						cout<<"Are you sure to reset the month? Service charge will be deducted and interest will be added to your account(y/n)";
						cin>>confirm;
					    if (confirm=='y' or confirm=='Y'){
					    	checkings.checkingsAccount::monthlyProc();
					    	cout<<"Month reset"<<endl;
					    	cout<<"go back?(y)";
					        cin>>confirm;
					        if (confirm=='y' or confirm=='Y'){
						        goto foundarea2;
					}
					        else{
						        goto foundarea2;
					}
					    	
					     
					
					}
					
				}
				else if(button2==5){//
					//write code to update and exit file.
					fstream checkingsupdate;
					checkingsupdate.open("Checkings.txt", ios::in| ios::out | ios::binary);
					while(checkingsupdate.read((char*)&checkingsup, sizeof(checkingsup))){
						if(checkingsup.getUID()==checkings.getUID()){
							checkingsupdate.seekp(-sizeof(checkingsup),ios::cur);
                            checkingsupdate.write((char*)&checkings, sizeof(checkings));
							break;
						}
		
					
					
				}   
				checkingsupdate.close();	
				goto homepagearea;
				
					
					
					
				}
			    else{
			    	goto foundarea2;
				}   	
				
				
				
			}
		
					
		}
//end of nested case for checkings-------------------------------------------------------------------------------------------------------------------------------------------------------------------		
		
			case 5:{//exit the program
				cout<<"Shutting down"<<endl;
				exit(0);
				
				
			}	
		
			
		}
	}
	


return 0;
}




			  
	

			
  

 

