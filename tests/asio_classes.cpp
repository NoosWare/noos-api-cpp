#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>
#include <noos/cloud/asio/http_response.hpp>
#include <noos/cloud/asio/http_header.hpp>
#include <noos/cloud/asio/http_post.hpp>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/asio/platform.hpp>
#include <noos/objects/picture.hpp>


/**
 * \brief TEST for http_reponse class
 *
 * First, we check the constructor creating two equal objects and comparing
 * their attribute buffer between them.
 *
 * Second, method 'to_string()' is checked creating an string equal to argument
 * we pass to the constructor, and they are compared.
 *
 * Third, method 'strip_http_header' is checked creating manually a http header
 * and comparing with the header created by the class. It's checked too
 * if it's empty.
 *
 * Last, method 'has_content_lenght' is checked comparing with and size_t with
 * the same size that the header created before, and comparing them.
 */
SCENARIO("Create a http_response", "[http_response]") 
{
    GIVEN ("A std::string with the header data") {
        // header has zero content-length
        std::string hardcoded_header = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"; 
                    hardcoded_header += "Host: net.tutsplus.com\r\n";
                    hardcoded_header += "Accept-Encoding: gzip,deflate\r\n";
                    hardcoded_header += "Connection: keep-alive\r\n";
                    hardcoded_header += "Content-Length: 9\r\n";
                    hardcoded_header += "Cache-Control: no-cache\r\n\r\n";

        std::string buf = hardcoded_header;
        WHEN ("http_response is constructed") {
            auto obj1 = std::make_unique<noos::cloud::http_response>(buf);
            THEN ("the content lenght should be the same as the given header") {
                REQUIRE(obj1);
                REQUIRE(9 == obj1->content_length());
            }
        }
        WHEN ("http_response is copied") { 
            auto obj2 = std::make_unique<noos::cloud::http_response>(buf);
            THEN ("the data should be the same for both") { 
                REQUIRE(obj2);
                REQUIRE(9 == obj2->content_length());
            }
        }
    }
}

/**
 * \brief TEST for http_header class
 *
 * First,  we check the constructor and the  method 'to_string()' creating manually
 * an http header and comparing with the header created by the class.
 *
 * Second, method 'get boundary' is checked comparing the attibute of the first
 * object with itself
 */
SCENARIO("Create http_header", "[http_header]")
{
    GIVEN ("A known uri(std::string)") {
        std::string ur = "hop/test\r\n";
        noos::cloud::http_header head1(ur);
        THEN("The object is created") {
            REQUIRE(!head1.get_boundary().empty());
        }
        WHEN("http_header is given the platform data") {
            THEN("All the attributes are filled") {
                std::string head2 = "hop/test\r\n";
                            head2 += "Host: http://example:8080\r\n";
                            head2 += "User-Token: \r\n";
                            head2 += "Accept-Token: token\r\n";
                            head2 += "Content-Length: 8\r\n";
                            head2 += "\r\n\r\n";
    
                noos::cloud::platform info = { "http://example", "8080", "token"};
                unsigned int length_test = 8;
                std::string head3 = head1.to_string(info, length_test);
                REQUIRE(head3 == head2);

                std::string boundary_test = head1.get_boundary();
                REQUIRE(head1.get_boundary() == boundary_test);
            }
        }
    }
}

/**
 * \brief TEST for http_post class
 * First, we check the constructor creating two equal objects and comparing
 * their attribute buffer between them.
 *
 * Second, method 'to_string()' is checked creating a post header manually
 * equal that the class creates for comparing them.
 *
 * Third, both methods 'add_content' is checked creating a post data manually
 * and comparing with the one created by the class
 *
 * Last, method 'size' is checked using the same string and calculating
 * the size manually and with the method.
 */ 
SCENARIO("Test http_post", "[http_post]")
{
    GIVEN("http_post is constructed") {
        std::string boundary_example = noos::misc::random_boundary();
        auto post1 = std::unique_ptr<noos::cloud::http_post>(new noos::cloud::http_post(boundary_example)); 
        REQUIRE(post1);

        WHEN("A second http_post is constructed with the same boundary") {
            auto post2 = std::unique_ptr<noos::cloud::http_post>(new noos::cloud::http_post(boundary_example));
            THEN("Both objects are equals") {
                REQUIRE(post2);
                REQUIRE(post1->to_string() == post2->to_string());
            }
        }

        WHEN("Add_content method is called") {
            THEN("data attribute is filled(no image)") {
                // craft a manual POST Content Disposition and compare it to the method
                std::string string_post3 = post1->to_string()
                                         + "--" + boundary_example + "\r\n"
                                         + "Content-Disposition: form-data; name=\"blah\"\r\n\r\n"
                                         + "blah blah blah"
                                         + "\r\n"; 

                auto post4 = std::unique_ptr<noos::cloud::http_post>(new noos::cloud::http_post(boundary_example));
                REQUIRE(post4);
                post4->add_content("blah", "blah blah blah", true);
                // compare manual string with method one
                REQUIRE(post4->to_string() == string_post3);
            }
            THEN("data attribute is filled(with an image)") {
                // load the picture bytes
                const std::string file = "tests/data/asio_classes_qr_code_1.png";
                auto pic = std::unique_ptr<noos::object::picture>(new noos::object::picture(file));
                REQUIRE(pic);
                const auto bytes = pic->bytearray();
                std::string string_post4 = "--" + boundary_example + "\r\n"
                                         + "Content-Disposition: form-data; name=\"blah\"\r\n"
                                         + "Content-Type: application/octet-stream\r\n\r\n";
                string_post4.insert(string_post4.end(), bytes.begin(), bytes.end());
                string_post4 += "\r\n";                     

                auto post5 = std::unique_ptr<noos::cloud::http_post>(new noos::cloud::http_post(boundary_example));
                REQUIRE(post5);
                post5->add_content("blah", file, bytes);
                // test the content disposition for files with manual string
                REQUIRE(post5->to_string().size() == string_post4.size());
                // check post sizes
                unsigned int str_size = string_post4.size()*sizeof(std::string::value_type);
                REQUIRE(str_size == post5->size());
            }
        }
    }
}

/**
 * \brief TEST for http_request class
 */
SCENARIO("Test http_request", "[http_request]")
{
    GIVEN ("A known uri") {
        const std::string ur = "ur\r\n";
        std::string ur2 = ur;
        THEN ("http_request is constructed and create copies") {
            auto request_test1 = noos::cloud::http_request(ur);
            auto request_test2 = noos::cloud::http_request(request_test1);
            REQUIRE(request_test1 == request_test2);

            auto request_test3 = noos::cloud::http_request(ur, false);
            auto request_test4 = noos::cloud::http_request(request_test3);
            REQUIRE(request_test3 == request_test4);
        }
        THEN ("two different object constructed with the same uri are not equal") {
            auto request_test5 = noos::cloud::http_request(ur);
            auto request_test6 = noos::cloud::http_request(ur);
            REQUIRE((request_test5 == request_test6) == false);
        }
    }
}

/**
 * \brief TEST for platform
 */
SCENARIO("Test platform struct", "[platform]")
{
    GIVEN ("An address, a port, an user and a password") {
        THEN ("The platform can be created and copied") {
            noos::cloud::platform platform1 = { "192.168.1.1", "22", "pass", "user", "http" };
            REQUIRE(platform1.address == "192.168.1.1");
            REQUIRE(platform1.port == "22");
            REQUIRE(platform1.user == "user");
            REQUIRE(platform1.token == "pass");
            REQUIRE(platform1.protocol == "http");

            auto platform2 = platform1;
            REQUIRE(platform1.address == platform2.address);
            REQUIRE(platform1.port == platform2.port);
            REQUIRE(platform1.user == platform2.user);
            REQUIRE(platform1.token == platform2.token);
            REQUIRE(platform1.protocol == platform2.protocol);
        }
    }
    GIVEN ("A json with all the parameters need it for the platform") {
        THEN ("A platform can be created") {
            auto json1 = R"(
                      {
                        "platform":{ 
                                     "address" : "192.168.1.2",
                                     "port" : "23",
                                     "token" : "pass",
                                     "user" : "user",
                                     "protocol" : "http"
                                   } 
                       })"_json;
            auto platform3 = noos::cloud::platform()(json1);
            REQUIRE(platform3.address == "192.168.1.2");
            REQUIRE(platform3.port == "23");
            REQUIRE(platform3.user == "user");
            REQUIRE(platform3.token == "pass");
            REQUIRE(platform3.protocol == "http");
        }
    }
    GIVEN ("A file with a json with all the parameters need it for the platform") {
        THEN ("A platform can be created") {
            std::string filename = "tests/data/platform_file.json";
            auto platform4 = noos::cloud::platform()(filename);
            REQUIRE(platform4.address == "192.168.1.2");
            REQUIRE(platform4.port == "23");
            REQUIRE(platform4.user == "user");
            REQUIRE(platform4.token == "pass");
            REQUIRE(platform4.protocol == "http");

        }
    }
}
