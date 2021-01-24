//
// Created by user on 1/19/2021.
//

#include <stddef.h>
#include <iostream>
#include "string.h"
#include <string.h>

/*
class String {
    char *data;
    size_t length;

public:
*/

/**
    * @brief Initiates an empty string
    */
String::String(): length(0){
    data= new char [1];
    strcpy(data,"\0");
}


/**
 * @brief Initiates string from other string
 */
String::String(const String &str) {
    if(str.data==NULL){
        exit (1);
    }
    data= new char [str.length+1];
    strcpy(data,str.data);
    length=str.length;
}


/**
 * @brief Initiates a string from char array
 */
String::String(const char *str)  {
    if (str == NULL) {
        exit(1);
    }
    data = new char[strlen(str) + 1];
    strcpy(data, str);
    length = strlen(str);
}

String::~String() {
    delete[] data;

}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {
    /*if(rhs.data==NULL){
        return NULL;
    }*/
    if(this != &rhs) {
        delete[] data; /// maybe without []
        if (rhs.data==NULL) {
            data=NULL;
        }
        data = new char[rhs.length+1];
        strcpy(data, rhs.data);
        length=rhs.length;
    }
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str) {
    delete[] data; /// maybe without []
    if (str==NULL) { /// if str is NULL should we delete data?
        data=NULL;
    }
    data = new char[strlen(str)+1];
    strcpy(data, str);
    length = strlen(str);
    return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
    if(rhs.data==NULL){
        if(data==NULL) {
            return true;
        }
        return false;
    }
    return (!strcmp(data, rhs.data));
}


/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
    if(rhs==NULL){
        if(data==NULL) {
            return true;
        }
        return false;
    }
    return (!strcmp(data, rhs));
}



/**
     * @brief count the fields in a string according to a delimiter
     * Does not change this.
     */
size_t count_fields (const char *delimiters, const char* data)  {
    if (delimiters == NULL) {
        exit(1);
    }
    std::cout << "delimiter: " << delimiters[0];
    std::cout << "delimiters: " << delimiters;
    std::string data_clone ;
    data_clone.assign(data);
    std::string delim ;
    delim.assign(delimiters);

    int counter =0;
    auto start = 0U;
    auto end = data_clone.find(delim);
    while (end != std::string::npos) {
        start = end + delim.length();
        end = data_clone.find(delim, start);
        if(start != end ){
            counter++;
        }
    }
    /* string stars with delimiters */
    if(! delim.compare( data_clone.substr(0, delim.length())) ){
        counter --;
    }
    /* string end with delimiter */
    if(! delim.compare(data_clone.substr(data_clone.length()-delim.length(),
                                         delim.length())) ){
        counter --;
    }
    return counter+1;
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
bool fill_array(const char *delimiters, String *fields,const char *data, size_t length)  {
    std::cout <<"inside fill array" << std::endl;

    if ((delimiters == NULL) || (fields == NULL)) {
        std::cout << "problem with pointers" << std::endl;
        return false;
    }

    char buf1[length+1] ;
    strcpy(buf1,data);
    //std::cout << "strcpy succeed" << std::endl;

    int i = 0;
    char *p1 = strtok(buf1, delimiters);
    //std::cout << "strtok succeed" << std::endl;
    while (p1 != NULL) {
        //std::cout << "inside while" << std::endl;

        size_t temp_size = strlen(p1);
        char temp_token[temp_size+1];
        strcpy(temp_token,p1);
       // std::cout << "strcpy succeed allocating new string" << std::endl;
        String *field=new String(temp_token);
        //std::cout << "assigning value to field:" << i <<std::endl;
        fields[i] = *field;
        //std::cout << "assign succeed" << std::endl;
        p1 = strtok(NULL, delimiters);
        //std::cout << "strtok succeed" << std::endl;
        i++;
    }
    std::cout << "outside while returning from fill_array()" << std::endl;
    return true;
}




/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const{
    *size= count_fields (delimiters, data);
    if(output==NULL) { /*compute size*/
        return;
    }
    String *fields= new String [*size];
    std::cout <<"allocated fields[] of size:"<< *size << std::endl;


    std::cout << "delete array fields!!!!!!!!!!!!!!!!!!!!!! split func" << std::endl;
    if(fill_array(delimiters,fields, data, length)) {
        std::cout << "returned from fill array" << std::endl;
        *output = fields;
        return;
    }

    exit(1);
}




/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
    return atoi(data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
    std::cout << "inside trim       " << std::endl;
    char *start=data;
    char *end=start+length-1;
    const char white_space=' ';
    size_t counter=length;
    while (*start == white_space){
        start++;
        counter--;
    }
    //std::cout << " trim start:_" <<start<< std::endl;
    while(*end==white_space){
        end--;
        counter--;
    }
    //std::cout << " trim counter:_" <<counter<< std::endl;
    char temp_str[counter+1];
    strncpy(temp_str,start,counter);
    //std::cout << " after strncpy:_" << std::endl;
    temp_str[counter] = '\0';

    //std::cout << " trim   ######test trim:" << temp_str<<"::"<< std::endl;
    String *trim_str= new String(temp_str);
    std::cout <<"returning from trim()"<< std::endl;
    return *trim_str;
}



/* getters*/
/*
const char* get_data()const {
    std::cout << "inside get data" << std::endl;
    return data;
}
*/


void  String:: print(){
    std::cout <<"data:  "<< data << std::endl;
    std::cout <<"length:  "<< length << std::endl;

    return;
}

//};



