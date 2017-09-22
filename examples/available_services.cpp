#include <noos/noos>
#include <iostream>
/*
 * Example which shows how a simple cloud call works.
 * In this example we'll use `available_services` which returns a list of the
 * services the noos platform supports.
 */
int main()
{
    using namespace noos::cloud;
    /*
     * Now construct a lambda, std::function or bind your own functor.
     * This functor will receive the reply from the cloud **asynchronously**!
     * In this example we'll pass an inline lambda as the callback.
     * In order to use the correct callback, see the "callback" definition in each cloud class.
     * For example, the class `available_services` has a `callback` alias set to:
     *      `using callback = std::function<void(std::vector<service>)>;`
     */
    auto request  = available_services();
    auto callback = [](std::vector<std::string> services) {
         std::cout << "available services: " << std::endl;
         for (const auto name : services) {
            std::cout << name << std::endl;
         }
     };
    /*
     * Finally we create a callable object and send the information to the platform
     * with a timeout of 2 seconds
     * For more information /see noos::cloud::callable
     *
     * The actual parameter depends on the cloud class you're using,
     * so for a complete list, you need to read and understand how each cloud class functions.
     */
    callable<available_services> callable_services(request, callback);
    callable_services.send(2);
    
    return 0;
}
