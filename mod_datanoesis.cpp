#include <memory>
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "DatanoesisHandler.h"

auto handler = std::make_unique<DatanoesisHandler>();
extern "C"{
    static void mod_datanoesis_register_hooks(apr_pool_t *p)
    {
        ap_hook_handler([](request_rec *req) {
                    return handler->RunHandler(req);
                },
                NULL, 
                NULL, 
                APR_HOOK_MIDDLE
        );
    }

/* Dispatch list for API hooks */
    module AP_MODULE_DECLARE_DATA datanoesis_module = {
        STANDARD20_MODULE_STUFF, 
        NULL,                  /* create per-dir    config structures */
        NULL,                  /* merge  per-dir    config structures */
        NULL,                  /* create per-server config structures */
        NULL,                  /* merge  per-server config structures */
        NULL,                  /* table of config file commands       */
        mod_datanoesis_register_hooks  /* register hooks                      */
    };
};

