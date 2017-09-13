#define CATCH_CONFIG_MAIN
#include <tests/Catch/single_include/catch.hpp>
#include <iostream>
#include <fstream>
#include <noos/misc/json/src/json.hpp>
#include <noos/objects.hpp>

/// \brief function to read a json file and it is converted 
//  into a string param
std::string read_json_file(const std::string file)
{
    if (file.empty()){
        throw std::runtime_error("empty file param");
    }
    std::ifstream t(file);
    if (t.good()) {
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();
	return buffer.str();
    }
    else {
        throw std::runtime_error("failed to open ifsteam");
    }
}

/**
 * \brief check noos::object::time for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for time", "[time]")
{
    std::string string = read_json_file("tests/data/json_classes_time.json");
    REQUIRE(!string.empty());

    auto json = nlohmann::json::parse(string); 
    const auto stamp = json.find("stamp");
    REQUIRE(stamp != json.end());

    noos::object::time time_obj = noos::object::time(stamp);
    REQUIRE(time_obj.seconds == 1464949299);
    REQUIRE(time_obj.nanoseconds == 93018853);
        
    nlohmann::json::object_t out = {{"stamp", time_obj.to_json()}};
    REQUIRE(json == out);
}

/**
 * \brief check noos::object::point for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for point", "[point]")
{
    std::string string = read_json_file("tests/data/json_classes_point.json");
    REQUIRE(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto position = json.find("position");
    REQUIRE(position != json.end());

    noos::object::point<double> point_obj = noos::object::point<double>(position);
    REQUIRE(point_obj.x == 0.9999999776482582);
    REQUIRE(point_obj.y == 0.9999999776482582);
    REQUIRE(point_obj.z == 0.0);

    nlohmann::json::object_t out = {{"position", point_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto point1 = point_obj;
    REQUIRE(point1 == point_obj);
    auto point2(point_obj);
    REQUIRE(point2 == point_obj);

    //Default constructor
    noos::object::point<float> point3;
    REQUIRE(point3.x == 0);
    REQUIRE(point3.y == 0);
    REQUIRE(point3.z == 0);
}

/**
 * \brief check noos::object::human for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for human", "[human]")
{
    std::string string = read_json_file("tests/data/json_classes_human.json");
    REQUIRE(!string.empty());

    const auto json = nlohmann::json::parse(string);
    const auto human_it = json.find("human");
    REQUIRE(human_it != json.end());

    auto human_obj = noos::object::human(human_it);
    nlohmann::json out = {{"human", human_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto human1 = human_obj;
    auto human2(human_obj);
    REQUIRE(human1 == human_obj);
    REQUIRE(human2 == human_obj);
}

/**
 * \brief check noos::object::face for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for face", "[face]")
{
    std::string string = read_json_file("tests/data/json_classes_face.json");
    REQUIRE(!string.empty());

    const auto json = nlohmann::json::parse(string);
    const auto face_it = json.find("faces");
    REQUIRE(face_it != json.end());

    auto face_obj = noos::object::face(face_it);
    nlohmann::json out = {{"faces", face_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto face1 = face_obj;
    auto face2(face_obj);
    REQUIRE(face1 == face_obj);
    REQUIRE(face2 == face_obj);

}

/**
 * \brief check noos::object::face_recognition_obj for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for face_recognition_obj", "[face_recognition_obj]")
{
    std::string string = read_json_file("tests/data/json_classes_face_recognition.json");
    REQUIRE(!string.empty());

    const auto json = nlohmann::json::parse(string);
    const auto face_it = json.find("faces");
    REQUIRE(face_it != json.end());

    auto face_obj = noos::object::face_recognition_obj(face_it);
    nlohmann::json out = {{"faces", face_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto face1 = face_obj;
    auto face2(face_obj);
    REQUIRE(face1 == face_obj);
    REQUIRE(face2 == face_obj);

}

/**
 * \brief check noos::object::orientation for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for orientation", "[orientation]")
{
    std::string string = read_json_file("tests/data/json_classes_orientation.json");
    REQUIRE(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto it = json.find("orientation");
    REQUIRE(it != json.end());

    noos::object::orientation<double> angles_obj = noos::object::orientation<double>(it);
    REQUIRE(angles_obj.roll  == 0.99999997);
    REQUIRE(angles_obj.pitch == 0.99999995);
    REQUIRE(angles_obj.yaw   == 0.99999996);

    nlohmann::json::object_t out = {{"orientation", angles_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto angles1 = angles_obj;
    REQUIRE(angles1 == angles_obj);
    auto angles2(angles_obj);
    REQUIRE(angles2 == angles_obj);

    //Default constructor
    noos::object::orientation<float> angles3;
    REQUIRE(angles3.roll == 0);
    REQUIRE(angles3.pitch == 0);
    REQUIRE(angles3.yaw == 0);
}

/**
 * \brief check noos::object::pose for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
TEST_CASE("Json test for pose", "[pose]")
{
    std::string string = read_json_file("tests/data/json_classes_pose.json");
    REQUIRE(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto it = json.find("pose");
    REQUIRE(it != json.end());

    noos::object::pose<double> pose_obj = noos::object::pose<double>(it);
    REQUIRE(pose_obj.coordinates.x == 0.9999991);
    REQUIRE(pose_obj.coordinates.y == 0.9999992);
    REQUIRE(pose_obj.coordinates.z == 0.0);
    REQUIRE(pose_obj.angles.roll  == 0.001);
    REQUIRE(pose_obj.angles.pitch == 0.002);
    REQUIRE(pose_obj.angles.yaw   == 0.17576372515799546);

    nlohmann::json::object_t out = {{"pose", pose_obj.to_json()}};
    REQUIRE(json == out);

    //Copy and assignment
    auto pose1 = pose_obj;
    REQUIRE(pose1 == pose_obj);
    auto pose2(pose_obj);
    REQUIRE(pose2 == pose_obj);

    //Default constructor
    noos::object::pose<float> pose3;
    REQUIRE(pose3.coordinates.x == 0);
    REQUIRE(pose3.coordinates.y == 0);
    REQUIRE(pose3.coordinates.z == 0);
    REQUIRE(pose3.angles.roll == 0);
    REQUIRE(pose3.angles.pitch == 0);
    REQUIRE(pose3.angles.yaw == 0);
}
