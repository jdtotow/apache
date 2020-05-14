#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "http_protocol.h"

using std::string;

class Parser{
    public:
        void parse(request_rec *req){
            this->method = string(req->method);
            if(this->method == "GET"){
                if(req->args){
                    this->args = string(req->args);
                    std::istringstream stream_args(string(this->args));
                    string keyval, key, val;
                    while(std::getline(stream_args, keyval, '&')) // split each term
                    {
                        std::istringstream iss(keyval);
                        // split key/value pairs
                        if(std::getline(std::getline(iss, key, '='), val))
                            this->params[key] = val;
                    }
                }
            }
            else if(this->method == "POST"){
                this->args = getData(req);
            }
            else if(this->method == "PUT"){
                this->args = getData(req);
            }
            else if(this->method == "DELETE"){

            }
            else{
                //
            }
            
        }
        string getData(request_rec *req){
            const size_t _length = 4048;
            char* buf[_length];
            util_read(req,buf);
            return string((char*)*buf);
        }
        int util_read(request_rec *r, char **rbuf){
            int rc;
            int length = 0;
            if((rc = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)) != OK){
                return rc;
            }
            if(ap_should_client_block(r)){
                char argsbuffer[HUGE_STRING_LEN];
                int rsize, len_read, rpos=0;
                length = r->remaining;
                *rbuf = (char*)apr_pcalloc(r->pool, length + 1);
                while((len_read = ap_get_client_block(r, argsbuffer, sizeof(argsbuffer))) > 0){
                    if((rpos + len_read) > length){
                        rsize = length - rpos;
                    } else {
                        rsize = len_read;
                    }
                    memcpy((char*)*rbuf + rpos, argsbuffer, rsize);
                    rpos += rsize;
                }

            }
            return rc;
        }
        string getResponse(){
            return "Default response from module parser\nMethod: "+ method+"\nArgs: "+ args+"\n";
        }
        string getArgs(){
            return args;
        }
        string getMethod(){
            return method;
        }
        std::map<string,string> getParams(){
            return params;
        }
    private:
        string args;
        string method;
        std::map<std::string, std::string> params;
};