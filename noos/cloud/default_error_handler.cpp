#include "default_error_handler.hpp"

namespace noos {
namespace cloud {

const std::string default_error_handler::error_message =  "\e[31m[error-message]\e[0m :";

void default_error_handler::operator()(boost::system::error_code & error) const
{
    switch(error.value()) { 
        case 2:
            //End of file
            throw std::runtime_error(error_message + " The platform has closed the connection.");
            break;
        case 13:
            //Permission denied
            throw std::runtime_error(error_message + " Permission denied. Check user and password.");
            break;
        case 31:
            //Protocol error
            throw std::runtime_error(error_message + " Protocol error has been received (timeout, uri not found, bad request, etc).");
            break;
        case 32:
            //Broken pipe
            throw std::runtime_error(error_message + " The platform has closed the connection without closing API connection.");
            break;
        case 71:
            //Protocol error
            throw std::runtime_error(error_message + " HTTP error receive from the platform. ");
            break;
        case 75:
            //HTTP Bad request 
            throw std::runtime_error(error_message + " HTTP Bad Request. One or more parameters in the header are missing.");
            break;
        case 99:
            //HTTP URL not found
            throw std::runtime_error(error_message + " HTTP URI not found. The service you are calling is not available in the platform.");
            break;

        case 110:
            //Timeout
            throw std::runtime_error(error_message + " Connection time out.");
            break;
        case 111:
            throw std::runtime_error(error_message + " Impossible to connect with the platform." +
                                     " Check the IP and try again. ");
            break;
        case 103:
            throw std::runtime_error(error_message + " Connection aborted. Socket shutdown." +
                                     "Create a different connection.");
            break;
        case 125:
            throw std::runtime_error(error_message + " Operation canceled.");
            break;
        default:
            throw std::runtime_error(error_message +  error.message());
            break;
    }
}
}
}
