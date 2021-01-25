//
// Created by user on 1/22/2021.
//

#include <stddef.h>
#include <iostream>
#include <string.h>
#include "field.h"
#include "ip.h"
#include "port.h"

/*DEFINES*/
#define MASK_SEGMENT 2
#define SUB_FIELDS 2
#define SEGMENTS 4
#define BYTE 8


/**
class Field {
private:
    String pattern;
    field_type type;
**/

Field::Field(String pattern, field_type type):type(type){
    this->pattern=pattern;
}


Field::Field(String pattern) :type(GENERIC) {
    //String *temp = new String(pattern);
    this->pattern=pattern;
    //type=get_type();
}


Field::~Field(){

}

bool Field::set_value(String val){
    //std::cout << " inside field's set_value()  " << std::endl;
    if(type==IP){
    //    std::cout << "  calling ip's set_value()    " << std::endl;
        return (Ip*)this->set_value(val);
    }
    if(type==PORT){
        return (Port*)this->set_value(val);
    }
    return false;
}


bool Field::match_value(String val)const{
    //std::cout << "inside FIeld::match_value()" << std::endl;
    if(type==IP){

        return ((Ip*)this)->match_value(val);
    }
    if(type==PORT){
        return ((Port*)this)->match_value(val);
    }
    return false;
}

bool Field::match(String packet){
    //std::cout << "indisde Field::match()" << std::endl;
    String *fields;
    String *sub_fields;
    size_t field_count;
    size_t sub_field_count;

    const char *delim=",";
    const char *sub_delim="=";
    /*splitting to packet fields*/
    //std::cout << "spliting packet t fields" << std::endl;

    packet.split(delim,&fields,&field_count);
    if (field_count!=SEGMENTS){
        //std::cout << "error in split" << std::endl;

        delete [] fields;
        delete [] sub_fields;
        return false;
    }

    //std::cout << "split succeddeddededd" << std::endl;

    /*split each field to pattern and val*/
    //std::cout << "for loop - split each field to val and pattern" << std::endl;

    for (size_t i=0; i<field_count; i++){
        //std::cout << "indisde for" << std::endl;
        fields[i]=fields[i].trim();
        //std::cout << "trimmed String' now splitiing " << std::endl;
        (fields[i]).split(sub_delim,&sub_fields,&sub_field_count);
        if(sub_field_count!=SUB_FIELDS){
            //std::cout << "error in split, continue" << std::endl;
            continue;//if one field is illegal should we keep checking?
        }
        /*temp_type is pattern of field*/
        //std::cout << "trriming pattern" << std::endl;

        String temp_type= sub_fields[0].trim();
        /*if (true), no need to check other fields*/
        if (temp_type.equals(pattern)){
            //std::cout << "indisde if- pattern matched this->pattern, trimming val" << std::endl;
            String temp_val = sub_fields[1].trim();
            //std::cout << "field in question is : " << std::endl;
           // temp_val.print();
            //std::cout << "deleting allocations" << std::endl;

            delete [] fields;
            delete [] sub_fields;
            //std::cout << "allocations delete,  returning" << std::endl;

            /*check if val is in legal interval*/
            //std::cout << "CALLING MATCH_VALUE() befor returning from MATCH() " << std::endl;
            return match_value(temp_val);
        }
    }
    //std::cout << "out of for loop, no field matched this_>pattern, deleting and returning" << std::endl;
    delete [] fields;
    delete [] sub_fields;
    return false;
}

/*
void Field::print() {
 //   pattern.print();
    //std::cout << "type: " << type << std::endl;

    return;
}
*/

/** getters **/

field_type Field::get_type() const{
    return type;
}

/*
String get_pattern(){
    return this->pattern;
}
*/



