#include <string>
#include <iostream>
#include "http_protocol.h"
#include "parser.h"
#include "logic.h"

using std::string;
class DatanoesisHandler {
    public:
        int RunHandler(request_rec *req) {
            if (!req->handler || path != req->handler) return DECLINED;
            //ap_rputs(message.c_str(), req);
            parser = new Parser();
            logic = new Logic();
            parser->parse(req);
            logic->setParams(parser->getArgs(), parser->getMethod(),parser->getParams());
            //std::cout << "Here some log" << std::endl;
            int _return_code;
            string _return_string;
            std::tie(_return_code,_return_string) = logic->getResponse();
            ap_rputs(_return_string.c_str(),req);
            //ap_rprintf(req,message.c_str());
            return _return_code;
        }


    private:
        string path = "datanoesis";
        Parser *parser;
        Logic *logic;
};
