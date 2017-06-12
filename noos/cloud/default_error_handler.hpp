#ifndef CLOUD_DEFAULT_ERROR_HANDLER
#define CLOUD_DEFAULT_ERROR_HANDLER

namespace rapp {
namespace cloud {
/**
 * @brief default error handler will output on stderr only if NDEBUG macro is used
 * @struct default_error_handler
 * @version 0.7.3
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @date 7 June 2017
 */
struct default_error_handler
{
    void operator()(boost::system::error_code & error) const
    {
        #if (!NDEBUG)
        std::cerr << "[error-message]: " << error.message() 
                  << " [error-value]: " << error.value() << std::endl;
        #endif
    }
};

}
}
#endif
