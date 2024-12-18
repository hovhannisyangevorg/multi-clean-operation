#include "../../sources/server/server_core/server.h"
#include "../../sources/calculator/calculator_executor/calculator_executor_test.h"

 int main () {
     t_error*    Error = NULL;
     t_server*   Server = NULL;
     t_config*   ConfigServer = NULL;

     Error = init_error();
     if (!Error) {
         return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
     }

     if (init_server(Error)->message) {
         Set(Error, format(__func__, ""));
         logger(ERROR, Error->message);
         clean_up_error(&Error);
         return EXIT_FAILURE;
     }
     Server = Error->value;

     if (init_config(Error)->message) {
         Set(Error, format(__func__, ""));
         logger(ERROR, Error->message);
         clean_up_error(&Error);
         clean_up_server(&Server);
         return EXIT_FAILURE;
     }
     ConfigServer = Error->value;

     if (server(ConfigServer, Server, Error)->message) {
         Set(Error, format(__func__, ""));
         logger(ERROR, Error->message);
         clean_up_error(&Error);
         clean_up_server(&Server);
         clean_up_config(&ConfigServer);
         return EXIT_FAILURE;
     }
     clean_up_error(&Error);
     clean_up_server(&Server);
     clean_up_config(&ConfigServer);
     return (EXIT_SUCCESS);
 }

#include "../../sources/calculator/calculator_executor/calculator_executor_test.h"
//int main()
//{
//    t_error *Error = NULL;
//
//    Error = init_error();
//    if (!Error) {
//        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
//    }
//
//    if (calculator_executor_test(Error)->message) {
//        return logger(ERROR, Error->message), EXIT_FAILURE;
//    }
//    t_vector* Vector = init_vector();
//    if (!Vector)
//        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;

//    for (size_t i = 0; i < 1; ++i) {
//        char* expression = strdup(expressions[i]);
//        size_t size = strlen(expression);
//
//        if (tokenizer_code(expression, size, Error)->message) {
//            return logger(ERROR, Error->message), EXIT_FAILURE;
//        }
//        Vector = Error->value;
//
//        if (parse(Error->value, Error)->message) {
//            return logger(ERROR, Error->message), EXIT_FAILURE;
//        }
//
//        if (validator(Vector, Error)->message) {
//            return logger(ERROR, Error->message), EXIT_FAILURE;
//        }
//
//        if (calculator_core(Error->value, Error)->message) {
//            return logger(ERROR, Error->message), EXIT_FAILURE;
//        }
//        printf("%s = (%s)\n", expressions[i], (char*)Error->value);
//    }
//    clean_up_error(&Error);
//}
