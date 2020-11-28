//
//  main.cpp
//  grucenje
//
//  Created by Andraz Vrecko on 12/06/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;
struct Tocka{
    double x = NULL;
    double y = NULL;
    int najblizjiK = NULL;
};
double randomDouble(double spM, double zgM){
    double db = (double)rand() / RAND_MAX;
    return spM + db * (zgM - spM);
}

void readTocke(vector<Tocka> &a, string path){ //prebere tocke iz datoteke
    ifstream inpt;
    inpt.open(path);
    double prva;
    double druga;
    Tocka temp;
    while(inpt){
        if(inpt.eof()){
            break;
        }
        inpt>>prva>>druga;
        temp.x = prva;
        temp.y = druga;
        a.push_back(temp);
    }
}
double findXMax(vector<Tocka> a){
    double min = a[0].x;
    for(int i = 0; i < a.size();i++){
        if(a[i].x > min){
            min = a[i].x;
        }
    }
    return min;
}
double findYMax(vector<Tocka>a){
    double min = a[0].x;
    for(int i = 0; i < a.size();i++){
        if(a[i].y > min){
            min = a[i].y;
        }
    }
    return min;
}
double findXMin(vector<Tocka> a){
    double min = a[0].x;
    for(int i = 0; i < a.size();i++){
        if(a[i].x < min){
            min = a[i].x;
        }
    }
    return min;
}
double findYMin(vector<Tocka>a){
    double min = a[0].x;
    for(int i = 0; i < a.size();i++){
        if(a[i].y < min){
            min = a[i].y;
        }
    }
    return min;
}

void izracunK(vector<Tocka> &tocke, vector<Tocka> b){
    vector<double> tempDolzine; // vector z dolzinami
    int dolzina;
    int najkrajsa = 0;
    int l;
    for(int j = 0; j < tocke.size();j++){ // ponavlja za vsako tocko
        tempDolzine.clear(); // na zacetku se sprazni
        
        for(int i = 0; i < b.size(); i++){ // ponavlja za vsak k
            dolzina = (tocke[j].x - b[i].x)*(tocke[j].x - b[i].x) + (tocke[j].y - b[i].y)*(tocke[j].y - b[i].y);
            tempDolzine.push_back(dolzina);//izracuna dolzino in jo da v vector
        }
        najkrajsa = 0;
        
        l=0;
        for(l; l < tempDolzine.size();l++){
            if(tempDolzine[l] < tempDolzine[najkrajsa]){
                najkrajsa=l; // poisce najkrajso izmed k dolzin
            }
        }
        tocke[j].najblizjiK = najkrajsa;
    }
}

void iniGruce(vector<Tocka> &a, int k, vector<Tocka> b){ //inicializacija gruc
    Tocka temp;
    double prva;
    double druga;
    int minX = findXMin(b);// poisce vse meje
    int maxX = findXMax(b);
    int minY = findYMin(b);
    int maxY = findYMax(b);
    
    for(int i = 0;i < k;i++){
        prva = randomDouble(minX, maxX);
        druga = randomDouble(minY, maxY);//random koordinata med mejami
        temp.x = prva;
        temp.y = druga;
        a.push_back(temp);
    }
}

void grucenje(vector<Tocka>gruce, int t, vector<Tocka> tocke){
    double vsotaX=0;
    double counter = 0;
    double novaVel;
    for(int i = 0; i < t;i++){
        for(int j = 0; j < gruce.size();j++){
            for(int l = 0; l < tocke.size();l++){
                if(tocke[l].najblizjiK == j){
                    vsotaX += tocke[l].x;
                    counter++;
                }
            }
            if(counter > 0){
                novaVel=vsotaX/counter;
                gruce[j].x = novaVel;
            }
            vsotaX = 0;
            counter  = 0;
            for(int l = 0; l < tocke.size();l++){
                if(tocke[l].najblizjiK == j){
                    vsotaX += tocke[l].y;
                    counter++;
                }
            }
            if(counter > 0){
                novaVel=vsotaX/counter;
                gruce[j].y = novaVel;
            }
            vsotaX=0;
            counter=0;
        }
        izracunK(tocke, gruce);
        //cout << endl << endl;
        for(int i = 0; i < tocke.size();i++){
            //cout << tocke[i].x << " " << tocke[i].y << " - " << gruce[tocke[i].najblizjiK].x<<" " << gruce[tocke[i].najblizjiK].y << endl;
        }
        //cout << "GRUCE: "<<endl;
        for(int i = 0; i < gruce.size();i++){
            //cout << gruce[i].x << " " << gruce[i].y << endl;
        }
    }
    ofstream output;
    output.open("out.txt");
    //cout << endl << "Izpis: " << endl;
    for(int i = 0; i < tocke.size();i++){
        output << i << " " << tocke[i].najblizjiK << endl;
    }
    output.close();
}

int main(int argc, const char * argv[]) {
    int stIt = atoi(argv[1]);
    int stGr = atoi(argv[2]);
    string path = argv[3];
    srand(time(NULL));
    int k = stGr;
    int t = stIt;
    vector<Tocka> gruce;
    vector<Tocka> tocke;
    readTocke(tocke, path);
    iniGruce(gruce, k, tocke);
    izracunK(tocke, gruce);

    
    
    
    
    /*for(int i = 0; i < tocke.size();i++){
        cout << tocke[i].x << " " << tocke[i].y << " - " << gruce[tocke[i].najblizjiK].x<<" " << gruce[tocke[i].najblizjiK].y << endl;
    }
    cout << "GRUCE: "<<endl;
    for(int i = 0; i < gruce.size();i++){
        cout << gruce[i].x << " " << gruce[i].y << endl;
    }*/
    
    grucenje(gruce, t, tocke);
    return 0;
}
