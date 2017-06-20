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
     * Construct the platform info setting the hostname/IP, port and authentication token.
     * Then proceed to create a cloud node, we'll use it to create and call the cloud services.
     */
	platform info = {"10.130.3.17", "8080", "mysecret", "alex"}; 
	node<> ctrl(info);

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
     * Finally we make and run call:
     * The simplest way is to use the `make_call` template function, specifying
     * as template parameter the cloud class you want to use (e.g., noos::cloud::available_services)
     *
     * The actual parameter depends on the cloud class you're using,
     * so for a complete list, you need to read and understand how each cloud class functions.
     */
    //ctrl.test_call(request, callback);
    
    return 0;
}
