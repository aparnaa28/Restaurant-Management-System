//******************************************************************
//        PROJECT RESTAURANT MANAGEMENT
//**************************************************************

//***************************************************************
//        INCLUDE HEADER FILES
//****************************************************************

#include<fstream.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>

int m_item_no=0;
int p_item_no=0;
int p_book=0;

struct item_B
{
 int item_no;
 char description[20];
 float price;
};

struct date             //to get the date
{
 short int dd;
 short int mm;
 short int yy;
};

struct time            //to get the time
{
 short hh;
 short mm;
};

class MenuCard:private item_B      //for menu card
{
  public:
  void Getdata()
  {
       cout<<"\nItem No : ";
       cin>>item_no;
       cout<<"\nDescription: ";
       gets(description);
       cout<<"Price: ";
       cin>>price;
       cout<<endl;
	}

  void Display()
  {
       cout<<"\nItem no: "<<item_no;
       cout<<"\nDescription: "<<description;
       cout<<"\nPrice: "<<price;
  }
  int Retitem()
  {
       return item_no;
  }
  int Retprice()
  {
       return price;
  }
  void Modify();
  };
  void MenuCard::Modify()
  {
   char ch='n';
   Display();
   cout<<"\n\nDo you want to modify this item(y/n)";
   cin>>ch;
   if(ch=='y')
   {

       cout<<"\nEnter new details: \n";
       cout<<"\nDescription: ";
       gets(description);
       cout<<"Price: ";
       cin>>price;
       cout<<endl;
   }
  }

class PartyCard:private item_B            //for party card
{
  public:
  int party_code;
  PartyCard()
  {
	cout<<"\nParty Card no";
	cin>>party_code;
  }
  void Getdata()
  {
    cout<<"\nItem No: ";
       cin>>item_no;
      cout<<"\nDescription: ";
	gets(description);
       cout<<"Price: ";
       cin>>price;
       cout<<endl;
   }

   void Display()
  {
       cout<<"\nItem no: "<<item_no;
       cout<<"\nDescription: "<<description;
       cout<<"\nPrice: "<<price;
  }
  int Retitem()
  {
       return item_no;
  }
  int Retprice()
  {
       return price;
  }
  void Modify();
  };
  void PartyCard::Modify()
  {
   char ch='n';
   Display();
   cout<<"\n\nDo you want to modify this item(y/n)";
   cin>>ch;
   if(ch=='y')
   {
       cout<<"\nEnter new details: \n";
       cout<<"\nDescription: ";
       gets(description);
       cout<<"Price: ";
       cin>>price;
       cout<<endl;
   }
  }


class PartyBook         //for party booking
{
  private:
  char name[30];
  long num;
  int guest;
  date pdate;
  time t1,t2;
  public:
  int book_no;
  void GetData()
  {
      cout<<"******************BOOKING FOR PARTY*********************"<<endl;
      cout<<"\n\t\t\tPLease Enter the following details\n\n";
      cout<<"\nYour name: ";
      gets(name);
      cout<<"Contact Number: ";
      cin>>num;
      cout<<"Number of guests for the party: ";
      cin>>guest;
      cout<<"Date of the party(DD/MM/YY): ";
      cout<<"\nDate: ";
      cin>>pdate.dd;
      cout<<"Month: ";
      cin>>pdate.mm;
      cout<<"Year: ";
      cin>>pdate.yy;
      cout<<"Timings of party: Starting Time(Hour:Minute): ";
      cout<<"\nHour: ";
      cin>>t1.hh;
      cout<<"Minute: ";
      cin>>t1.mm;
      cout<<"Ending time(Hour:Minute): ";
      cout<<"\nHour: ";
      cout<<t2.hh;
      cout<<"Minute: ";
      cout<<t2.mm;
      book_no=p_book+1;
      cout<<"\nYour information has been recorded\nYour booking number is: "<<book_no;
  }

  void Display()
  {
      cout<<"\nYour name: ";
      gets(name);
      cout<<"Contact Number: ";
      cin>>num;
      cout<<"Number of guests for the party: ";
      cin>>guest;
      cout<<"Date of the party(DD/MM/YY): ";
      cout<<"\nDate: ";
      cin>>pdate.dd;
      cout<<"Month: ";
      cin>>pdate.mm;
      cout<<"Year: ";
      cin>>pdate.yy;
      cout<<"Timings of party: ";
      cout<<t1.hh<<":"<<t1.mm<<":"<<"to"<<t2.hh<<":"<<t2.mm;
  }
};


  void tot_m_item()        //to calculate no. of items already existing
  {
    ifstream fin("Menu.dat",ios::binary|ios::in);
    MenuCard M;
    if(fin)
    {
      while(fin.read((char*)&M,sizeof(M)));
      m_item_no=M.Retitem();
    }
    fin.close();
  }

  void tot_p_item()        //to calculate no. of items already existing
  {
    ifstream fin("Party.dat",ios::binary|ios::in);
    PartyCard P;
    if(fin)
    {
      while(fin.read((char*)&P,sizeof(P)));
      p_item_no=P.Retitem();
    }
    fin.close();
  }

  void tot_book()         //to calculate the no of items already existing
  {
     ifstream fin("Book.dat",ios::binary|ios::in);
    PartyBook B;
    if(fin)
    {
      while(fin.read((char*)&B,sizeof(B)));
      p_book=B.book_no;
    }
    fin.close();
  }


  //*******************functions for menu card*******************

  void mcreate()        //to create and add items to menucard
  {
    tot_m_item();
    clrscr();
    MenuCard M;
    int n;
    fstream fout("Menu.dat",ios::binary|ios::app);
    cout<<"**********************MENU CARD CREATION************************"
	<<"\n\n\n\n Enter the no. of items to be added: ";
    cin>>n;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
    M.Getdata();
    fout.write((char *)&M,sizeof(M));
    }
     textcolor(BLINK+GREEN);
     cprintf("\n\n MENU CARD CREATED SUCCESSFULLY\N\N\N\N");
     textcolor(LIGHTGRAY);

   }

  void mdel()           //to delete item from the menu card
  {
    clrscr();
    MenuCard M;
    int ino;
    char rep;
    ifstream fin("Menu.dat",ios::binary|ios::in);
    ofstream fout("Temp.dat",ios::binary|ios::out);
    cout<<"*******************CANCELLATION OF ITEM*****************"
	<<endl<<endl;
    cout<<"Enter item number to be deleted";
    cin>>ino;
    while(fin.read((char*)&M,sizeof(M)))
    {
	if(M.Retitem()!=ino)
	fout.write((char*)&M,sizeof(M));
	else
	{
	  cout<<"\n Record to be deleted"<<endl;
	  M.Display();
	  cout<<"\nWant to delete the record(y\n): ";
	  cin>>rep;

	  if(rep=='n'||rep=='N')
	  fout.write((char*)&M,sizeof (M));

	  else
	  {
	   textcolor(BLINK+GREEN);
	   cprintf("\n\n  ITEM CANCELLED SUCCESSFULLY  \n\n\n");
	   textcolor(LIGHTGRAY);
	  }
	 }
    }
    fin.close();
    fout.close();
    remove("Menu.dat");
    rename("Temp.dat","Menu.dat");
 }

  void mdisplay()    //to display complete menu card
  {
    clrscr();
    MenuCard M;
    cout<<"*****************MENUCARD****************"<<endl<<endl;
    fstream fin("Menu.dat",ios::binary|ios::in);
    fin.seekg(0);
    while(fin.read((char*)&M,sizeof(M)))
    {
      M.Display();
    }
  getch();
  cout<<endl;
  fin.close();
  }

  void mmodify()
  {
    clrscr();
    int ino;
    long pos;
    char found='f';
    MenuCard M;
    fstream fio("Menu.dat",ios::in|ios::out|ios::binary);
    cout<<"\n enter the item number to be modified ";
    cin>>ino;
    while(!fio.eof())
    {
     pos=fio.tellg();
     fio.read((char*)&M,sizeof(M));
     if(M.Retitem()==ino)
     {
       M.Modify();
       fio.seekg(pos);
       fio.write((char*)&M,sizeof(M));
       found='t';
       break;
     }
    }
   if(found=='f')
   cout<<"\n item not found";
  }


  /****functions for party card******/

  void pcreate()     //to create or add an item to party card
  {
    tot_p_item();
    clrscr();
    PartyCard P;
    int n;
    fstream fout("Party,dat",ios::binary|ios::app);
    cout<<"***************PARTY BOOKING*********************"<<endl<<endl;
    cout<<"enter the number of items to be added"<<endl;
    cin>>n;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
     P.Getdata();
    fout.write((char*)&P,sizeof(P));
     p_item_no++;
    }
    fout.close();
     textcolor(BLINK+GREEN);
     cprintf("\n\n  PARTY BOOKING UPDATED SUCCESSFULLY\n\n\n");
     textcolor(LIGHTGRAY);
      }

  void pdel()             //to delete an item from party card
  {
     clrscr();
    PartyCard P;
    int ino;
    char rep;
    ifstream fin("Party.dat",ios::binary|ios::in);
    ofstream fout("Temp.dat",ios::binary|ios::out);
    cout<<"*******************CANCELLATION FOR THE PARTY BOOKING*****************"
	<<endl<<endl;
    cout<<"Enter item number to be deleted";
    cin>>ino;
    while(fin.read((char*)&P,sizeof(P)))
    {
	if(P.Retitem()!=ino)
	fout.write((char*)&P,sizeof(P));
	else
	{
	  cout<<"\n Record to be deleted"<<endl;
	  P.Display();
	  cout<<"\nWant to delete the record(y\n): ";
	  cin>>rep;

	  if(rep=='n'||rep=='N')
	  fout.write((char*)&P,sizeof (P));

	  else
	  {
	   textcolor(BLINK+GREEN);
	   cprintf("\n\n  ITEM CANCELLED SUCCESSFULLY  \n\n\n");
	   textcolor(LIGHTGRAY);
	  }
	 }
    }
    fin.close();
    fout.close();
    remove("Party.dat");
    rename("Temp.dat","Party.dat");
 }




  void pdisplay()        //to display the complete party card
  {
   clrscr();
   PartyCard P;
   cout<<"***************DISPLAY BOARD *****************"<<endl<<endl;
   fstream fin("Party.dat",ios::binary|ios::in);
   fin.seekg(0);
   while (fin.read((char*)&P,sizeof(P)))
   {
     P.Display();
   }
  getch();
  cout<<endl;
  fin.close();
 }

  void pmodify()           //to modify specifc item in partycard
  {
    clrscr();
    int ino;
    long pos;
    char found ='f';
    PartyCard P;
    fstream fio("Party.dat",ios::in|ios::out|ios::binary);
    cout<<"\n enter item no. to be modified ";
    cin>>ino;
    while(!fio.eof())
    {
     pos=fio.tellg();
     fio.read((char*)&P,sizeof(P));
     if(P.Retitem()==ino)
     {
      P.Modify();
      fio.seekg(pos);
      fio.write((char*)&P,sizeof(P));
      found='t';
      break;
     }
     }
    if(found=='f')
    cout<<"item not found"<<endl;
  }

/*************functons for party booking*********************/
  void pbook()                     //to add booking details in a file
  {
    tot_book();
    clrscr();
    PartyBook P;
    fstream fout("Book.dat",ios::binary||ios::app);
    P.GetData();
    fout.write((char*)&P,sizeof(P));
    p_book++;
    fout.close();
  }

  void pcancel()             //to delete booking record of file
  {
     clrscr();
    PartyBook P;
    int bno;
    char rep,found='F';
    ifstream fin("Book.dat",ios::binary|ios::in);
    ofstream fout("Temp.dat",ios::binary|ios::out);
    cout<<"Enter your booking code";
    cin>>bno;
    while(fin.read((char*)&P,sizeof(P)))
    {
	if(P.book_no!=bno)
	fout.write((char*)&P,sizeof(P));
	else
	{
	  found='t';
	  cout<<"\n Your booking details:"<<endl;
	  P.Display();
	  cout<<"\nAre you sure you want to cancel your booking?(y\n): ";
	  cin>>rep;

	  if(rep=='n'||rep=='N')
	  fout.write((char*)&P,sizeof (P));

	 }
    }
    if(found=='f'||found=='F')
    {
     cout<<"\n No such booking exist in your record";
     cout<<"\n Please make sure you have entered correct booking code";
    }
    fin.close();
    fout.close();
    remove("Book.dat");
    rename("Temp.dat","Book.dat");
 }

// ***************functions for calculating bill****************
void calbill()
{
 clrscr();
 char ch='y';
 char ch1='Y';
 int ino;
 int total=0;
 MenuCard M;
 fstream fin("Menu.dat",ios::binary|ios::in);
 cout<<"Refer to the menu card for item no."
     <<"\nDo you want to look at the menu card first?(y/n)";
 cin>>ch1;
 if(ch1=='y'||ch1=='Y')
  {
   mdisplay();
   clrscr();
  }
 cout<<"\nEnter the following Details of Order\n\n";
 do
  {
   int found=0,pr=0,qty=0;
   cout<<"\nItem NO.:";
   cin>>ino;
   fin.seekg(0);
   while(fin.read((char*)&M,sizeof(M)))
   {
    if(M.Retitem()==ino)
     {
      found=1;
      break;
     }
   }
   if(found==1)
   {
    pr=M.Retprice();
    cout<<"Quantity:";
    cin>>qty;
    total=total+(pr*qty);
   }
   else
   cout<<"\n\t\tSoory The Above Item Doesn't Exist.";
   cout<<"\n\t\tDo you want to add more items to order(Y/N):";
   cin>>ch;
  }while(ch=='y'||ch=='Y');
   cout<<"\n\n\n\t\tTotal Bill Amount is:"<<total
      <<" Bill Amount is :"<<total<<"\n\n\n\n";
      getch();
  fin.close();
 }
 /*---------------functions for sub menus------------------*/

void Menucard(int choice)	//options for menu card management
{
  switch(choice)
  {
	case 1:mcreate();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 2: mdel();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 3: mmodify();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 4: mdisplay();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	default: cout<<"Choose The Correct Option!!";
	getch();
   }
}

void Partycard(int choice)	//options for party card management
{
  switch(choice)
  {
	case 1: pcreate();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 2: pdel();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 3: pmodify();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	case 4: pdisplay();
	cout<<"\n\nPress Any Key To Go Back..";
	getch();
	break;
	default: cout<<"Choose The Correct Option!!";
	getch();
  }
}


void main()
{
int opt,choice;
MenuCard M;

do
{
clrscr();
cout<<"*********FAST FOOD RESTAURANT MANAGEMENT***********\n\n";
cout<<"\t\t\t1. Menu Card Management\n\n\n\t\t\t";
cout<<"2. Party Card Management\n\n\n\t\t\t";
cout<<"3.Bill\n\n\n\t\t\t";
cout<<"4. Party Booking/Cancellation\n\n\n\t\t\t";
cout<<" 5. Exit\n\n\n\n\n\n\t\t\t";
cout<<"Choose The Correct Option";
cin>>opt;
switch(opt)
{
 case 1: clrscr();
 do{
   clrscr();
   cout<<"*************MENU CARD MANAGEMENT*************\n\n\n";
   cout<<"\n\n\t\t\t1. Add An Item To Menu Card\n\n\n\t\t\t";
   cout<<"\n\n\t\t\t2. Delete An Item To Menu Card\n\n\n\t\t\t";
   cout<<"\n\n\t\t\t3. Modify An Item To Menu Card\n\n\n\t\t\t";
   cout<<"\n\n\t\t\t4. Display Items To Menu Card\n\n\n\t\t\t";
   cout<<"\n\n\t\t\t5. Go Back to main menu\n\n\n\t\t\t";
   cout<<"\n\n\t\t\tChoose The Correct Option:";
   cin>>choice;
   if(choice==5)
	break;
   Menucard(choice);
  }while(1);
  break;
 case 2:
  do{
   clrscr();
   cout<<"*************PARTY CARD MANAGEMENT***************\n\n\n";
   cout<<"\n\n\t\t\t1. Add An Item To Party Card\n\n\n\t\t\t";
   cout<<"2. Delete An Item From PartyCard\n\n\n\t\t\t";
   cout<<"3. Modify Party Card\n\n\n\t\t\t";
   cout<<"4. Watch Party Card\n\n\n\t\t\t";
   cout<<"5. Go Back To Main Menu\n\n\n\n\n\n\t\t\t";
   cout<<"Choose The Correct Option:";
   cin>>choice;
   if(choice==5)
	break;
   Partycard(choice);
  }while(1);
  break;
 case 3: calbill();
  cout<<"\n\nPress Any Kay To Go Back..";
  getch();
  break;
 case 4:
  do{
   clrscr();
   cout<<"*****************PARTY BOOKING-CANCELLATION***************\n\n\n";
   cout<<"\n\n\t\t\t1. Book For Party\n\n\n\t\t\t";
   cout<<"2. Cancel Party Booking\n\n\n\t\t\t";
   cout<<"3. Go BackTo Previous Menu\n\n\n\n\n\n\t\t\t";
   cout<<"Choose The Correct Option:";
    cin>>choice;
   if(choice==3)
	break;
   switch(choice)
   {
	case 1:pbook();
	cout<<"\n\nPress Any Kay To Go Back..";
	getch();
	 break;
	case 2:pcancel();
	cout<<"\n\nPress Any Kay To Go Back..";
	getch();
	 break;
	default:cout<<"\nPlease Enter Correct Choice";
  }
 }while(1);
 break;
 case 5: exit(0);
 default:cout<<"Choose The Correct Option!!";
  getch();
 }
 }while(1);
}





