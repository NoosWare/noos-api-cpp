#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>
#include <fstream>
#include <chrono>
#include <iostream>
#include <noos/objects.hpp>

/**
 * \brief TEST for time object
 *
 * We check the constructors creating identical objects and comparing 
 * between them.
 *
 * Methods seconds and nanoseconds are checked comparing the atributes
 * between the objects created before. They have to be the same.
 */
TEST_CASE("object_time_test", "[time]")
{
    std::chrono::nanoseconds t(1464949299093018853);
    noos::object::time obj_time1 = noos::object::time(t);
    noos::object::time obj_time2 = noos::object::time(t);
    REQUIRE(obj_time1 ==  obj_time2);

    REQUIRE(obj_time1.seconds == 1464949299);
    REQUIRE(obj_time1.nanoseconds == 93018853);

    // assignment constructor
    noos::object::time obj_time3(obj_time1);
    REQUIRE(obj_time1 == obj_time3); 

    // copy constructor
    auto obj_time4 = obj_time3;
    REQUIRE(obj_time3 == obj_time4);

    // test seconds
    uint32_t s_obj_time1 = obj_time1.seconds;
    uint32_t s_obj_time2 = obj_time2.seconds;
    REQUIRE(s_obj_time1 == s_obj_time2);

    // test nanoseconds
    uint64_t n_obj_time1 = obj_time1.nanoseconds;
    uint64_t n_obj_time2 = obj_time2.nanoseconds;
    REQUIRE(n_obj_time1 == n_obj_time2);

    // test comparison operator
    REQUIRE(obj_time1 == obj_time2);
}

/**
 * \brief TEST for picture object
 *
 * The constructor are checked creating identical
 * objects and comparing between them.
 *
 * To compare different images a vector of images
 * is created, to verify all of them
 */

TEST_CASE("object_picture_test", "[picture]")
{
    std::vector<std::string> infiles = { "tests/data/object_classes_picture_1.png", 
                                         "tests/data/object_classes_picture_2.jpg", 
                                         "tests/data/object_classes_picture_3.png", 
                                         "tests/data/object_classes_picture_4.jpg", 
                                         "tests/data/object_classes_picture_5.jpg", 
                                         "tests/data/object_classes_picture_6.jpg" };

    // Construct from a file-path
    noos::object::picture lena(infiles[0]);

    for (auto it = infiles.begin() + 1; it != infiles.end(); ++it) {
        // Construct from a file-path
        noos::object::picture picture1(*it);

        // Open a byte steam from file, and construct the picture
        std::ifstream bytestream(*it, std::ios::in | std::ios::binary | std::ios::ate);
        noos::object::picture picture_copy1(bytestream);
        REQUIRE(picture1 == picture_copy1);

        // Copy constructor
        noos::object::picture picture_copy2(picture1);
        REQUIRE(picture1 == picture_copy2);

        // Assignment
        noos::object::picture picture_copy3 = picture1;
        REQUIRE(picture_copy3 == picture1);

        REQUIRE(lena != picture1);
    }
}

/**
 * \brief TEST for audio object
 *
 * The constructors are checked creating identical
 * objects and comparing between them.
 *
 * Different audios are saved in a vector and 
 * they are used to compare between formats.
 */
TEST_CASE("object_audio_test", "[audio]")
{
    // audio tests
    std::vector<std::string> infiles = { "tests/data/object_classes_audio_1.ogg", 
                                         "tests/data/object_classes_audio_2.wav" 
                                       };

    noos::object::audio audio1(infiles.at(0));
    std::ifstream bytes1(infiles.at(0), std::ios::in | std::ios::binary | std::ios::ate);
    noos::object::audio audio1_ifstrm(bytes1);

    REQUIRE(audio1 == audio1_ifstrm);

    noos::object::audio audio2(infiles.at(1));
    noos::object::audio audio2_cpy = audio2;

    REQUIRE(audio2 == audio2_cpy);
}

/**
 * @brief TEST for config_file
 */
TEST_CASE("object config_file", "[config_file]")
{
    std::string filepath = "tests/data/config_test.ini";
    noos::object::config_file file1(filepath);
    noos::object::config_file file2(filepath);
    REQUIRE(file1.get_data() == file2.get_data());

    auto file3 = noos::object::config_file(filepath);
    REQUIRE(file1.get_data() == file3.get_data());
    REQUIRE(file1.get_data().size() == 28);

    auto file4 = file3;
    REQUIRE(file4.get_data() == file3.get_data());

    noos::object::config_file file5("tests/data/config_file.ini");
    REQUIRE(file5.get_data().size() == 5155);

}
