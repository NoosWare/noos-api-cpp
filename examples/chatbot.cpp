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
    // 
    // We create a callable object and send the information to the platform
    // with a timeout of 2 seconds.
    // We specific this isn't a keep alive connection using `false` as the second
    // template parameter.
    //
    // For more information @see noos::cloud::callable
    // 
    std::string greet = "hello";
    callable<chatbot,false> query(callback, default_node, greet);
    query.send(2);
    return 0;
}
