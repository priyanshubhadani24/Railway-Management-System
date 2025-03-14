// Railway Reservation System

// #include<iostream>
// #include<fstream>
// #include<string.h>
// #include<random>
// #include<vector>
// #include<sstream>
// #include<cstdlib>
// #include<ctime>
















#include<bits/stdc++.h>
using namespace std;

int pnr_generator();
vector<string> simple_token(string str);

class Admin{
    // Admin purpose
    private:
        char admin_user[100];
        char admin_pass[100];
    
    public:
        void get_admin_details() {
            cout<<"Enter Username (Without Spaces): ";
            cin>>admin_user;

            cout<<"Enter Password: ";
            cin>>admin_pass;
        }

        void display_admin_details() {
            cout<<"Username: "<<admin_user<<endl;
            cout<<"Password: "<<admin_pass<<endl;
        }

        string get_user_name() {
            return admin_user;
        }

        string get_user_pass() {
            return admin_pass;
        }
};

class Train{
    // Train Details To Enter By the Admin Mode
    public:
        string t_name;
        string t_code;
        int sl, gen, ac;
        float sl_fare, gen_fare, ac_fare;

        string start_point;
        string end_point;

        void get_train_details() {
            cin.ignore();
            cout<<"Enter name of Train: ";
            getline(cin, t_name);

            // cin.ignore();
            cout<<"Enter Train code: ";
            getline(cin, t_code);

            cout<<"Enter Starting Point: ";
            cin>>start_point;

            cout<<"Enter End Point: ";
            cin>>end_point;

            cout<<"Enter total number of seats in Sleeper category: ";
            cin>>sl;

            cout<<"Enter price per Sleeper seat: ";
            cin>>sl_fare;

            cout<<"Enter total number of seats in General category: ";
            cin>>gen;

            cout<<"Enter price per General seat: ";
            cin>>gen_fare;

            cout<<"Enter total number of seats in AC category: ";
            cin>>ac;

            cout<<"Enter price per AC seat: ";
            cin>>ac_fare;
        }

        void display_train_details() {
            cout << "\n|Train Name" << "\t" << "|Train Code" << "\t" << "|Boarding pt." << "\t" << "|Destination pt."  <<"\t";
			cout << "|SL-Class" << "\t"<< "|SL-Class Fare" << "\t" << "|GEN-Class" << "\t" << "|GEN-Class Fare" <<"\t";
			cout << "|AC-Class" << "\t"<< "|AC-Class Fare" << "\t";

			cout << "|" << t_name << "\t\t" << "|" << t_code << "\t\t" << "|" << start_point << "\t\t" << "|" << end_point <<"\t\t\t";
			cout << "|" << sl << "\t\t" << "|"<< sl_fare << "\t\t" << "|" << gen<< "\t\t" << "|" << gen_fare <<"\t\t";
			cout << "|" << ac << "\t\t" << "|"<< ac_fare << "\t\t";
        }
};

class Passenger{
    // Passenger Info
    private:
        char passenger_user[100];
        char passenger_pass[100];
    
    public:
        void get_p_details() {
            cout<<"Enter Username: ";
            cin>>passenger_user;

            cout<<"Enter Password: ";
            cin>>passenger_pass;
        }

        void display_p_details() {
            cout<<"Username: "<<passenger_user<<endl;
            cout<<"Password: "<<passenger_pass<<endl;
        }

        string get_user_name() {
            return passenger_user;
        }

        string get_user_pass() {
            return passenger_pass;
        }
};

class Reservation{
    public:
        char t_code[20];
        int nosr, pnr;
        char pname[10][100];
        int age[10];
        int d,m,y;
        char category[10];

        void pdetails() {
            cout<<"Enter Train Code: ";
            cin.ignore();
            cin.getline(t_code, 20);

            cout<<"Enter number seats you want to reserve: ";
            cin>>nosr;

            for(int i = 0; i<nosr; i++) {
                cout<<"Enter Passenger Name: ";
                cin.ignore();
                cin.getline(pname[i], 100);

                cout<<"Enter Passenger Age: ";
                cin>>age[i];
            }

            cout<<"Enter Date of Travel in the Format DD MM YYYY(Separation by spaces): ";
            cin>>d>>m>>y;

            cout<<"Enter Category(SL, GEN, AC): ";
            cin>>category;

            pnr = pnr_generator();
        }


        void display_pdetails() {
            cout<<"Train Code: "<<t_code<<" PNR: "<<pnr<<endl;
            cout<<"Boarding Date: "<<d<<"-"<<m<<"-"<<y<<endl;
            for(int i = 0; i<nosr; i++) {
                cout<<"Name: "<<pname[i]<<" Age: "<<age[i]<<" Category: "<<category<<endl;
            }
        }

        string gen_pdetails() {
            string name = "";
            for(int i = 0; i<nosr; i++) {
                string temp = (string)pname[i]+" "+to_string(age[i])+" ";
                name = name + temp;
            }

            string str = (string)t_code+" "+to_string(pnr)+" Boarding_Date:"+to_string(d)+":"+to_string(m)+":"+to_string(y)
            +" "+string(category)+" "+name;

            return str;
        }
        
};

void login_signin(Admin &A, const string &filename, Train &T);
void login_signin_p(Passenger &P, const string &filename, Reservation &R);
void displayFileContent(const string &filename);
// int searchAndDisplay(const string &filename, const string &searchStr);
string search(const string &filename, const string &searchStr);
void admin_management(Train &T); 
void admin_mode_management(Admin &A, Train &T);
void user_mode_management(Passenger &P, Reservation &R);
void user_management(Reservation &R);

int main() {
    cout<<"************************ Welcome to Main Menu ***********************"<<endl;
    int option;
    Admin A;
    Passenger P;
    Train T;
    Reservation R;
    string username, password, str, filename;
    fstream file;

    while(1){
        cout<<"1. Admin"<<endl;
        cout<<"2. User"<<endl;
        cout<<"3. Exit Program"<<endl;

        cout<<"Enter choice: ";
        cin>>option;

        switch(option) {
            case 1:
                cout<<"**************ADMIN MODE****************"<<endl;
                admin_mode_management(A, T);
                break;

            case 2:
                cout<<"**************USER MODE****************"<<endl;
                user_mode_management(P, R);
                break;

            case 3:
                exit(0);

            default:
                cout<<"Enter a valid option."<<endl;
                break;
        }
    }

    return 0;
}

int pnr_generator() {

    srand(time(0));
    int lb = 20, ub = 100; 
    int random = (rand() % (ub - lb + 1)) + lb;
    return random;
}

void displayFileContent(const string &filename) {
    fstream file(filename);
    string line;
    vector<string> v;

    if(file.is_open()) {
        // cout<<"File Content: "<<endl;
        while(getline(file, line)) {
            v = simple_token(line);
            for(auto value: v) {
                cout<<value<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;

        file.close();
    }else{
        cout<<"Failed to open file."<<endl;
    }
}

void admin_management(Train &T){
    cout<<"********************** Welcome to Admin Management ***********************"<<endl;
    int option1;
    string str, line, x, t_code, filename = "Train_details.txt";
    fstream file, temp;
    // const char *p;
 
    do {
        cout<<"1. Add Train Details"<<endl;
        cout<<"2. Delete Train Details"<<endl;
        cout<<"3. Display Train Details"<<endl;
        cout<<"4. Go Back to Main Menu"<<endl;

        cout<<"Enter your option: ";
        cin>>option1;

        switch(option1) {
            case 1: 
                T.get_train_details();

                str = (string)T.t_name+" "+(string)T.t_code+" "+(string)T.start_point+" "+(string)T.end_point+" "+
                to_string(T.sl)+" "+to_string(T.sl_fare)+" "+to_string(T.gen)+" "+to_string(T.gen_fare)+" "+to_string(T.ac)+" "+to_string(T.ac_fare);

                file.open(filename, ios::in|ios::out|ios::app);
                file<<str<<endl;
                file.close();
                break;

            case 2:
                cout<<"Enter Train Code: ";
                cin>>t_code;

                str = search(filename, t_code);
                // cout<<str<<endl;

                file.open(filename, ios::in | ios::out | ios::app);
                temp.open("temp1.txt", ios::in | ios::out | ios::app);
                while(getline(file, line)) {
                    if(line == str) {
                        // cout<<"True"<<endl;
                    }
                    if(line != str) {
                        temp<<line<<endl;
                    }
                }

                temp.close();
                file.close();

                remove("Train_details.txt");
                rename("temp1.txt", "Train_details.txt");                

                break;


            case 3:
                cout << "\n|Train Name" << "\t\t\t" << "|Train Code" << "\t" << "|Boarding pt." << "\t" << "|Destination pt."  <<"\t";
			    cout << "|SL-Class" << "\t"<< "|SL-Class Fare" << "\t" << "|GEN-Class" << "\t" << "|GEN-Class Fare" <<"\t";
			    cout << "|AC-Class" << "\t"<< "|AC-Class Fare" << "\t";
                cout<<endl;
                displayFileContent(filename);
                break;

            case 4:
                break;
            
            default:
                cout<<"Enter a valid option"<<endl;
                break;
        }
    }while(option1 != 4);
}

void admin_mode_management(Admin &A, Train&T){
    int option;
    string username, password, str, filename;
    fstream file;
    do{
        filename = "admin_login.txt";
        cout<<"1. Login"<<endl;
        cout<<"2. Add new user"<<endl;
        cout<<"3. Display Users"<<endl;
        cout<<"4. Go Back to Main Menu"<<endl;

        cout<<"Enter your option: ";
        cin>>option;

        switch(option) {
            case 1:
                login_signin(A, filename, T);
                break;

            case 2:
                A.get_admin_details();
                username = A.get_user_name();
                password = A.get_user_pass();
                str = username + " " + password;
                file.open(filename, ios::in|ios::out|ios::app);
                file<<str<<endl;
                file.close();
                cout<<"Successfully Added New Admin User"<<endl;
                break;

            case 3:
                cout<<"Username: "<<"\t"<<"Password: "<<endl;
                displayFileContent(filename);
                break;

            case 4:
                break;

            default:
                cout<<"Enter a valid option."<<endl;
                break;
        }

    }while(option != 4);
}

void user_mode_management(Passenger &P, Reservation &R) {
    int option;
    string username, password, str, filename = "user_login.txt";
    fstream file;

    do{
        cout<<"1. Login"<<endl;
        cout<<"2. Sign Up"<<endl;
        cout<<"3. Go back to Main Menu"<<endl;

        cout<<"Enter your option: ";
        cin>>option;

        switch(option) {
            case 1:
                login_signin_p(P, filename, R);
                break;

            case 2:
                P.get_p_details();
                username = P.get_user_name();
                password = P.get_user_pass();
                str = username + " " + password;
                file.open(filename, ios::in|ios::out|ios::app);
                file<<str<<endl;
                file.close();
                cout<<"Successfully Added New User"<<endl;
                break;

            case 3:
                break;
            
            default:
                cout<<"Enter a valid option"<<endl;
                break;
        }
    }while(option != 3);
}

void user_management(Reservation &R) {
    int option;
    string str,pnr,x,line, head, sub_head, filename = "reservation.txt";
    fstream file, temp;
    vector<string> v;

    do{
        cout<<"1. Display Availabe Train Bookings"<<endl;
        cout<<"2. Reserve Seats"<<endl;
        cout<<"3. Cancel Reservation"<<endl;
        cout<<"4. Display Reservation"<<endl;
        cout<<"5. Generate E-Ticket"<<endl;
        cout<<"6. Go Back to Main Menu"<<endl;

        cout<<"Enter your option: ";
        cin>>option;

        switch(option) {
            case 1:
                cout << "\n|Train Name" << "\t\t\t" << "|Train Code" << "\t" << "|Boarding pt." << "\t" << "|Destination pt."  <<"\t";
			    cout << "|SL-Class" << "\t"<< "|SL-Class Fare" << "\t" << "|GEN-Class" << "\t" << "|GEN-Class Fare" <<"\t";
			    cout << "|AC-Class" << "\t"<< "|AC-Class Fare" << "\t";
                cout<<endl;
                displayFileContent("Train_details.txt");
                break;

            case 2:
                R.pdetails();
                str = R.gen_pdetails();
                file.open(filename, ios::in|ios::out|ios::app);
                file<<str<<endl;
                file.close();
                break;

            case 3:
                cout<<"Enter your PNR number: ";
                cin>>pnr;

                x = search(filename, pnr);
                if(x != "NULL"){
                    file.open(filename, ios::in | ios::out | ios::app);
                    temp.open("temp.txt", ios::in | ios::out | ios::app);
                    while(getline(file, line)) {
                        if(line != x){
                            temp<<line<<endl;
                        }
                    }
                    temp.close();
                    file.close();

                    remove("reservation.txt");
                    rename("temp.txt", "reservation.txt");
                }

                break;

            case 4:
                cout<<"Enter your PNR number: ";
                cin>>pnr;

                cout<<"Your Reservation Data: "<<endl;
                cout<<endl;
                x = search(filename, pnr);
                if(x!="NULL"){
                    v = simple_token(x);
                    cout<<"Train Code: "<<v[0]<<" "<<"PNR number: "<<v[1]<<" "<<v[2]<<" "<<"Category: "<<v[3]<<endl;
                    cout<<"Name: "<<"\t"<<"Age: "<<endl;
                    for(auto it = v.begin()+4; it<v.end(); it++) {
                        cout<<*it<<" ";
                    }
                }
                cout<<endl;
                break;

            case 5:
                file.open("e_ticket.txt", ios::in | ios::out);
                head = "********************************* E-Ticket *********************************";
                sub_head = "\t*********** Case 7 Railway Reservation System ***********";
                cout<<"Enter your PNR number: ";
                cin>>pnr;

                x = search(filename, pnr);
                if(x!="NULL"){
                    file<<head<<endl;
                    file<<sub_head<<endl;
                    v = simple_token(x);
                    file<<"\n\nTrain code: "<<v[0]<<endl;
                    file<<"PNR number: "<<v[1]<<endl;
                    file<<v[2]<<endl;
                    file<<"Category: "<<v[3]<<endl;
                    file<<"Name: "<<"\t\t"<<"Age: "<<endl;
                    // cout<<v.size();
                    for(int i = 4; i<v.size(); i++) {
                        file<<v[i]<<" ";
                    }
                    cout<<endl;
                }

                cout<<"Your E-Ticket is Generated"<<endl<<endl;
                
                break;

            case 6:
                break;

            default:
                cout<<"Enter a valid option"<<endl;
                break;
        }

    }while(option!=6);
}

void login_signin(Admin &A, const string &filename, Train &T) {

    fstream file(filename);
    A.get_admin_details();

    string searchStr = A.get_user_name() + " " + A.get_user_pass();
    string x = search(filename, searchStr);

    if(x != "NULL") {
        cout<<"Successfully Logined"<<endl;
        admin_management(T);
    }else{
        cout<<"Don't have any Account? Sign Up"<<endl;
    }
}

void login_signin_p(Passenger &P, const string &filename, Reservation &R) {

    fstream file(filename);
    P.get_p_details();

    string searchStr = P.get_user_name() + " " + P.get_user_pass();
    string x = search(filename, searchStr);

    if(x != "NULL") {
        cout<<"Successfully Logined"<<endl;
        user_management(R);
    }else{
        cout<<"Don't have any Account? Sign Up"<<endl;
    }
}

string search(const string & filename, const string & searchStr){
    fstream file(filename);
    string line;

    int lineNumber = 1;
    while(getline(file, line)) {
        if(line.find(searchStr) != string::npos) {
            return line;
        }
    }
    file.close();

    return "NULL";
}

vector<string> simple_token(string str) {
    stringstream ss(str);
    string word;
    vector<string> words;

    while(ss>>word){
        words.push_back(word);
    }

    return words;
}