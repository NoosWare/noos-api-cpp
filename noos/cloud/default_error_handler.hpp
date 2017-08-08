#ifndef NOOS_CLOUD_DEFAULT_ERROR_HANDLER
#define NOOS_CLOUD_DEFAULT_ERROR_HANDLER
namespace noos {
namespace cloud {
/**
 * @brief default error handler will output on stderr only if NDEBUG macro is used
 * @struct default_error_handler
 * @version 0.7.3
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @date 7 June 2017
 *
 * common errors are:
 *  - boost::system::errc::bad_message if the header is not followed by a double return carriage
 *  - boost::system::errc::no_message if the platform does not respond with any data
 *  - boost::system::errc::protocol_not_supported if the reply does not conform to HTTP 1.1
 *  - boost::system::errc::protocol_error if HTTP header does not respond with 200 status code
 */
struct default_error_handler
{
    void operator()(boost::system::error_code & error) const
    {
        #if (!NDEBUG)
        switch(error.value()) { 
            case 103:
                std::cerr << "[error-message]: Connection aborted. Socket shutdown. Create a different connection." << std::endl;
                break;
            default:
                std::cerr << "[error-message]: " << error.message() 
                          << " [error-value]: " << error.value() << std::endl;
                break;
        }
        #endif
    }
};

}
}
#endif
