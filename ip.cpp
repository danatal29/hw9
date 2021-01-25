//
// Created by user on 1/23/2021.
//

#include <iostream>
#include <stddef.h>
#include "ip.h"
#include <cmath>

#define MASK_SEGMENT 2
#define SEGMENTS 4
#define BYTE 8



Ip::Ip(String pattern):Field(pattern,IP),low(0),high(0){

}


/*calculate address's value, caller to calc value need to delete subfields*/
unsigned int calc_value(String val,const char *delim,String **fields,
                                                          bool *succ){
    size_t counter_fields=0;
    //std::cout << " inside calc_value()   " << std::endl;
    /*split address 127.0.0.1 to 127,0,0,1*/
   // std::cout << "  spliting address to sub addresses 127 0 0 1    " << std::endl;
    val.split(delim,fields,&counter_fields);
    if(counter_fields!=SEGMENTS){
        //std::cout << "  split didnt give back enough fields   " << std::endl;
        *succ= false;
        return 1;
    }
    //std::cout << "  successfull split    " << std::endl;
    /*assist array, holds sub address int value*/

    int ip_val[SEGMENTS];
    //std::cout << "  for loop calc address integral value   " << std::endl;
    for (int i=0; i<SEGMENTS ; i++){
        ((*fields)[i])=((*fields)[i]).trim();
        //std::cout << "  calling to_integer()   " << std::endl;
        ip_val[i]=((*fields)[i]).to_integer();
        //std::cout << ip_val[i] << std::endl;
    }
    //std::cout << "  done with loop    " << std::endl;
    /*bitwise calculation of address*/
    //std::cout << "  final bitwise calc   " << std::endl;
    unsigned int ip= ((ip_val[0])<<BYTE*3) | ((ip_val[1])<<BYTE*2) |
                     ((ip_val[2])<<BYTE) | ((ip_val[3]));
    //std::cout << ip << std::endl;
    *succ= true;
    return ip;
}



bool Ip::set_value(String val){
    //std::cout << "  inside ip's set_value()    " << std::endl;
    String *fields;
    String *sub_fields;
    size_t counter_fields;
    const char *delim= "/";
    const char *sub_delim= ".";
    bool succ= false;

    /*splitting rule to address and mask*/
    /*field[0] is address and field[1]*/
    //std::cout << "  spliting to address and mask    " << std::endl;
    val.split(delim,&fields,&counter_fields);
    if(counter_fields!=MASK_SEGMENT){
        //std::cout << " split failed   " << std::endl;
        delete [] fields;
        return false;
    }
    for (int i=0; i<MASK_SEGMENT ;i++){
        fields[i]=fields[i].trim();
    }
    //std::cout << "  calc mask   " << std::endl;
    int mask=(fields[1]).to_integer();
    /*calculate address's value*/
    //std::cout << "  calling calc_value()    " << std::endl;
    unsigned int ip= calc_value(fields[0],sub_delim,&sub_fields,&succ);
    //std::cout << "returned from calc_value()" << std::endl;
    if(succ==false){
        std::cout << "  calc_value() failed    " << std::endl;
        delete [] fields;
        delete [] sub_fields;
        return false;
    }
    //std::cout << "calc low, high"<< std::endl;
    /*bitewise calc low and high*/
    int dont_care_bits= SEGMENTS*BYTE-mask;
    /* shifting back and forth replaces with zeros*/
    low= (ip>>dont_care_bits)<<dont_care_bits;
    high= low + pow(2,dont_care_bits) -1;
    //std::cout <<"delet memory" << std::endl;
    delete [] fields;
    delete [] sub_fields;
    //std::cout <<" returning from ip.set_value() "<< std::endl;
    return true;
}
/* calc_value(String val,const char *sub_delim,String *sub_fields,
                        size_t counter_sub_fields,bool *succ){ */



bool Ip::match_value(String val) const{
    //std::cout <<" inside ip.match_value() "<< std::endl;
    const char *delim=".";
    String *fields;
    bool succ=false;
    //std::cout <<" calling to calc_value() "<< std::endl;
    unsigned int ip_val = calc_value(val,delim,&fields,&succ);
    if (succ==false){
        //std::cout <<" calc_value() didnt succeed"<< std::endl;
        delete [] fields;
        //std::cout <<" deleted returning"<< std::endl;
        return false;
    }
    if((ip_val>=low)&&(ip_val<=high)){
        //std::cout <<" val is in range"<< std::endl;
        delete [] fields;
        //std::cout <<" deleted returning"<< std::endl;
        return true;
    }
    delete [] fields;
    //std::cout <<" deleted returning"<< std::endl;
    return false;
}

/*
void Ip::print_ip() {
    print();
    std::cout << "low: " << low << std::endl;
    std::cout << "high: " << high << std::endl;

    return;
}
*/