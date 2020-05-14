#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <memory>
#include <tuple>
#include <cstdlib>
#include <fstream>
#include "json/include/json.hpp"
#include "soci/include/soci/soci.h"
#include "soci/include/soci/oracle/soci-oracle.h"
#include "soci/include/soci/mysql/soci-mysql.h"
#include "http_protocol.h"
#include "logger.h"

using namespace soci;
using json = nlohmann::json;
using namespace std;

class Logic{
    public:
        void setParams(string _args,string _method, std::map<string,string> _params, string _handler)
        {
            args = _args;
            method = _method;
            params = _params;
            handler = _handler;
            logger = CLogger::GetLogger();
            readDatabaseInfo();
            if(!db_config_ready){
                //response = "Database information not set\n";
                return;
            }
            if(database_type == "mysql"){
                string connection_str = "db="+dbname+" host='"+hostname+"' user="+username+" password='"+password+"'";
                response = "MySQL is set as default database\n";
                try{
                    session sql(mysql, connection_str);
                }
                catch(exception const &e){
                    response = e.what();
                }
                //response = connection_str;
                //string response_db;
                //sql << "select * from table", into(response_db);
                //response = response_db;
            }
            else if(database_type == "oracle"){
                response = "Oracle set as database\n";
                string connection_str = "service="+hostname+" user="+username+" password="+password;
                try{
                    session sql(oracle, connection_str); //using factory
                }
                catch(exception const &e){
                    response = e.what();
                }
                response = handler+"\n"+args+"\n"+response;

            }
            else{
                response = "No database defined\n";
            }
        }
        void connect(){
            logger->Log("Try to connect");
        }
        void readDatabaseInfo(){
            string config_file_content;
            try{
                ifstream inFile;
                inFile.open("/Project/apache/config.json");
                stringstream strStream;
                strStream << inFile.rdbuf();
                config_file_content = strStream.str();
                response = config_file_content+"\n";
            }
            catch (exception const &e){
                response = "could not read json file\n";
                logger->Log("Coud not read json file");
                return;
            }
            if(config_file_content == ""){
                response = "content file empty\n";
                logger->Log("Config file is empty");
                return;
            }
            try{
                json config = json::parse(config_file_content);
                if (config.is_object())
                {
                    database_type = config["db_type"].get<string>();
                    hostname = config["host"].get<string>();
                    port = config["port"].get<int>();
                    username = config["user"].get<string>();
                    password = config["password"].get<string>();
                    dbname = config["dbname"].get<string>(); 
                    db_config_ready = true;
                }
                else{
                    response = "Error content config file\n";
                } 
            }
            catch(json::parse_error &e){
                response = e.what();
                return;
            }
        }
        std::tuple<int,string> getResponse(){
            return std::make_tuple(OK, response);
        }
        std::tuple<int,string> insert(){

        }
        std::tuple<int,string> get(){

        }
        std::tuple<int,string> update(){

        }
        std::tuple<int,string> remove(){

        }

    private:
        string args;
        string method;
        std::map<string,string> params;
        CLogger *logger;
        string database_type;
        string dbname;
        string hostname;
        string username;
        string password;
        string response;
        string handler;
        int port;
        bool db_config_ready;

};
