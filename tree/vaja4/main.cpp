//
//  main.cpp
//  vaja4
//
//  Created by Andraz Vrecko on 24/03/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>

using namespace std;

struct node{
    int vrednost;
    node* oce = NULL;
    node* leviSin = NULL;
    node* desniSin = NULL;
};

node* head = NULL;


void vstavi(int k){
    /*if(head == NULL){
     node* newhead = new node;
     head = newhead;
     head->vrednost = k;
     }
     else{
     node* y = new node;
     node* temphead = head;
     while(temphead != NULL){
     temphead = y;
     if(temphead->vrednost < k){
     y = temphead->desniSin;
     }
     else if(temphead->vrednost > k){
     y =  temphead->leviSin;
     }
     else{
     cout << "error";
     return;
     }
     }
     node *z =  new node;
     z->vrednost = k;
     z->oce = y;
     if(y->vrednost < k){
     y->desniSin = z;
     }
     else if(y->vrednost > k){
     y->leviSin = z;
     }
     else{
     cout << "error";
     }
     }*/
    node* y = new node;
    node* temphead = head;
    while(temphead != NULL){
        y = temphead;
        if(temphead->vrednost < k){
            temphead = temphead->desniSin;
        }
        else if(temphead->vrednost > k){
            temphead =  temphead->leviSin;
        }
        else{
            cout << "error";
            return;
        }
    }
    node* z = new node;
    z->vrednost = k;
    z->oce = y;
    if(head == NULL){
        head = z;
        cout << "Uspesen vnos \n";
    }
    else if(y->vrednost < k){
        y->desniSin = z;
        cout << "Uspesen vnos \n";
    }
    else if(y->vrednost > k){
        y->leviSin = z;
        cout << "Uspesen vnos \n";
    }
}

void urejenIzpis(node* x){
    if(x != NULL){
        urejenIzpis(x->leviSin);
        cout << x->vrednost;
        urejenIzpis(x->desniSin);
    }
}

void izpisPovezav(node* x){
    if(x != NULL){
        if(x->leviSin != NULL){
            cout << "L: "<< x->leviSin->vrednost << " ";
            izpisPovezav(x->leviSin);
        }
        if(x->desniSin != NULL){
            cout << "D: " <<x->desniSin->vrednost << " ";
            izpisPovezav(x->desniSin);
        }
    }
    else{
        cout << "prazno";
    }
}

node* iskanje(node* x, int k){
    while(x != NULL and k != x->vrednost){
        if(k > x->vrednost){
            x=x->desniSin;
        }
        else{
            x=x->leviSin;
        }
    }
    if(x == NULL){
        cout << "Ne obstaja \n";
        return NULL;
    }
    else{
        //cout << x->vrednost << endl;
        return x;
    }
}

int minimum(node* temp){
    int x = 0;
    while(temp->leviSin != NULL){
        temp = temp->leviSin;
    }
    x = temp->vrednost;
    return x;
}

int maximum(node* temp){
    int x = 0;
    while(temp->desniSin != NULL){
        temp = temp->desniSin;
    }
    x = temp->vrednost;
    return x;
}

void minmax(node* x){
    if(x != NULL){
        int min = minimum(head);
        int max = maximum(head);
        cout << "Minimum: " << min << endl << "Maximum: " << max << endl;
    }
    else{
        cout << "Prazno \n";
    }
}
node* naslednjik(int k){
    node* iskan = iskanje(head, k);
    if(iskan != NULL){
        if(iskan->desniSin != NULL){
            cout << minimum(iskan->desniSin) << endl;
            return iskanje(head, minimum(iskan->desniSin));
        }
        else{
            node* y = iskan->oce;
            while(y != NULL and iskan == y->desniSin){
                iskan = y;
                y= y->oce;
            }
            //cout << y->vrednost;
            return y;
        }
    }
    cout << "Ne obstaja \n";
    return NULL;
}

node* predhodnik(int k){
    node* iskan = iskanje(head, k);
    if(iskan != NULL){
        if(iskan->leviSin != NULL){
            cout << maximum(iskan->leviSin) << endl;
            return iskanje(head, maximum(iskan->leviSin));
        }
        else{
            node* y = iskan->oce;
            while(y!=NULL and iskan == y->leviSin){
                iskan = y;
                y= y->oce;
            }
            //cout << y->vrednost;
            return y;
        }
    }
    cout << "Ne obstaja \n";
    return NULL;
}

void nasledpred(int k){
    node* prejsnji = predhodnik(k);
    node* naslednji = naslednjik(k);
    cout << "Predhodnik: " << prejsnji->vrednost << endl << "Naslednjik: " << naslednji->vrednost << endl;
}

void brisi(int k, node* T){
    node* z = iskanje(head, k);
    node* y = new node;
    node* x = new node;
    if(T != NULL){
        if(z == head and z->leviSin == NULL and z->desniSin == NULL){
            head = NULL;
        }
        if(z->leviSin == NULL or z->desniSin == NULL){
            y = z;
        }
        else{
            y= naslednjik(z->vrednost);
        }
        if(y->leviSin != NULL){
            x = y->leviSin;
        }
        else{
            x = y->desniSin;
        }
        if(x != NULL){
            x->oce = y->oce;
        }
        if(y->oce == NULL){
            T = x;
        }
        else{
            if(y == y->oce->leviSin){
                y->oce->leviSin = x;
            }
            else{
                y->oce->desniSin = x;
            }
        }
        if(y != z){
            z->vrednost = y->vrednost;
        }
        y = NULL;
    }
    else{
        cout << "Ne obstaja \n";
    }
}

char menu() {
    cout << "--------------------------------------- \n";
    cout << "MENI \n";
    cout << "1 - VNOS\n";
    cout << "2 - UREJEN IZPIS\n";
    cout << "3 - IZPIS POVEZAV\n";
    cout << "4 - ISKANJE\n";
    cout << "5 - POISCI MIN IN MAX\n";
    cout << "6 - POISCI PREDHODNIKA IN NASLEDNJIKA\n";
    cout << "7 - BRISI VREDNOST\n\n";
    cout << "9 - KONEC\n\n";
    cout << "--------------------------------------- \n";
    cout << "Izberi: ";
    
    char izbira;
    cin >> izbira;
    return izbira;
}

int main(int argc, const char * argv[]) {
    int vrednost;
    int n;
    bool alive = true;
    while(alive == true){
        vrednost = menu();
        switch(vrednost){
            case '1':
                cout << "Vpisi: ";
                cin >> n;
                vstavi(n);
                break;
            case '2':
                urejenIzpis(head);
                cout << endl;
                break;
            case '3':
                izpisPovezav(head);
                cout << endl;
                break;
            case '4':
                cout << "Vpisi: ";
                cin >> n;
                iskanje(head, n);
                break;
            case '5':
                minmax(head);
                break;
            case '6':
                cout << "Vpisi: ";
                cin >> n;
                nasledpred(n);
                break;
            case '7':
                cout << "Vpisi: ";
                cin >> n;
                brisi(n, head);
                break;
            default:
                break;
        }
    }
}

