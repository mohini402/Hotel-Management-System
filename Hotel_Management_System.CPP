#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<iomanip>
#include<ctype.h>
#include<windows.h>

using namespace std;

COORD coord={0,0};


struct CUST  //checkin in main menu
{
	int rmno;
	char name[30];
	char address[30];
	long Phone;
	int member;
	char date[15];
	int ndys;
	float rmcst;
}c;

struct BILL   //checkout in main menu
{
	int rmno;
	char name[30];
	char address[30];
	long Phone;
	int member;
	char date[15];
	int ndys;
	float rmcst,orcst;
	float total;
}b;

struct RUM    //roomtype in master menu
{
		int roomno;
		int p_ebed;
		int p_eplw;
		int p_eblk;
		int p_etwl;
		char bed[15];
		char roomtype[30];
		float roomcst;
		int avl;
}r;


void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void setTextColor(const string& color) {
    cout << color;
}

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string WHITE = "\033[0m";

//-------------------------------------------------------------------

void CURRENT() {
    system("cls");
    RUM r1;
    ofstream fout("record.dat", ios::app);
    fstream fin("roomtype.txt", ios::in);
    
    cout << "\nROOM AVAILABILITY: ";
    setTextColor(WHITE);
    cout << "(";
    setTextColor(RED);
    cout << "RED: ROOM ALREADY BOOKED | ";
    setTextColor(GREEN);
    cout << "GREEN: ROOM AVAILABLE)";
    setTextColor(WHITE);
    cout << "\n";
    cout << "\tROOM NUMBER\t  ROOM TYPE\t   BED TYPE\t      PRICE\n";
    for (int i = 0; i < 80; i++) { cout << "-"; }
    cout << endl;

    int rr = 6;
    int rmm[50], rmmcst[50];
    int rnc = 0;
    
    while (fin.read(reinterpret_cast<char*>(&r1), sizeof(r1))) {
        if (r1.avl == 1) {
            setTextColor(GREEN);
        } else {
            setTextColor(RED);
        }
        gotoxy(8, rr);
        cout << r1.roomno;
        gotoxy(28, rr);
        cout << r1.roomtype;
        gotoxy(45, rr);
        cout << r1.bed;
        gotoxy(61, rr);
        cout << fixed << setprecision(2) << r1.roomcst;
        cout << endl;
        
        if (r1.avl == 1) {
            rmm[rnc] = r1.roomno;
            rmmcst[rnc] = r1.roomcst;
            rnc++;
        }
        rr++;
    }
    fin.close();
    setTextColor(WHITE);

    if (rnc == 0) {
        cout << "ROOM NOT AVAILABLE.\n";
    } else {
        time_t t = time(nullptr);
        tm tm = *localtime(&t);
        cout << "THE CURRENT DATE IS: " << put_time(&tm, "%d/%m/%Y") << "\n";
        cout << "**********************\nENTER CUSTOMER DETAILS\n**********************\n";
        int flg = 0, i;

        while (true) {
            cout << "\nENTER ROOM NUMBER Or PRESS 0 TO EXIT): ";
            cin >> c.rmno;
            if (c.rmno == 0) {
                break;
            } else {
                flg = 0;
                for (i = 0; i < rnc; i++) {
                    if (c.rmno == rmm[i]) {
                        flg = 1;
                        break;
                    }
                }
                if (flg == 1) {
                    c.rmcst = rmmcst[i];
                    cout << "\nNAME: ";
                    cin >> c.name;
                    cin.ignore();
                    cout << "\nNO.OF FAMILY MEMBERS: ";
                    cin >> c.member;
                    cin.ignore();
                    cout << "\nADDRESS: ";
                    cin >> c.address;
                    cin.ignore();
                	cout << "\nNUMBER OF DAYS: ";
                    cin >> c.ndys;
                    cout << "\nPHONE NUMBER: ";
                    cin >> c.Phone;
                    cout << "\n";
                    break;
                } else {
                    cout << "INVALID ROOM NUMBER.\nPRESS ANY KEY TO ENTER CORRECT ROOM NUMBER:";
                    _getch();
                }
            }
        }
        if (c.rmno > 0) {
            cout << "DO YOU WANT TO SAVE(Y/N) :";
            char ch;
            cin >> ch;
            if (toupper(ch) == 'Y') {
                cout << "\nHAVE A NICE DAY\n";
                fout.write(reinterpret_cast<char*>(&c), sizeof(c));
                fstream fin("roomtype.txt", ios::in | ios::out);
                while (fin.read(reinterpret_cast<char*>(&r1), sizeof(r1))) {
                    if (r1.roomno == c.rmno) {
                        int pos = fin.tellg();
                        fin.seekp(pos - sizeof(r1));
                        r1.avl = 0;
                        fin.write(reinterpret_cast<char*>(&r1), sizeof(r1));
                        break;
                    }
                }
                fin.close();
            }
        }
    }
    fout.close();
}

void ADVANCE() {
    system("cls");
    RUM r2;
    ofstream fout("record1.dat", ios::app);
    fstream fin("roomtype.txt", ios::in);
    
    cout << "\nROOM AVAILABILITY: ";
    setTextColor(WHITE);
    cout << "\n\n";
    cout << "\tROOM NUMBER\t  ROOM TYPE\t   BED TYPE\t PRICE\n";
    for (int i = 0; i < 80; i++) { cout << "-"; }
    cout << endl;

    int rr = 6;
    while (fin.read(reinterpret_cast<char*>(&r2), sizeof(r2))) {
        gotoxy(8, rr);
        cout << r2.roomno;
        gotoxy(28, rr);
        cout << r2.roomtype;
        gotoxy(45, rr);
        cout << r2.bed;
        gotoxy(61, rr);
        cout << fixed << setprecision(2) << r2.roomcst;
        cout << endl;
        rr++;
    }
    fin.close();
    setTextColor(WHITE);

    time_t t = time(nullptr);
    tm tm = *localtime(&t);
    cout << "THE CURRENT DATE IS: " << put_time(&tm, "%d/%m/%Y") << "\n";
    cout << "**********************\nENTER CUSTOMER DETAILS\n**********************\n";
    
    cout << "\nNAME: ";
    cin >> c.name;
    cout << "\nNO.OF FAMILY MEMBERS: ";
    cin >> c.member;
    cout << "\nENTER CHECKIN DATE (dd/mm/yyyy): ";
    cin >> c.date;
    cout << "\nADDRESS: ";
    cin >> c.address;
    cout << "\nPHONE NUMBER: ";
    cin >> c.Phone;

    cout << "DO YOU WANT TO SAVE (Y/N): ";
    char ch;
    cin >> ch;
    if (toupper(ch) == 'Y') {
        cout << "\nHAVE A NICE DAY\n";
        fout.write(reinterpret_cast<char*>(&c), sizeof(c));
        
        fstream fin("roomtype.txt", ios::in | ios::out);
        while (fin.read(reinterpret_cast<char*>(&r2), sizeof(r2))) {
            if (r2.roomno == c.rmno) {
                int pos = fin.tellg();
                fin.seekp(pos - sizeof(r2));
                r2.avl = 0;
                fin.write(reinterpret_cast<char*>(&r2), sizeof(r2));
                break;
            }
        }
        fin.close();
    }
    fout.close();
}


void CHECKIN_MENU()              //in main menu
{
	system("cls");
	char ch;
	while(1)
	{
		system("cls");
		gotoxy(33,4);printf("**********************");
		gotoxy(33,5);printf("SELECT TYPE OF BOOKING");
		gotoxy(33,6);printf("**********************");
		gotoxy(33,8);printf("1. CURRENT BOOKING");
		gotoxy(33,9);printf("2. ADVANCE BOOKING");
		gotoxy(33,10);printf("3. RETURN");
		gotoxy(33,12);printf("ENTER YOUR CHOICE:");
		ch=getche();
		switch(ch)
		{
			case '1': system("cls");
				  CURRENT();
				  getch();
				  break;
			case '2': system("cls");
				  ADVANCE();
				  getch();
				  break;
			case '3': return;
		}
	}
}

//-------------------------------------------------------------------

void R_MODIFY_FORAVL(int);
void C_DELETE(int);

void CHECKOUT()
{
	fstream fout("bill.txt",ios::app);
	fstream fin("record.dat",ios::in);
	fin.read((char *)&c,sizeof(c));
	for(int i=0;i<80;i++){ printf("-"); } printf("\n");
	gotoxy(33,2);printf("COMFORT INN HOTEL");printf("\n");
	for(int i=0;i<80;i++){ printf("-"); } printf("\n");
	printf("\n");
	int rno;
	printf("\nENTER ROOM NUMBER TO GENERATE BILL FOR: ");
	scanf("%d",&rno);
	if(rno==c.rmno)
	{
		float btotal;
		printf("\nROOM NUMBER: %d",c.rmno);
		printf("\nNAME: %s",c.name);
		printf("\nNO.OF FAMILY MEMBERS: %d",c.member);
		printf("\nADDRESS: %s",c.address);
		printf("\nPHONE NUMBER: %ld",c.Phone);
		printf("\nNUMBER OF DAYS: %d",c.ndys);
		printf("\nPER DAY COST: %f",c.rmcst);
		btotal=c.ndys*c.rmcst;
		printf("\nROOM COST FOR %d DAYS: %f",c.ndys,btotal);
		float gtotal=btotal;
		printf("\nGRAND TOTAL COST: %f",gtotal);
		printf("\nAMOUNT TO BE PAID (Y/N): ");
		fflush(stdin);
		char ch;
		scanf("%c",&ch);
		if(toupper(ch)=='Y')
		{
			b.rmno=c.rmno;strcpy(b.name,c.name);strcpy(b.address,c.address);
			b.Phone=c.Phone;b.member=c.member;strcpy(b.date,c.date);
			b.ndys=c.ndys;b.rmcst=c.rmcst;
			b.total=gtotal;
			fout.write((char *)&b,sizeof(b));
			R_MODIFY_FORAVL(c.rmno);
			fin.close();
			C_DELETE(c.rmno);
		}
	}
	fout.close();
	fin.close();
	getch();
}

//-------------------------------------------------------------------

void R_ADD()                       //in room type
{
	system("cls");
	fstream fout("roomtype.txt",ios::out|ios::app|ios::binary);
	printf("\n**********************");
	printf("\nENTER ROOM DETAILS");
	printf("\n**********************");
	fflush(stdin);
	printf("\nROOM NUMBER: ");
	scanf("%d",&r.roomno);
	fflush(stdin);
	printf("\nROOMTYPE: ");
	scanf("%s",&r.roomtype);
	fflush(stdin);
	printf("\nTYPE OF BED: ");
	gets(r.bed);
	printf("\nROOMCOST: ");
	scanf("%f",&r.roomcst);
	r.avl=1;
	printf("DO YOU WANT TO SAVE(Y/N): ");
	char ch;
	cin>>ch;
	if(toupper(ch)=='Y')
	{
		fout.write((char*)&r,sizeof(r));
		printf("\nROOMTYPE ADDED.");
	}
	fout.close();
}

void R_MODIFY()                       //in room type
{
	system("cls");
	ofstream fout("rtype.tmp",ios::out|ios::binary);
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO ROOM FOUND.");
	}
	else
	{
		int rno;
		printf("\nENTER ROOM NUMBER TO MODIFY: ");
		scanf("%d",&rno);
		while(fin.read((char*)&r,sizeof(r)))
		{
			if(rno==r.roomno)
			{
				RUM r1=r;
				printf("\n***********************");
				printf("\nENTER DETAILS TO MODIFY");
				printf("\n***********************");
				printf("\nROOM NUMBER: %d",r1.roomno);
				printf("\nROOMTYPE: ");
				gets(r1.roomtype);
				printf("\nROOMCOST: ");
				scanf("%f",&r1.roomcst);
				printf("DO YOU WANT TO SAVE(Y/N): ");
				char ch;
				printf("%c",&ch);
				if(toupper(ch)=='Y')
				{
					fout.write((char*)&r1,sizeof(r1));
				}
				else
					fout.write((char*)&r,sizeof(r));
			}
			else
				fout.write((char*)&r,sizeof(r));
		}
		fout.close();
		fin.close();
		remove("roomtype.txt");
		rename("rtype.tmp","roomtype.txt");
	}
}

void R_MODIFY_FORAVL(int rno)
{
	ofstream fout("rtype.tmp",ios::out|ios::binary);
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO ROOM FOUND.");
	}
	else
	{
		while(fin.read((char*)&r,sizeof(r)))
		{
			if(rno==r.roomno)
			{
				r.avl=1;
				fout.write((char*)&r,sizeof(r));
			}
			else
				fout.write((char*)&r,sizeof(r));
		}
		fout.close();
		fin.close();
		remove("roomtype.txt");
		rename("rtype.tmp","roomtype.txt");
	}
}


void R_DISPLAY()                       //in room type
{
	system("cls");
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO ROOM FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ cout<<"*"; }
		gotoxy(30,2);printf("ROOM DETAIL INFORMATION\n");
		for(int i=0;i<80;i++){ printf("*"); }printf("\n");
		printf("\tROOM NUMBER\t    ROOM TYPE\t      ROOM COST\t\tBED TYPE\n");
		for(int i=0;i<80;i++){ printf("-"); }
		int rr=7;
		while(fin.read((char*)&r,sizeof(r)))
		{
			gotoxy(12,rr);
			printf("%d",r.roomno);
			gotoxy(31,rr);
			printf("%s",r.roomtype);
			gotoxy(46,rr);
			printf("%f",r.roomcst);
			gotoxy(67,rr);
			printf("%s",r.bed);
			printf("\n");
			rr++;
		}
		printf("\nPRICE OF EXTRA BED: ");
		r.p_ebed=200;
		printf("%d",r.p_ebed);
		printf("\nPRICE OF EXTRA PILLOW: ");
		r.p_eplw=40;
		printf("%d",r.p_eplw);
		printf("\nPRICE OF EXTRA BLANKET: ");
		r.p_eblk=80;
		printf("%d",r.p_eblk);
		printf("\nPRICE OF EXTRA TOWEL: ");
		r.p_etwl=20;
		printf("%d",r.p_etwl);
	}
	fin.close();
}


void R_DELETE()
{
	system("cls");
	ofstream fout("rtype.tmp",ios::out|ios::binary);
	ifstream fin("roomtype.txt",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"NO ROOM FOUND.";
	}
	else
	{
		int rno;
		printf("\nENTER ROOM NUMBER TO DELETE: ");
		scanf("%d",&rno);
		int flg=0;
		while(fin.read((char*)&r,sizeof(r)))
		{
			if(rno==r.roomno)
				flg=1;
			else
				fout.write((char *)&r, sizeof(r));
		}
		if(flg==1)
			printf("ROOMTYPE DELETED.");
		else
			printf("ROOM NOT AVAILABLE TO DELETE.");
	}

	fout.close();
	fin.close();
	remove("roomtype.txt");
	rename("rtype.tmp","roomtype.txt");
}

void M_ROOMTYPE_MENU()            //room in master
{
	system("cls");
	int ch;
	while(1)
	{
		system("cls");
		gotoxy(33,4);cout<<"**********************";
		gotoxy(33,5);cout<<"     ROOM OPTIONS";
		gotoxy(33,6);cout<<"**********************";
		gotoxy(33,8);cout<<"1. ADD ";
		gotoxy(33,9);cout<<"2. MODIFY";
		gotoxy(33,10);cout<<"3. DISPLAY";
		gotoxy(33,11);cout<<"4. DELETE";
		gotoxy(33,12);cout<<"5. RETURN";
		gotoxy(33,14);cout<<"ENTER YOUR CHOICE:";
		ch=getche();
		switch(ch)
		{
			case '1': system("cls");
				  R_ADD();
				  getch();
				  break;
			case '2': system("cls");
				  R_MODIFY();
				  getch();
				  break;
			case '3': system("cls");
				  R_DISPLAY();
				  getch();
				  break;
			case '4': system("cls");
				  R_DELETE();
				  getch();
				  break;
			case '5': return;
		}
	}
}

//-------------------------------------------------------------------

void C_MODIFY()
{
	system("cls");
	ofstream fout("ctype.tmp",ios::out|ios::binary);
	ifstream fin("record.dat",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}
	else
	{
		int rno;
		CUST c1;
		printf("\nENTER ROOM ID TO MODIFY: ");
		scanf("%d",&rno);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(rno==c.rmno)
			{
				printf("\n***********************");
				printf("\nENTER DETAILS TO MODIFY");
				printf("\n***********************");
				printf("\nENTER ROOM ID TO MODIFY: %d",rno);
				printf("\nNAME: ");
				scanf("%s",c1.name);
				fflush(stdin);
				printf("\nNO.OF FAMILY MEMBERS: ");
				scanf("%d",c1.member);
				printf("\nADDRESS: ");
				scanf("%s",c1.address);
				fflush(stdin);
				printf("\nNUMBER OF DAYS: ");
				scanf("%d",&c1.ndys);
				printf("\nPHONE NUMBER: ");
				scanf("%ld",&c1.Phone);
				fflush(stdin);
				printf("\n\n");
				char ch;
				printf("DO YOU WANT TO SAVE(Y/N): ");
				scanf("%c",&ch);
				if(toupper(ch)=='Y')
				{
					c1.rmno=c.rmno;
					c1.rmcst=c.rmcst;
					fout.write((char*)&c1,sizeof(c1));
					printf("RECORD MODIFIED.");
				}
				else
					fout.write((char*)&c,sizeof(c));
			}
			else
				fout.write((char*)&c,sizeof(c));
		}
		fout.close();
		fin.close();
		remove("record.dat");
		rename("ctype.tmp","record.dat");
	}
}

void C_DISPLAY()
{
	system("cls");
	ifstream fin("record.dat",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ printf("*"); }
		gotoxy(33,2);printf("CUSTOMER DETAIL INFORMATION\n");
		for(int i=0;i<80;i++){ printf("*"); } printf("\n");
		gotoxy(2,5);printf("R.NO");
		gotoxy(15,5);printf("CUSTOMER NAME");
		gotoxy(35,5);printf("ADDRESS");
		gotoxy(50,5);printf("PHONE");
		gotoxy(60,5);printf("DAYS");
		gotoxy(70,5);printf("COST");printf("\n");
		for(int i=0;i<80;i++){ printf("-"); }printf("\n");
		int rr=7;
		while(fin.read((char*)&c,sizeof(c)))
		{
			gotoxy(3,rr);printf("%d",c.rmno);
			gotoxy(17,rr);printf("%s",c.name);
			gotoxy(37,rr);printf("%s",c.address);
			gotoxy(50,rr);printf("%ld",c.Phone);
			gotoxy(62,rr);printf("%d",c.ndys);
			gotoxy(70,rr);printf("%f",c.rmcst);
			rr++;
		}
		fin.close();
	}
}


void BILL_DISPLAY()
{
	system("cls");
	ifstream fin("bill.txt",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}
	else
	{
		for(int i=0;i<80;i++){ printf("*"); }
		gotoxy(25,2);printf("CUSTOMER WISE BILL DETAIL INFORMATION\n");
		for(int i=0;i<80;i++){ printf("*"); }
		gotoxy(2,5);printf("R.NO");
		gotoxy(10,5);printf("CUSTOMER NAME");
		gotoxy(25,5);printf("ADDRESS");
		gotoxy(36,5);printf("PHONE");
		gotoxy(47,5);printf("DAYS");
		gotoxy(56,5);printf("COST");
		gotoxy(69,5);printf("T.COST");printf("\n");
		for(int i=0;i<80;i++){ printf("-"); }printf("\n");
		int rr=7;
		while(fin.read((char*)&b,sizeof(b)))
		{  	gotoxy(2,rr);printf("%d",b.rmno);
			gotoxy(13,rr);printf("%s",b.name);
			gotoxy(27,rr);printf("%s",b.address);
			gotoxy(35,rr);printf("%ld",b.Phone);
			gotoxy(48,rr);printf("%d",b.ndys);
			gotoxy(54,rr);printf("%f",b.rmcst);
			gotoxy(68,rr);printf("%f",b.total);
			rr++;
		}
		fin.close();
	}
}

void C_DELETE(int rno)
{
	system("cls");
	ofstream fout("ctype.tmp",ios::out|ios::binary);
	ifstream fin("record.dat",ios::in|ios::binary);
	if(!fin)
	{
		printf("NO RECORD FOUND.");
	}


	else
	{
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(rno!=c.rmno)
				fout.write((char *)&c, sizeof(c));
		}

	}
	fout.close();
	fin.close();
	remove("record.dat");
	rename("ctype.tmp","record.dat");
}

void CUSTOMER_MENU()
{
	int ch;
	while(1)
	{
		system("cls");
		gotoxy(33,4);cout<<"**********************";
		gotoxy(33,5);cout<<"   CUSTOMER OPTIONS        ";
		gotoxy(33,6);cout<<"**********************";
		gotoxy(33,8);cout<<"1. MODIFY";
		gotoxy(33,9);cout<<"2. DISPLAY";
		gotoxy(33,10);cout<<"3. BILL DISPLAY";
		gotoxy(33,11);cout<<"4. RETURN";
		gotoxy(33,12);cout<<"ENTER YOUR CHOICE:";
		ch=getche();
		switch(ch)
		{
			case '1': system("cls");
				  C_MODIFY();
				  getch();
				  break;
			case '2': system("cls");
				  C_DISPLAY();
				  getch();
				  break;
			case '3': system("cls");
				  BILL_DISPLAY();
				  getch();
				  break;
			case '4': return;
		}
	}
}

//-------------------------------------------------------------------



void MASTER_MENU()
{
	system("cls");
	int ch;
	while(1)
	{
		system("cls");
		gotoxy(33,4);printf("**********************");
		gotoxy(33,5);printf("        MASTER        ");
		gotoxy(33,6);printf("**********************");
		gotoxy(33,8);printf("1. ROOM TYPE");
		gotoxy(33,9);printf("2. RETURN");
		gotoxy(33,12);printf("ENTER YOUR CHOICE: ");
		ch=getche();
		switch(ch)
		{
			case '1': 	system("cls");
					M_ROOMTYPE_MENU();
					break;
			case '2': 	return;
		}
	}
}

//-------------------------------------------------------------------

void intro()
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t  HOTEL MANAGEMENT SYSTEM");
	printf("\n\n\n\n\t\t\t  MADE BY: ");
	printf("\n\t\t\t\t   MOHINI AGARWAL");
	printf("\n\n\n\n\t\t\t  PRESS ANY KEY TO CONTINUE...");
	getch();
}

int main()
{
	system("cls");
	intro();
	char choice;
	while(1)
	{
		system("cls");
		gotoxy(33,4);printf("*************");
		gotoxy(33,5);printf("* MAIN MENU *");
		gotoxy(33,6);printf("*************");
		gotoxy(33,8);printf("1.CHECK-IN");
		gotoxy(33,9);printf("2.CHECK-OUT");
		gotoxy(33,10);printf("3.CUSTOMER INFO");
		gotoxy(33,11);printf("4.MASTER");
		gotoxy(33,12);printf("5.EXIT");
		gotoxy(33,13);printf("ENTER YOUR CHOICE:");
		choice=getche();

		switch(choice)
		{
			case '1': system("cls");
				  CHECKIN_MENU();
				  break;
			case '2': system("cls");
				  CHECKOUT();
				  break;
			case '3': system("cls");
				  CUSTOMER_MENU();
				  break;
			case '4': system("cls");
				  MASTER_MENU();
				  break;
			case '5': exit(0);
		}
	}
	return 0;
}
