#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<mmsystem.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8
void dataout();
const char* USER_INFO_OUT = "(%s,%s,%s,%s,%c,%s,%s,%s,%.3lf,%.3lf,%.3lf)";
const char* USER_INFO_IN = "(%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lf,%lf,%lf)";
const char* TRANSACTION = "(%s,%s,%.3lf,%s)\n";
char password2[100];
void withdrawal();
typedef struct user
{
    char TCID[100];
    char fullname[100];
    char email[100];
    char phone[100];
    char gender;
    char address[100];
    char password[100];
    char customerID[100];
    double balance;
    double savings;
    double debt;
}user;
FILE *data;
char* datafolder = "transactions.dat";
user usr1; //used in sign up function

void registar();
void customerid(char *id);
void menu();
int main(){
    
    srand(time(0));
    system("color 31");
    
    registar();

    return 0;
}

//------------------Mistake Alarm Sound---------------------
void allert(){
    Beep(800,300);
    PlaySound(TEXT("Sounds\\invalid.wav"),NULL,SND_ASYNC);
    Sleep(3000);
}

//---------------- Creating Customer ID ---------------------
void customerid(char *id) {
  int i;
  for (i = 0; i < 10; i++) {
    id[i] = rand() % 10 + '0';
  }
  id[i]= 0;
}

//---------------- Take Input From User----------------------------

void takeinput(char usr[100]){
    fgets(usr,100,stdin);
    usr[strlen(usr)-1] = 0;
}

//----------------***TAKE PASSWORD *** ---------------------------
void takepassword(char pwd[100]){
    int i = 0;
    char ch;
    while (1){
        ch = getch();
        if(ch == ENTER || ch == TAB){
            pwd[i] = '\0';
            break;
            }
        else if(ch == BCKSPC){
            if(i>0){
                i--;
                printf("\b \b");
            }
            else{
                Beep(800,300);
            }
        }
        else{
            pwd[i] = ch;
            i++;
            printf("* \b");
        }

    }
}

//----------------------------SIGN UP A NEW ACCOUNT OPTION ------------------------
void signup(){
    FILE *fp;
    system("cls");
    printf("\n\t\t\t--------------REGISTER A NEW ACCOUNT--------------\n\n\n");
    
    printf("\n\tEnter Your Full Name:\t");
    fgetc(stdin);
    takeinput(usr1.fullname);
    printf("\n\tEnter Your Tc. ID NO:\t");
    takeinput(usr1.TCID);
    printf("\n\tEnter Your e-mail:\t");
    takeinput(usr1.email);
    printf("\n\tEnter Your Phone No:\t");
    takeinput(usr1.phone);
    printf("\n\tEnter Your Gender M/F:\t");
    scanf("%c", &usr1.gender);
    fgetc(stdin);
    printf("\n\tEnter Your address:\t");
    takeinput(usr1.address);
    printf("\n\tEnter Your password:\t");
    takepassword(usr1.password);
    printf("\n\tEnter Your password again:\t");
    takepassword(password2);
    if(!strcmp(usr1.password, password2)){
        customerid(usr1.customerID);
        system("cls"); 
        char folder[100] = "users\\";
        strcat(folder,usr1.customerID);
        strcat(folder, ".dat");
        fp = fopen(folder, "a+");
        fprintf(fp, USER_INFO_OUT, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, usr1.gender, usr1.address, usr1.password, usr1.customerID, usr1.balance, usr1.savings, usr1.debt);
        printf("\n\t\t\t--------------REGISTERATION COMPLETED--------------\n\n\n");
        PlaySound(TEXT("Sounds\\signupdone.wav"),NULL,SND_ASYNC);
        printf("\n\tYou succesfully created an account %s", usr1.fullname);
        printf("\n\tThis is your Customer ID:\t%s", usr1.customerID);
        printf("\n\nSave Your Customer ID to Log in to Your account later!");
        fseek(fp, 0, SEEK_SET);
        fclose(fp);
    }else{
        PlaySound(TEXT("Sounds\\invpass.wav"),NULL,SND_ASYNC);
        printf("\n\n\t Redirecting to main menu...");
        Sleep(4000);
        registar();
    }

}

//--------------------------------------------LOG IN FUNCTION---------------------
void login(){
    FILE *f;
    system("cls");
    printf("\n\t\t\tWELLCOME BACK TO AVCI BANK\n\n");
    printf("\n\t\tPlease enter Your Customer ID: \t");
    fgetc(stdin);
    takeinput(usr1.customerID);
    char folder[100] = "users\\";
    strcat(folder,usr1.customerID);
    strcat(folder, ".dat");
    f = fopen(folder, "r");
    if (f== NULL)
    {
        printf("\n\n\tSorry This Account Doesn't Exist.\n\t Contact us for further information or Create a new account");
        system("pause");
        registar();
    }
    else{
        fseek(f, 0, SEEK_SET);
        fscanf(f, USER_INFO_IN, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, &usr1.gender, usr1.address, usr1.password,usr1.customerID, &usr1.balance, &usr1.savings, &usr1.debt);
        printf("\n\tEnter Your Password:\t");
        fclose(f);
        takepassword(password2);
        while (strcmp(usr1.password, password2))
        {
            system("cls");
            printf("\n\n\tInvalid Password for %s\n\n\tPlease Enter Your Password:\t", usr1.customerID);
            takepassword(password2);
        }
        system("cls");
        printf("Wellcome back %s...", usr1.fullname);
        Sleep(1000);
        printf("\b \b");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf("\b \b");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        system("cls");
        //uploaded menu animation
        menu();
    }
    
}

//--------------------------Create Account or Log in----------------
void registar(){
    int opt;
    system("cls");
    printf("\n\t\t\tWELLCOME TO AVCI BANK\n\n");
    printf("\n\t1. Sign Up");
    printf("\n\t2. Sign In\n\n");
    printf("\tChoose Your Operation (1/2):\t");
    PlaySound(TEXT("Sounds\\register.wav"),NULL,SND_ASYNC);
    Sleep(4000);
    scanf("%d", &opt);
    while(opt !=1 && opt != 2){
        system("color 0b");
        allert();
        printf("\n\tInvalid choise! Please try again\n\t");
        system("cls");
        printf("\n\t1. Sign Up");
        printf("\n\t2. Sign In\n\n");
        printf("\tChoose Your Operation (1/2):\t");
        PlaySound(TEXT("Sounds\\register.wav"),NULL,SND_ASYNC);
        Sleep(1000);
        scanf("%d", &opt);
    }
    switch (opt)
    {
    case 1:
        printf("\n\tsign up");
        signup();
        char opt1;
        printf("\n\tDo you want to continue? (y/n):\t");
        scanf("%c", &opt1);
        switch (opt1)
        {
        case 'y':
            menu();
            break;
        
        case 'Y':
            menu();
            break;
        default:
            break;
        }
        break;
    case 2:
        login();
        printf("\n\tsign in");
        break;
    
    }
}
//---------------------------- EDIT ACCOUNT FUNCTION ---------------------------------------
void editaccount(){
    FILE *f1;
    char folder[100] = "users\\";
    strcat(folder,usr1.customerID);
    strcat(folder, ".dat");
    f1 = fopen(folder, "w+");
    system("cls");
    printf("\n\n\t-------------------- ||EDIT ACCOUNT|| --------------------\n\n");
    printf("\n\tOptions:\n\t1.Phone:\n\t2.Address:\n\t3.Password:\n\tChoose An Option:\t");
    char op2;
    char op1;
    scanf("%c", &op2);
    if(op2 == '1'){
        printf("\n\n\tEnter New Phone Number:\t");
        fgetc(stdin);
        takeinput(usr1.phone);
    }else if(op2 =='2'){
        printf("\n\n\tEnter New Address:\t");
        fgetc(stdin);
        takeinput(usr1.address);
    }else if(op2 =='3'){
        printf("\n\n\tEnter New Password:\t");
        fgetc(stdin);
        takepassword(usr1.password);
        printf("\n\tEnter Your password again: ");
        takepassword(password2);
    }else{
        printf("\n\tInvalid Option");
        PlaySound(TEXT("Sounds\\invalid.wav"),NULL,SND_ASYNC);
        Sleep(3000);
        editaccount();
    }
    dataout(usr1.customerID);
    printf("\n\tDo You want To Continue?(y/n)");
    scanf("%c", &op1);
    switch (op1)
        {
        case 'y':
            menu();
            break;
        case 'Y':
            menu();
            break;
        default:
            fseek(f1, 0, SEEK_SET);
            fprintf(f1, USER_INFO_OUT, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, usr1.gender, usr1.address, usr1.password, usr1.customerID, usr1.balance, usr1.savings, usr1.debt);
            printf("\n\tThanks for usink our System!");
            Sleep(2000);
            break;
        }

}

//--------------------------------------------------- WITHDRAW MONEY FROM ACCOUNT ------------------------------------------
void withdrawal(){
    double withdraw = 0;
    system("cls");
    printf("\n\n\t-------------------- ||WITHDRAW MONEY|| --------------------\n\n");
    printf("\n\tYour Balance: %.2lf" ,usr1.balance);
    printf("\n\tWithdrawal Amount: \t");
    
    scanf("%lf",&withdraw);
    if(withdraw<usr1.balance && withdraw>10){
        usr1.balance -= withdraw;
        printf("\n\tWithdrawal Successful!");
        data = fopen(datafolder,"a+");
        fprintf(data,TRANSACTION,usr1.customerID,"Withdrawal completed",withdraw,"USD");
        fclose(data);
        dataout(usr1.customerID);
        menu();

    }
    else{
        printf("\n\tInsufficiant or too low amount. Should be between 10 and your balance");
        Sleep(2000);
        fgetc(stdin);
        menu();
    }
    
}

//------------------------------------------- DEPOSIT MONEY TO ACCOUNT -----------------------------------------
void deposit(){
    system("cls");
    printf("\n\n\t-------------------- ||DEPOSIT MONEY|| --------------------\n\n");
    printf("\n\tYour Balance: %.2lf" ,usr1.balance);
    printf("\n\tDeposit Amount: \t");
    double depo;
    scanf("%lf",&depo);
    usr1.balance += depo;
    printf("\n\tDeposit Successful!");
    data = fopen(datafolder,"a+");
    fprintf(data,TRANSACTION,usr1.customerID,"Deposit completed",depo,"USD");
    fclose(data);
    dataout(usr1.customerID);
    menu();
}
//--------------------------------------- TRANSFER MONEY --------------------------------------------------------------------
void transfer(){
    system("cls");
    printf("\n\n\t-------------------- ||TRANSFER MONEY|| --------------------\n\n");
    FILE *user2;
    printf("\n\tYour Balance: %.2lf" ,usr1.balance);
    printf("\n\tYour Balance: %.2lf\n\n" ,usr1.savings);
    printf("\n\tChoose An Option:\n\t1. Transfer To Savings Account\n\t2. Transfer From Savings Account\n\t3. Transfer To Anouther Account\n\tEnter an Option:\t");
    char opttransfer = ' ';
    opttransfer = getch();
    system("cls");
    switch (opttransfer)
    {
    case '1':
        printf("\n\n\t-------------------- ||TRANSFER TO SAVINGS|| --------------------\n\n");
        printf("\n\tTransfer Amount: \t");
        double trans;
        scanf("%lf",&trans);
        if (trans <= usr1.balance)
        {
            usr1.balance -= trans;
            usr1.savings += trans;
            dataout(usr1.customerID);
            printf("\n\tTransfer Completed! You can check your account details from the menu!");
            Sleep(1500);
            menu();
        }
        else{
            printf("\n\tSorry something went wrong! Please try again later.");
            Sleep(1500);
            menu();
        }
        
        break;
    case '2':
        printf("\n\n\t-------------------- ||TRANSFER FROM SAVINGS|| --------------------\n\n");
        printf("\n\tTransfer Amount: \t");
        double transa;
        scanf("%lf",&transa);
        if (transa <= usr1.savings)
        {
            usr1.balance += transa;
            usr1.savings -= transa;
            dataout(usr1.customerID);
            printf("\n\tTransfer Completed! You can check your account details from the menu!");
            Sleep(1500);
            menu();
        }
        else{
            printf("\n\tSorry something went wrong! Please try again later.");
            Sleep(1500);
            menu();
        }
        
        break;
    case '3':
        printf("\n\tTransfer Amount: \t");
        double transx;
        scanf("%lf",&transx);
        printf("\n\tThe Transfer Account:\t");
        user usr2;
        fgetc(stdin);
        takeinput(usr2.customerID);
        char folder1[100] = "users\\";
        strcat(folder1,usr2.customerID);
        strcat(folder1, ".dat");
        user2 = fopen(folder1, "r");
        if(user2 == NULL){
            printf("Sorry This Account Doesn't exist");
            menu();
        }
        else{
            fseek(user2, 0, SEEK_SET);
            fscanf(user2, USER_INFO_IN, usr2.fullname, usr2.TCID, usr2.email, usr2.phone, &usr2.gender, usr2.address, usr2.password,usr2.customerID, &usr2.balance, &usr2.savings, &usr2.debt);
            fclose(user2);
        
            if(transx <= usr1.balance){
                usr1.balance -= transx;
                usr2.balance += transx;
                dataout(usr1.customerID);
                user2 = fopen(folder1, "w+");
                fseek(user2, 0, SEEK_SET);
                fprintf(user2, USER_INFO_OUT, usr2.fullname, usr2.TCID, usr2.email, usr2.phone, usr2.gender, usr2.address, usr2.password, usr2.customerID, usr2.balance, usr2.savings, usr2.debt);
                fclose(user2);
                data = fopen(datafolder,"a+");
                fprintf(data,TRANSACTION,usr1.customerID,"Transfer completed",trans,usr2.customerID);
                fclose(data);
                printf("\nTransfer Completed!");
                menu();


            }
            else{
                menu();
            }

        }

    default:
        menu();
        break;
    }
    
    
    

}

//-------------------------------------------------- VIEW ACCOUNT INFORMATION -------------------------------------------------
void viewaccount(){
    char goback;
    system("cls");
        printf("\n\n\t-------------------- ||%20s ACCOUNT|| --------------------\n\n",usr1.fullname);
        printf("\n\tFull Name:\t%50s\n\tTC NO:\t%50s\n\tPhone No.:\t%50s\n\tCustomer ID:\t%50s\n\tE-mail:\t%50s\n\tGender:\t%50c\n\tAddress:\t%50s", usr1.fullname,usr1.TCID,usr1.phone,usr1.customerID,usr1.email,usr1.gender,usr1.address);
        printf("\n\n\n\tAccount Balance:\t%20.2lf", usr1.balance);
        printf("\n\tSavings Account:\t%20.2lf", usr1.savings);
        double a = usr1.savings * 1.04;
        printf("\n\tYou will Have %.2lf In this savings account end of this year. ",a);
        printf("\n\tAccount Debts:\t%20.2lf", usr1.debt);
        double b = usr1.debt / 12;
        printf("\n\tYou have to pay %.2lf Amount of Money Monthly", b);
        printf("\n\tDo you want to continue? (y/n):\t");
        goback =  getch();
        switch (goback)
        {
        case 'y':
        case 'Y':
            system("cls");
            menu();
            break;
        
        default:
            printf("\n\tThanks for using our System!");
            Sleep(2000);
            break;
        }
}


//-------------------------------------------- WRITE TO FOLDER
void dataout(char a[100]){
FILE *fout;
char folder[100] = "users\\";
strcat(folder,a);
strcat(folder,".dat");
remove(folder);
fout = fopen(folder, "w+");
fprintf(fout, USER_INFO_OUT, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, usr1.gender, usr1.address, usr1.password, usr1.customerID, usr1.balance, usr1.savings, usr1.debt);
fclose(fout);
    
}

void menu(){
    system("cls");
    char opt11 = ' ';
    FILE *f1;
    /*char *folder = "users\\";
    strcat(folder,usr1.customerID);
    strcat(folder, ".dat");
    f1 = fopen(folder, "w+");
    fseek(f1, 0, SEEK_SET);
    fprintf(f1, USER_INFO_OUT, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, usr1.gender, usr1.address, usr1.password, usr1.customerID, usr1.balance, usr1.savings, usr1.debt);
    fseek(f1, 0, SEEK_SET);
    fscanf(f1, USER_INFO_IN, usr1.fullname, usr1.TCID, usr1.email, usr1.phone, &usr1.gender, usr1.address, usr1.password,usr1.customerID, &usr1.balance, &usr1.savings, &usr1.debt);
    fclose(f1);*/
    printf("\n\n\t-------------------- ||MAIN MENU|| --------------------\n\n");
    printf("\n\tOptions:\n\t1.View Account Information:\n\t2.Edit Account:\n\t3.Widthdraw Money:\n\t4.Deposit Money:\n\t5.Send Money\n\t6.Exit\n\tChoose An Option:\t");
    opt11 = getch();
    switch (opt11)
    {
    case '1':
        viewaccount();
        break;
    case '2':
        editaccount();
        break;
    case '3':
        withdrawal();
        break;
    case '4':
        deposit();
        break;
    case '5':
        transfer();
        break;
    case '6':
        dataout(usr1.customerID);
        printf("\nThanks For Preferring Us!");
        Sleep(1000);
        break;
    
    default:
        PlaySound(TEXT("Sounds\\invalid.wav"),NULL,SND_ASYNC);
        menu();
    }
}