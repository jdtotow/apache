#include <string>
#include "http_protocol.h"

using std::string;

class ModuleHelper {
    public:
        void parse(request_rec *req){
            path = string(req->handler);
            method = string(req->method);
            parameters = string(req->args);
        }
        string getPath(){
            return path;
        }
        string getMethod(){
            return method;
        }
        string getParameters(){
            return parameters;
        }
        int getResponse(){
            return HTTP_OK;
        }
        string getOutput(){
            return default_response;
        }
    private:
        string default_response = "Response from the default Datanoesis handler";
        string path;
        string method;
        string parameters;
};