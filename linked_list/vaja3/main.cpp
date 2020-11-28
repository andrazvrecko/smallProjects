//
//  main.cpp
//  vaja3
//
//  Created by Andraz Vrecko on 13/03/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>
#include <time.h>

using namespace std;

struct node{
    int vrednost;
    node *next;
    node *prev;
};

node* head = NULL;
node* tail = NULL;
node* temphead = NULL;

node* iskanjepod(int a){
    node *temp = head;
    while(temp){
        if(a == temp->vrednost){
            cout << "podatek obstaja \n";
            return temp;
        }
        temp = temp->next;
    }
    cout << "Podatek ne obstaja \n";
    //temp = NULL;
    return NULL;
}

void createnodeglava(int a)
{
    node *temp=new node;
    temp->vrednost=a;
    temp->next=NULL;
    temp->prev =NULL;
    
    if(head==NULL)
    {
        head=temp;
        tail=temp;
        temp=NULL;
    }
    
    else{
        temp -> next = head;
        head -> prev = temp;
        head = temp;
        //temphead = head;
    }
}

void deletenode(int a)
{
    if(head == NULL){
        cout << "Seznam je prazen"<<endl;
    }
    else{
        
        node *temp = iskanjepod(a);
        if(temp == NULL){
            cout << "Podatek ne obstaja.";
            return;
        }
        else
        {
            if(NULL == temp -> prev and NULL == temp -> next){
                head = NULL;
                tail = NULL;
            }
            else if(NULL == temp->next){
                tail = temp->prev;
                temp->prev->next = NULL;
            }
            else{
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
            }
            delete temp;
            cout << "Element je zbrisan" << endl;
        }
    }
}

void createnodeelement(int a, int iskan)
{
    node *temp= iskanjepod(iskan);
    if(NULL == temp){
        return;
    }
    else{
        node *temppod = new node;
        temppod->vrednost=a;
        temppod->next = NULL;
        temppod->prev = NULL;
        if(NULL == temp->prev and NULL == temp->next){
            temp->next = temppod;
            temppod->prev = temp;
            tail = temppod;
        }
        else if(NULL == temp->prev)
        {
            temppod -> prev = temp;
            temppod -> next = temp->next;
            temp -> next->prev = temppod;
            temp -> next = temppod;
            
        }
        else if(NULL == temp->next)
        {
            temp -> next = temppod;
            temppod -> prev = temp;
            tail = temppod;
        }
        else{
            temppod -> prev = temp;
            temppod -> next = temp->next;
            temp -> next->prev = temppod;
            temp -> next = temppod;
        }
    }
}



void createnoderep(int a)
{
    node *temp=new node;
    temp->vrednost=a;
    temp->next=NULL;
    temp->prev =NULL;
    
    if(head==NULL)
    {
        head=temp;
        tail=temp;
        temp=NULL;
    }
    
    else{
        temp -> prev = tail;
        tail -> next = temp;
        tail = temp;
        //temphead = head;
    }
}

void izpisglava(){
    if(head == NULL){
        cout << "Prazno! \n";
        return;
    }
    int izpis1= 0;
    node *temp = head;
    while(temp){
        izpis1 = izpis1 + 1;
        temp = temp->next;
    }
    node *temphead = head;
    for(int i = 0; i < izpis1; i++){
        cout << temphead -> vrednost << endl;
        temphead = temphead ->next;
    }
}

void izpisrep(){
    if(head == NULL){
        cout << "Prazno! \n";
        return;
    }
    int izpis1= 0;
    node *temp = tail;
    while(temp){
        izpis1 = izpis1 + 1;
        temp = temp->prev;
    }
    node *temphead = tail;
    for(int i = 0; i < izpis1; i++){
        cout << temphead -> vrednost << endl;
        temphead = temphead ->prev;
    }
}

char menu() {
    cout << "--------------------------------------- \n";
    cout << "MENI \n";
    cout << "1 - ISKANJE PODATKA\n";
    cout << "2 - VNOS PODATKA V GLAVO\n";
    cout << "3 - VNOS PODATKA ZA ELEMENTOM\n";
    cout << "4 - VNOS PODATKA ZA REPOM\n";
    cout << "5 - BRISANJE PODATKA\n";
    cout << "6 - IZPIS OD GLAVE DO REPA\n";
    cout << "7 - IZPIS OD REPA DO GLAVE\n";
    cout << "8 - TESTIRAJ HITROST\n\n";
    cout << "9 - KONEC\n\n";
    cout << "--------------------------------------- \n";
    cout << "Izberi: ";
    
    char izbira;
    cin >> izbira;
    return izbira;
}

void premikpolja(int polje[], int N){
    // cout << polje[0] << endl;
    for(int i = N - 1; i > 0; i--){
        polje[i] = polje[i-1];
    }
}


int main(int argc, const char * argv[]) {
    
    int izbira;
    int vrednost;
    int vrednost2;
    bool alive = true;
    int N = 0;
    int stel = 0;
    int vsota = 0;
    node* temp = head;
    node *iskan = NULL;
    clock_t start;
    clock_t finish;
    double trajanje1;
    double trajanje2;
    double trajanje3;
    double trajanje4;
    double trajanje5;
    int *polje1;
    int *polje2;
    
    
    while(alive == true){
        izbira = menu();
        switch(izbira){
            case '1':
                cout << "Vnesite vrednost: ";
                cin >> vrednost;
                iskan = iskanjepod(vrednost);
                break;
                
            case '2':
                cout << "Vnesite vrednost: ";
                cin >> vrednost;
                createnodeglava(vrednost);
                break;
                
            case '3':
                cout << "Vnesite vrednost: ";
                cin >> vrednost;
                cout << "Vnesite element: ";
                cin >> vrednost2;
                createnodeelement(vrednost, vrednost2);
                
                break;
                
            case '4':
                cout << "Vnesite vrednost: ";
                cin >> vrednost;
                createnoderep(vrednost);
                break;
                
            case '5':
                cout << "Vnesite vrednost: ";
                cin >> vrednost;
                deletenode(vrednost);
                break;
                
            case '6':
                izpisglava();
                break;
                
            case '7':
                izpisrep();
                break;
                
            case '8':
                cout << "Vpisite vrednost: ";
                cin >> N;
                
                stel = N;
                //zacetek prve
                start = clock();
                for(int i = 0; i < N; i++){
                    createnodeglava(stel);
                    stel--;
                }
                finish = clock();
                trajanje1 = (double)(finish - start)/CLOCKS_PER_SEC;
                cout << "Cas polnjenja seznama v glavo: " << trajanje1 << endl;
                
                
                temp = head;
                //zacetek druge
                start = clock();
                for(int i = 0; i < N; i++){
                    vsota = vsota + temp->vrednost;
                    temp = temp->next;
                }
                finish = clock();
                trajanje2 = (double)(finish - start)/CLOCKS_PER_SEC;
                cout << "Cas racunanja vsote seznama: " << trajanje2 << endl;
                
                
                polje1 = new int [N+1];
                polje2 = new int [N];
                //zacetek tretje
                start = clock();
                stel = N;
                for(int i = 0; i < N-1; i++){
                    polje1[0] = stel;
                    stel--;
                    premikpolja(polje1, N);
                }
                polje1[0] = 1;
                finish = clock();
                trajanje3 = (double)(finish - start)/CLOCKS_PER_SEC;
                cout << "Cas za polnjenje polja s premikom v desno: " <<trajanje3 << endl;
                
                //zacetek cetrte
                start = clock();
                stel = N;
                for(int i = 0; i < N; i++){
                    polje2[N - i - 1]=stel;
                    stel--;
                }
                finish = clock();
                trajanje4 = (double)(finish - start)/CLOCKS_PER_SEC;
                cout << "Cas za polnjenje polja od desne proti levi: " << trajanje4 << endl;
                
                //zacetek pete
                start = clock();
                vsota = 0;
                for(int i = 0; i < N; i++){
                    vsota = vsota + polje2[i];
                }
                finish = clock();
                trajanje5 = (double)(finish - start)/CLOCKS_PER_SEC;
                cout << "Cas za racunanje vsote polja: " << trajanje5 << endl;
                //cout << endl << "Vsota: "<<vsota << endl;
                
                break;
                
            case '9':
                alive = false;
                break;
                
            default:
                cout << "Napacna izbira! \n";
                break;
        }
    }
    
    
    
    return 0;
}
