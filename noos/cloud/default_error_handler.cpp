#include "default_error_handler.hpp"

namespace noos {
namespace cloud {

const std::string default_error_handler::error_message =  "\e[31m[error-message]\e[0m :";

void default_error_handler::operator()(boost::system::error_code & error) const
{
    switch(error.value()) { 
        case 2:
            //End of file
            std::cerr << error_message 
                      << " The platform has closed the connection." << std::endl;
            break;
        case 31:
            //Protocol error
            std::cerr << error_message 
                      << " Protocol error has been received (timeout, uri not found, bad request, etc)." << std::endl;
            break;
        case 32:
            //Broken pipe
            std::cerr << error_message 
                      << " The platform has closed the connection without closing API connection." << std::endl;
            break;
        case 71:
            //Protocol error
            std::cerr << error_message
                      << " HTTP error receive from the platform. " << std::endl;
            break;
        case 75:
            //HTTP Bad request 
            std::cerr << error_message
                      << " HTTP Bad Request. One or more parameters in the header are missing." << std::endl;
            break;
        case 99:
            //HTTP URL not found
            std::cerr << error_message
                      << " HTTP URI not found. The service you are calling is not available in the platform." << std::endl;
            break;

        case 110:
            //Timeout
            std::cerr << error_message 
                      << " Connection time out." << std::endl;
            break;
        case 111:
            std::cerr << error_message 
                      << " Impossible connect with the platform." <<
                         " Check the IP and try again. " << std::endl;
            break;
        case 103:
            std::cout << error_message << " Connection aborted. Socket shutdown." 
                      << "Create a different connection." << std::endl;
            break;
        case 125:
            std::cout << error_message << " Operation canceled." << std::endl;
            break;
        default:
            std::cout << error_message << error.message() 
                      << " [Error-value]: " << error.value() << std::endl;
            break;
    }
}
}
}
