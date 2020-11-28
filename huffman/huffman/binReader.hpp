//
//  binReader.hpp
//  huffman
//
//  Created by Andraz Vrecko on 10/05/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#ifndef binReader_hpp
#define binReader_hpp

#include <iostream>
#include <fstream>

using namespace std;

class BinReader{
public:
    ifstream input;
    char spr=0;
    int count=-1;
    bool eof_int = false;
    bool EOF_ext = false;
    size_t length = 0;
    BinReader(string pot){
        input.open(pot, ios::binary);
        input.seekg (0, input.end);
        length = input.tellg();
        input.seekg (0, input.beg);
    };
    ~BinReader() {
        input.close();
    }
   
    
    bool readBit(){
        if(EOF_ext == true){
            exit;
        }
        bool b;
        if(count < 0){
            spr = 0;
            count = 7;
            input.read(&spr, 1);
            length--;
            //cout << "{" << spr << "}";
            if(length == 0)
                eof_int = true;
        }
        b = spr&(1<<count);// == (1 << count);
        //cout << b << "[" << count << "]";
        count--;
        if(eof_int && (count == 0)){
            EOF_ext = true;
        }
        return b;
    }

    char readByte(){
        char a;
        input.read(&a, 1);
        return a;
    }

    int readInt(){
        int i;
        input.read((char*)&i, sizeof(int));
        return i;
    }

    float readFloat(){
        float f;
        input.read((char*)&f, sizeof(float));
        return f;
    }
};

#endif /* binReader_hpp */
