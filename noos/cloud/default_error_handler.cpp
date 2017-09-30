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
                      << "The platform has closed the connection." << std::endl;
            break;
        case 31:
            //Protocol error
            std::cerr << error_message 
                      << "The service called is not available in the platform." << std::endl;
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
        default:
            std::cout << error_message << error.message() 
                      << " [Error-value]: " << error.value() << std::endl;
            break;
    }
}
}
}
