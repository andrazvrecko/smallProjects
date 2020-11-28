//
//  binreader.h
//  lzw
//
//  Created by Andraz Vrecko on 09/06/2018.
//  Copyright © 2018 Andraz Vrecko. All rights reserved.
//

#ifndef binreader_h
#define binreader_h
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

    BinReader(string pot){
        input.open(pot, ios::binary);
    };
    ~BinReader() {
        input.close();
    }
    
    
    bool readBit(){
        return true;
    }
    
    char readByte(){
        char a;
        input.read(&a, 1);
        return a;
    }
    
    int readInt(int a){
        int i;
        input.read((char*)&i, a);
        return i;
    }
    
    float readFloat(){
        float f;
        input.read((char*)&f, sizeof(float));
        return f;
    }
};

#endif /* binReader_hpp */


#endif /* binreader_h */
