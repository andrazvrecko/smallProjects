//
//  binWriter.hpp
//  huffman
//
//  Created by Andraz Vrecko on 10/05/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#ifndef binWriter_hpp
#define binWriter_hpp

#include <iostream>
#include <fstream>
using namespace std;
class BinWriter{
public:
    ofstream output;
    char spr=0;
    int count=7;
    BinWriter(std::string pot){
        output.open(pot, ios::binary);
    };
    
    ~BinWriter() {
        if(count<7){
            output.write(&spr, 1);
            //cout << spr;
        }
        output.close();
    }

    void writeBit(bool b) {
        
        spr ^= (-b ^ spr) & (1 << count); // nastavimo x-ti bit na b (0 ali 1)
        count--;
        //cout << b;
        if(count<0) {
            output.write(&spr, 1);
            //cout << "{" << spr << "}";
            count=7;
            spr=0;
            
        }
    }
    
    void writeByte(char b){
        output.write(&b,1);
    }

    
    void writeInt(int i){
        output.write((char*)&i, sizeof(int));
    }
    
    void writeFloat(float f){
        output.write((char*)&f,sizeof(float));
    }

    

    };

#endif /* binWriter_hpp */
