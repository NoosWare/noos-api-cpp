#include <noos/noos>
#include <iostream>
// 
// Example which shows how a simple cloud call works.
// In this example we'll use `available_services` which returns a list of the
// services the noos platform supports.
// 
int main()
{
    using namespace noos::cloud;
    // 
    // This lambda will receive the reply from the cloud.
    // In order to use the correct callback, see the "callback" definition in each cloud class.
    // For example, the class `available_services` has a `callback` alias set to:
    //      `using callback = std::function<void(std::vector<service>)>;`
    // 
    auto callback = [](std::vector<std::string> services) {
         std::cout << "available services: " << std::endl;
         for (const auto name : services) {
            std::cout << name << std::endl;
         }
     };
    // 
    // We create a callable object and send the information to the platform
    // with a timeout of 2 seconds.
    // We specific this isn't a keep alive connection using `false` as the second
    // template parameter.
    //
    // For more information @see noos::cloud::callable
    // 
    auto query = call<available_services,false>(callback);
    query.send(2);
    return 0;
}
