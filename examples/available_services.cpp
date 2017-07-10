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
     * 
     * In order to use the correct callback, see the "callback" definition in each cloud class.
     * For example, the class `available_services` has a `callback` alias set to:
     *
     *      `using callback = std::function<void(std::vector<service>)>;`
     *
     * The `service` is simply another alias set to:
     *
     *      `using service  = std::pair<std::string,std::string>;`
     */
    auto request  = available_services();
    auto callback = [](std::vector<std::pair<std::string, std::string>> services) {
         std::cout << "available services: " << std::endl;
         for (const auto & pair : services) {
            std::cout << pair.first << " " << pair.second << std::endl;
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
    callable<available_services> cb(request, callback);
    cb.send(2);
    
    return 0;
}
