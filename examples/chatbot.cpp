#include <noos/noos>
#include <iostream>
// 
// Example of the simplest chatbot
// 
int main()
{
    using namespace noos::cloud;
    // 
    // This lambda will receive the reply from the cloud.
    // 
    auto callback = [](std::string reply) {
         std::cout << "Reply: " << reply << std::endl;
     };
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    // 
    // We create a callable object and send the information to the platform
    // with a timeout of 2 seconds.
    // We specific this isn't a keep alive connection using `false` as the second
    // template parameter.
    //
    // For more information @see noos::cloud::callable
    // 
    std::string greet = "hello";
    callable<chatbot,false> query(callback, node, greet);
    query.send(2);
    return 0;
}
