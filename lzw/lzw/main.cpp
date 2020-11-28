//
//  main.cpp
//  lzw
//
//  Created by Andraz Vrecko on 31/05/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>
#include<map>
#include <vector>
#include <algorithm>
#include <cmath>
#include "binreader.h"
#include "binwriter.h"

using namespace std;

ifstream::pos_type velikostDat(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}


void preberiFile(string pot, string &niz, int najVel){
    niz.clear();
    //pot = "outfile.bin";
    ifstream d;
    d.open(pot, ios::binary);
    int cifra;
    vector<int> stevke;
    while(d){
        d.read((char*)&cifra, najVel);
        if (!d.good())
        {
            break;
        }
        stevke.push_back(cifra);
        
        
    }
    
    map<int, string>slovar3;
    slovar3.clear();
    int i = 0;
    for(i; i < 256; i++){
        slovar3[i] = string(1,i);
    }
    
    niz = "";
    string nizTMp;
    //cout << "Prebran bin file: " << endl;
    for(int j = 0; j < stevke.size();j++){
        nizTMp = slovar3[stevke[j]];
        //cout << stevke[j] << " ";
        niz += nizTMp;
    }
    d.close();
    cout <<"NIZ: " << niz << endl << endl;
}




void kodiraj(vector<char> niz, vector<int> &koda, int najVel, int mSize){
    map<string, int>slovar;
    slovar.clear();
    int i = 0;
    for(i; i < 256; i++){
        slovar[string(1,i)] = i;
    }
    string nizKode="";
    int lenOfNiz = 0;
    int lok = 0;
    int velNiz;
    //cout << niz.size() << endl;
    while(lenOfNiz <= niz.size()){
        if(slovar.size() <= mSize){
        velNiz = niz.size();
        if(slovar[nizKode+niz[lenOfNiz]]!=NULL){
                nizKode = nizKode + niz[lenOfNiz];
            }
            else{
                //cout << slovar[T];
                koda.push_back(slovar[nizKode]);
                if(lok < velNiz){
                    slovar[nizKode+niz[lenOfNiz]]=i;
                    i++;
                }
                nizKode = niz[lenOfNiz];
            }
            lenOfNiz++;
            lok++;
        }
        else{
            nizKode = niz[lenOfNiz-1];
            koda.push_back(slovar[nizKode]);
            lenOfNiz++;
        }
    }
    
    
    //Zapis v datoteko!
    BinWriter* a = new BinWriter("out.bin");
    //cout << "Kodiran zapis: "<< endl;
    for(int i = 0; i < koda.size(); i++){
        a->writeInt(koda[i], najVel);
        //cout << koda[i] << " ";
    }
    delete a;
    
    
    int prvotna = niz.size()*8;
    int nova = velikostDat("out.bin");
    
    cout << "Kompresijsko razmerje: " << prvotna << "/" << nova << endl;
}



void dekodiraj(int najVel, vector<int> koda2, string path){
    map<int, string>slovar;
    slovar.clear();
    int i = 0;
    for(i; i < 256; i++){
        slovar[i] = string(1,i);
    }//inicializacija slovarja
    koda2.clear();
   
    ifstream iptfile;
    iptfile.open(path, ios::binary);
    
    //cout << "Prebrano kodirano: "<< endl;
    
    for(int j = 0; j < koda2.size(); j++){
        //cout << koda2[j] << " ";
    }
    
    int cifra2;
    
    while(iptfile){
        iptfile.read((char*)&cifra2, najVel);
        if (!iptfile.good())
        {
            break;
        }
        //cout << cifra2 << " ";
        koda2.push_back(cifra2);
    }
    iptfile.close();
    
    
    
    string koncenNiz="";
    string nizKode="";
    int stStevil = 0;
    string P ="";
    int velSlov;
    while(stStevil<= koda2.size()){ //gre skozi vse kode
        velSlov = slovar.size();
        if(koda2[stStevil] == velSlov){//je mejni primer
            P = nizKode[0];
            slovar[velSlov] = nizKode+P;
        }
      
        else if(nizKode != ""){
            P = slovar[koda2[stStevil]][0];
            slovar[velSlov]=nizKode + P;
        }
        nizKode = slovar[koda2[stStevil]];
        koncenNiz+= slovar[koda2[stStevil]];
        stStevil++;
    }
    
    
    
    map<string, int>slovar2;
    slovar2.clear();
    i = 0;
    for(i; i < 256; i++){
        slovar2[string(1,i)] = i;
    }
    
    
    
    
    
    int vpisna;
    string temp;
    
    
    vector<int> crke;
    int cntr = 0;
    while(koncenNiz[cntr] != '\0'){
        cntr++;
    }
    for(int j = 0; j < cntr; j++){
        temp = koncenNiz[j];
        vpisna = slovar2[temp];
        crke.push_back(vpisna);
    }
    
    cout << endl <<"Dekodiran niz: " << koncenNiz << endl;
    //cout << "Izpisan bin file vse crke: "<< endl;
    int tmp;
    
    ofstream c;
    c.open("out.bin", ios::binary);
    for(int j = 0; j < crke.size();j++){
        tmp = crke[j];
        //cout << tmp << " ";
        c.write((char*)&tmp, najVel);
        
    }
    c.close();
}


int main(int argc, const char * argv[]) {
    string compare = argv[1];
    int mSize = atoi(argv[2]);
    string pot = argv[3];
    //cout << pot;
    
    int maxSize = mSize;
    int velKomp = ceil(log2(maxSize));
    string x2;
    vector<char> niz;
    vector<int> koda;
    
    
    if(compare == "c"){
        
        preberiFile(pot, x2, velKomp);
        for(int i = 0; i < x2.length(); i++){
            niz.push_back(x2[i]);
        }

        kodiraj(niz, koda, velKomp, maxSize);
    }
    else if(compare == "d"){
        dekodiraj(velKomp, koda, pot);
       
    }
    return 0;
}
