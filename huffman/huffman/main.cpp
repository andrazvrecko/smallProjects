//
//  main.cpp
//  huffman
//
//  Created by Andraz Vrecko on 10/05/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include "binReader.hpp"
#include "binWriter.hpp"

using namespace std;

struct node{  //seznam za frekvence
    char znak;
    int frequency;
    node* next;
    node* prev;
};

struct TreeNode{  //drevo za znake
    char znak;
    int frekvenca;
    TreeNode *leviSin = NULL;
    TreeNode* desniSin = NULL;
};

struct comp{
    bool operator()(TreeNode* st, TreeNode* nd){
        return (st->frekvenca > nd->frekvenca);
    }
};

node* head = NULL;
node* tail = NULL;
priority_queue<TreeNode*, vector<TreeNode*>, comp> minTree; //drevo s kodami
map<char, string> crka_koda; //kode

node* deli(node* a, node* b){
    int pe;
    pe= a->frequency;
    node* low = a;
    node* high = b;
    bool lind = false;
    while(lind == false){
        while(low->frequency <= pe and low != b){
            low = low->next;
            if(low == high){
                lind = true;
            }
        }
        while(high->frequency >= pe and high != a){
            high = high->prev;
            if(low == high){
                lind = true;
            }
        }
        if(lind == false){
            int tempo = low->frequency;
            char znak = low->znak;
            low->znak = high->znak;
            high->znak = znak;
            low->frequency = high->frequency;
            high->frequency = tempo;
        }
        
    }
    int tempo2 = a->frequency;
    a->frequency = high->frequency;
    high->frequency = tempo2;
    char znak2 = a->znak;
    a->znak = high->znak;
    high->znak = znak2;
    return high;
}

void quicksort(node* a, node* b){
    if(a != b){
        node* j = deli(a, b);
        if(a != j){
            quicksort(a, j->prev);
        }
        if(b != j){
            quicksort(j->next, b);
        }
    }
}


void createnodeglava(int a, char b)
{
    node *temp=new node;
    temp->znak=b;
    temp->frequency = a;
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
    }
}

void createList(int a[256], const char* text){
    for(int i=0; text[i] != '\0'; i++){
        a[text[i]]++;
    }
    for(int i=0; i < 256; i++){
        if(a[i] != 0){
            createnodeglava(a[i], (char)i);
        }
    }
    quicksort(head, tail);
}

void fillVec(vector<char> &a, vector<int> &b){
    node* temp = head;
    while(temp){
        a.push_back(temp->znak);
        b.push_back(temp->frequency);
        temp = temp->next;
    }
}


void Izpis(struct TreeNode* root, string koda)
{
    if (root==NULL){
        return;
    }
    if (root->znak != '$'){
        cout << root->znak << ": " << koda << endl;
    }
    Izpis(root->leviSin, koda + "0");
    Izpis(root->desniSin, koda + "1");
}



void ZgradiDrevo(vector<char> znak, vector<int> frekv){
    struct TreeNode *levo;
    struct TreeNode *desno;
    struct TreeNode *zgoraj;
    int size = znak.size();
    
    for (int i = 0; i < size; ++i){
        TreeNode* temp = new TreeNode;
        temp->znak = znak[i];
        temp->frekvenca = frekv[i];
        minTree.push(temp);
    }

    while(minTree.size() != 1){
        
        levo = minTree.top();
        minTree.pop();
        
        desno = minTree.top();
        minTree.pop();

        zgoraj = new TreeNode;
        zgoraj->znak = '$';
        zgoraj->frekvenca = levo->frekvenca+desno->frekvenca;
        
        zgoraj->leviSin = levo;
        zgoraj->desniSin = desno;
        
        minTree.push(zgoraj);
    }
}


void kodiranje(const char* text, vector<char> a, vector<int> b, int len){
    //ofstream out;
    //out.open("testoutput.bin", std::ios::binary);
    int temp = 0;
    int velprvot = 0;
    int velkomp = 0;
    velprvot = len * 8;
    for(int j = 0; j < a.size(); j++){
        temp = crka_koda[a[j]].length()*b[j];
        //cout << crka_koda[a[j]] << " " << b[j]<< endl;
        velkomp = velkomp + temp;
    }
    
    string tempkoda ="";
    
    BinWriter* izhod = new BinWriter("out.bin");
    izhod->writeInt(velkomp);
    izhod->writeInt(a.size());
    for(int z = 0; z < a.size(); z++){
        izhod->writeByte(a[z]);
        izhod->writeInt(b[z]);
    }

    
    int i=0;
    while(text[i] != '\0'){
        tempkoda = crka_koda[text[i]];
        //cout << "|" << tempkoda << "|";
        for(int j = 0; j < tempkoda.length(); j++){
            izhod->writeBit('1' == tempkoda[j]);
            //cout << tempkoda[j];
        }
        i++;
    }
    delete izhod;
    
    cout <<"Kodiranje: " <<  velprvot << "/" << (velkomp + (a.size()*8 + b.size()*4*8)+2*4*8) << endl;
    
}

void mapiranje(struct TreeNode* root, string koda){
    if (root==NULL)
        return;
    if (root->znak != '$'){
        crka_koda[root->znak]=koda;
    }
    mapiranje(root->leviSin, koda + "0");
    mapiranje(root->desniSin, koda + "1");
}

void dekodiranje(string pot){
    
    
    BinReader* dekoder = new BinReader(pot);
    int stbitov;
    int veltabele;
    stbitov = dekoder->readInt();
    veltabele = dekoder->readInt();
    vector<int> frek;
    vector<char> znak;
    for(int i = 0; i < veltabele; i++){
        znak.push_back(dekoder->readByte());
        frek.push_back(dekoder->readInt());
    }
    ZgradiDrevo(znak, frek);
    mapiranje(minTree.top(), "");
    string besedilo = "";
    //while(dekoder->EOF_ext != true){
    for(int i = 0; i < stbitov;i++){
        besedilo += (dekoder->readBit()) ? "1" : "0";
    }
    
    string dekodirantext = "";
    int i = 0;
    struct TreeNode* src = minTree.top();
    while(besedilo[i] != '\0'){
        if (besedilo[i] == '0'){
            src = src->leviSin;
        }
        else{
            src= src->desniSin;
        }
        if (src->leviSin==NULL and src->desniSin==NULL){
            dekodirantext += src->znak;
            src = minTree.top();
        }
        i++;
    }
    cout << dekodirantext << endl;
    delete dekoder;
}


int main(int argc, const char * argv[]) {
    string compare = argv[1];
    
    if(compare == "c"){
       // cout << "Active " << argv[1];
        fstream input;
        input.open(argv[2]);
        string contents((std::istreambuf_iterator<char>(input)),
                        istreambuf_iterator<char>());
        const char* text = contents.c_str();
        input.close();
        
        size_t txt = strlen(text);
        
        
        int count[256] = {0};
        
        createList(count, text); //ustvari seznam z frekvenco in ga sortira
        vector<int> frekvenca;
        vector<char> znaki;
        fillVec(znaki, frekvenca); //napolni vektorja s crkami in frekvencami
        ZgradiDrevo(znaki, frekvenca);
        mapiranje(minTree.top(), "");
        kodiranje(text, znaki, frekvenca, txt);
        Izpis(minTree.top(), "");
    }
    else if(compare == "d"){
        dekodiranje(argv[2]);
    }
}
