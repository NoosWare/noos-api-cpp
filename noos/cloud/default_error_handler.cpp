#include "default_error_handler.hpp"

namespace noos {
namespace cloud {

void default_error_handler::operator()(boost::system::error_code & error) const
{
    switch(error.value()) { 
        case 11:
            std::cerr << "[Error-message]: Impossible connect with the platform." <<
                         " Check the IP and try again. " << std::endl;
            break;
        case 103:
            std::cout << "[Error-message]: Connection aborted. Socket shutdown. Create a different connection." << std::endl;
            break;
        default:
            std::cout << "[Error-message]: " << error.message() 
                      << " [Error-value]: " << error.value() << std::endl;
            break;
    }
}
}
}
