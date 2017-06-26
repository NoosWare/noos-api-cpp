#ifndef NOOS_ASIO_TIMER
#define NOOS_ASIO_TIMER
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
namespace noos {
namespace cloud {
/**
 * @class asio_timer
 * @version 0.7.0
 * @date 12 August 2016 
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 * @brief used by asio_handler to detect connection time-outs 
 */
class asio_timer
{
public:
	/// @brief construct
    asio_timer(boost::asio::io_service &);

    /// @brief set the timer with \param seconds
    void set_timeout(unsigned int arg);

	/// @brief reset the timer
    void reset();

private:
    void check_timeout();
    boost::asio::deadline_timer timer_;
};
}
}
#endif
