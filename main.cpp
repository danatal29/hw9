#include <iostream>
#include <stdlib.h>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"




int main(int argc, char **argv) {

    if((check_args(argc,argv)) != 0){
        exit (1);
    }
    
    const char *delim="=";
    String *tmp_ptr;
    String **fields = &tmp_ptr;
    size_t field_count;
    String rule(argv[1]);
    rule=rule.trim();
    rule.split(delim,fields,&field_count);
    String pattern=((*fields)[0]);
    String val=((*fields)[1]);
    pattern=pattern.trim();
    val=val.trim();
    if((pattern.equals("src-ip"))||(pattern.equals("dst-ip"))){
        Ip ip_rule(pattern);
        ip_rule.set_value(val);
        parse_input(ip_rule);
        //delete ip_rule;

    }
    else if((pattern.equals("src-port"))||(pattern.equals("dst-port"))){
        Port port_rule(pattern);
        port_rule.set_value(val);
        parse_input(port_rule);
        //delete port_rule;
    }
    //delete [] fields;
    //for (size_t i=0; i<field_count ; i++){
       // std::cout<< "relese fields "<<i<<std::endl;

        //delete &((*fields)[i]);
    //}
    //std::cout<< "delete array fields"<<std::endl;
    delete[] *fields;
    //std::cout<< "delete array succeed"<<std::endl;
    //std::cout<< "end of main"<<std::endl;
    return 0;
}

/*
for (size_t i=0; i<field_count ; i++){
    delete ((*fields)[i]);
}
*/






