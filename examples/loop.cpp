#include <noos/noos>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
/*
 * \brief Example of a loop using asio timer
 */
int main() 
{
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(1));

    using namespace noos::cloud;

    auto pic = noos::object::picture("data/object_classes_picture_1.png");
    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::qr_code and
     * we show the size of the vector to know how many qr_codes have 
     * been found.
     */
    auto callback = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };
    /*
     * The face_detection object is created
     */
    auto face_request = face_detection(pic);
    /*
     * The callable object is created
     */
    callable<face_detection,true> cb(face_request, callback);
    /*
     * Construct a std::function which is going to be in charge of make the call
	 * reinitialize the timer and call the own function a second later to make an
	 * infinite loop.
     */
	std::function<void(const boost::system::error_code&)> func = [&](const auto & err) {
        /*
         * The information of the face_detection object is sent
         */
        cb.send(2);
        /*
         * If the image needs to be changed, just a new face_detection object
         * with the new image can be created
         */
        pic = noos::object::picture("data/object_classes_picture_1.png");
        cb.object = face_detection(pic);

		timer.expires_at(timer.expires_at() + boost::posix_time::milliseconds(50));
		timer.async_wait(func);
	};

	/* 
 	 * Asynchronously wait
	 */
	timer.async_wait(func);

    /* 
	 * The timer will fire for the first time 1 second from now
	 */
    io_service.run();
    return 0;
}
