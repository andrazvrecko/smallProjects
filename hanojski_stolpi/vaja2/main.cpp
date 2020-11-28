//
//  main.cpp
//  vaja2
//
//  Created by Andraz Vrecko on 12/03/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#include <iostream>

using namespace std;

char menu() {
    cout << "--------------------------------------- \n";
    cout << "MENI \n";
    cout << "Stolp iz katerega boste premikali: \n";
    cout << "1 - X\n";
    cout << "2 - Y\n";
    cout << "3 - Z\n\n";
    cout << "--------------------------------------- \n";
    cout << "Izberi: ";
    
    char izbira;
    cin >> izbira;
    return izbira;
}

char menu2() {
    cout << "--------------------------------------- \n";
    cout << "MENI \n";
    cout << "Stolp na katerega boste premiknili: \n";
    cout << "1 - X\n";
    cout << "2 - Y\n";
    cout << "3 - Z\n\n";
    cout << "--------------------------------------- \n";
    cout << "Izberi: ";
    
    char izbira;
    cin >> izbira;
    return izbira;
}
int main(int argc, const char * argv[]) {
    int X;
    cout << "Vpisite stevilo: ";
    cin >> X;
    int diski = X;
    int poljeX[100];
    int poljeY[100];
    int poljeZ[100];
    int vrhx = X - 1;
    int vrhy = -1;
    int vrhz = -1;
    int poteze = 0;
    
    for(int i = 0; i < X;i++){
        poljeX[i] = diski;
        diski = diski - 1;
    }
    while(poljeY[X - 1]!= 1){
        cout << "X: ";
        for(int i = 0; i < X; i++){
            cout << poljeX[i] << "  ";
        }
        cout << endl;
        cout << "Y: ";
        for(int i = 0; i < X; i++){
            cout << poljeY[i] << "  ";
        }
        cout << endl;
        cout << "Z: ";
        for(int i = 0; i < X; i++){
            cout << poljeZ[i] << "  ";
        }
        cout << endl;
        
        
        int izbiraa = menu();
        int izbirab;
        
        
        switch(izbiraa){
            case '1':
                izbirab = menu2();
                switch(izbirab){
                    case '1':
                        cout << "Napacna izbira \n";
                        break;
                        
                    case '2':
                        if(vrhy == -1){
                            poljeY[0] = poljeX[vrhx];
                            poljeX[vrhx] = 0;
                            vrhy = 0;
                            vrhx = vrhx-1;
                        }
                        else if(poljeY[vrhy] > poljeX[vrhx] and poljeX[vrhx] != 0){
                            poljeY[vrhy+1] = poljeX[vrhx];
                            poljeX[vrhx]=0;
                            vrhy++;
                            vrhx--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    case '3':
                        if(vrhz == -1){
                            poljeZ[0] = poljeX[vrhx];
                            poljeX[vrhx] = 0;
                            vrhz = 0;
                            vrhx = vrhx-1;
                        }
                        else if(poljeZ[vrhz] > poljeX[vrhx] and poljeX[vrhx] != 0){
                            poljeZ[vrhz+1] = poljeX[vrhx];
                            poljeX[vrhx]=0;
                            vrhz++;
                            vrhx--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    default:
                        cout << "Napacna izbira! \n";
                        break;
                }
                break;
                
            case '2':
                izbirab = menu2();
                switch(izbirab){
                    case '1':
                        if(vrhx == -1){
                            poljeX[0] = poljeY[vrhy];
                            poljeY[vrhy] = 0;
                            vrhx = 0;
                            vrhy = vrhy-1;
                        }
                        else if(poljeX[vrhx] > poljeY[vrhy] and poljeY[vrhy] != 0){
                            poljeX[vrhx+1] = poljeY[vrhy];
                            poljeY[vrhy]=0;
                            vrhx++;
                            vrhy--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    case '2':
                        cout << "Napacna izbira \n";
                        break;
                        
                    case '3':
                        if(vrhz == -1){
                            poljeZ[0] = poljeY[vrhy];
                            poljeY[vrhy] = 0;
                            vrhz = 0;
                            vrhy = vrhy-1;
                        }
                        else if(poljeZ[vrhz] > poljeY[vrhy] and poljeY[vrhy] != 0){
                            poljeZ[vrhz+1] = poljeY[vrhy];
                            poljeY[vrhy]=0;
                            vrhz++;
                            vrhy--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    default:
                        cout << "Napacna izbira! \n";
                        break;
                }
                break;
                
            case '3':
                izbirab = menu2();
                switch(izbirab){
                    case '1':
                        if(vrhx == -1){
                            poljeX[0] = poljeZ[vrhz];
                            poljeZ[vrhz] = 0;
                            vrhx = 0;
                            vrhz = vrhz-1;
                        }
                        else if(poljeX[vrhx] > poljeZ[vrhz] and poljeZ[vrhz] != 0){
                            poljeX[vrhx+1] = poljeZ[vrhz];
                            poljeZ[vrhz]=0;
                            vrhx++;
                            vrhz--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    case '2':
                        if(vrhy == -1){
                            poljeY[0] = poljeZ[vrhz];
                            poljeZ[vrhz] = 0;
                            vrhy = 0;
                            vrhz = vrhx-1;
                        }
                        else if(poljeY[vrhy] > poljeZ[vrhz] and poljeZ[vrhz] != 0){
                            poljeY[vrhy+1] = poljeZ[vrhz];
                            poljeZ[vrhz]=0;
                            vrhy++;
                            vrhz--;
                        }
                        else{
                            cout << "Napacna izbira \n";
                        }
                        
                        break;
                        
                    case '3':
                        cout << "Napacna izbira \n";
                        break;
                        
                    default:
                        cout << "Napacna izbira! \n";
                        break;
                }
                break;
                
            default:
                cout << "Napacna izbira! \n";
                break;
        }
        poteze++;
        
    }
    
    
    cout << "Konec. Zmagali ste v: " << poteze << " potezah!" <<endl;
    return 0;
}
