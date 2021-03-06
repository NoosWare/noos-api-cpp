#define CATCH_CONFIG_MAIN
#include <tests/catch.hpp>
#include <fstream>
#include <noos/misc/json.hpp>
#include <noos/noos>

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

struct get_platform
{
    noos::cloud::platform operator()() {
        noos::cloud::platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
        return node;
    }
};
/**
 * \brief check noos::cloud::callable
 */
SCENARIO("A service needs to be call")
{
    using namespace noos::cloud;
    GIVEN("A service and its callback") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto callback = [&](std::vector<noos::object::face> faces) { 
            REQUIRE(faces.size() == 1);
        };
        THEN("A call can be made") {
            callable<face_detection,false>callable_obj(callback, get_platform()(), pic);
            REQUIRE(callable_obj.object.uri == "face_detection");
        }
    }
    GIVEN("A vision batch service and its callback") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto face_cb = [&](std::vector<noos::object::face> faces) {};
        auto human_cb = [&](std::vector<noos::object::human> humans) {};
        vision_batch<tied<face_detection>,
                     tied<human_detection>> batch(pic, 
                                                  tied<face_detection>(face_cb), 
                                                  tied<human_detection>(human_cb));
        THEN("A call can be made") {
            auto callable_obj = std::make_unique<callable<decltype(batch)>>(batch, get_platform()());
            REQUIRE(callable_obj);
        }
    }
}

/**
 * \brief check noos::cloud::available_services
 * A json is done manually to be sure about results.
 */    
TEST_CASE("Test service Available services", "[available_services]")
{
    std::vector<std::string> services;
    noos::cloud::available_services available_serv;
    auto j1 = R"(
              {
                "services" : [
                               "name" 
                             ],
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    services = noos::cloud::deserialize<noos::cloud::available_services,
                                        typename noos::cloud::available_services::data_type>()(j1_string);
    REQUIRE(services.at(0) == "name");
}

/**
 * \brief check the vision detection classes
 */  
TEST_CASE("Test services vision detection", "[vision_detection]")
{
    using namespace noos::cloud;
    SECTION ("Face detection") 
    {
        //Construct
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto face_detect = face_detection(pic); 
        REQUIRE(face_detect.uri == "face_detection"); 
        REQUIRE(face_detect.is_single_callable() == true);

        auto face_detect_batch = face_detection();
        REQUIRE(face_detect_batch.uri == "face_detection");
        REQUIRE(face_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                    "faces":[{ 
                                "up_left_point":{
                                                    "x": 1, 
                                                    "y": 2
                                }, 
                                "down_right_point":{
                                                    "x": 3, 
                                                    "y": 4
                                } 
                     }],
                     "error" : ""
                   })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<noos::object::face> faces;
        faces = deserialize<face_detection,
                            typename face_detection::data_type>()(j1_string);
        REQUIRE(faces.at(0).top_left_x == 1);
        REQUIRE(faces.at(0).top_left_y == 2);   
        REQUIRE(faces.at(0).bottom_right_x == 3);
        REQUIRE(faces.at(0).bottom_right_y == 4);

    }

    SECTION ("Human detection") 
    {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto human_detect = human_detection(pic);
        REQUIRE(human_detect.uri == "human_detection"); 
        REQUIRE(human_detect.is_single_callable() == true);

        auto human_detect_batch = human_detection();
        REQUIRE(human_detect_batch.uri == "human_detection");
        REQUIRE(human_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                      "humans":[{ 
                                  "up_left_point":{
                                                      "x": 1, 
                                                      "y": 2
                                  }, 
                                  "down_right_point":{
                                                      "x": 3, 
                                                      "y": 4
                                  } 
                      }],
                      "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<noos::object::human> humans;
        humans = deserialize<human_detection,
                             typename human_detection::data_type>()(j1_string);
        REQUIRE(humans.at(0).top_left_x == 1);
        REQUIRE(humans.at(0).top_left_y == 2);
        REQUIRE(humans.at(0).bottom_right_x == 3);
        REQUIRE(humans.at(0).bottom_right_y == 4);
    }

    SECTION("ORB algorithm") 
    {
        auto pic = noos::object::picture("tests/data/object_classes_picture_2.jpg");
        auto orb_learn_obj = orb_add_model(pic, "cat");
        REQUIRE(orb_learn_obj.uri == "orb_add_model"); 
        REQUIRE(orb_learn_obj.is_single_callable() == true);

        auto orb_learn_obj_batch = orb_add_model("cat");
        REQUIRE(orb_learn_obj_batch.uri == "orb_add_model");
        REQUIRE(orb_learn_obj_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                      "result" : true,
                      "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        bool learn_reply = deserialize<orb_add_model,
                                      typename orb_add_model::data_type>()(j1_string);
        REQUIRE(learn_reply);

        //Class object_detection_clear_models
        orb_del_model orb_clear("user");
        REQUIRE(orb_clear.uri == "orb_del_model"); 
        REQUIRE(orb_clear.is_single_callable() == true);

        //Deserialize
        auto j2 = R"(
                  {
                      "result" : true,
                      "error" : ""
                  })"_json;
        std::string j2_string = j2.dump(-1);
        bool clear_reply = deserialize<orb_del_model,
                                      typename orb_del_model::data_type>()(j2_string);
        REQUIRE(clear_reply);

        //Class object_detection_find_objects 
        auto orb_find_obj = orb_query(pic, "cat", 200);
        REQUIRE(orb_find_obj.uri == "orb_query"); 
        REQUIRE(orb_find_obj.is_single_callable() == true);

        auto orb_find_obj_batch = orb_query("cat", 200);
        REQUIRE(orb_find_obj_batch.uri == "orb_query");
        REQUIRE(orb_find_obj_batch.is_single_callable() == false);
        auto j4 = R"(
                  {
                    "keypoints": [{
                                      "x": 0.999,
                                      "y": 0.999
                                 },
                                 {
                                      "x": 0.899,
                                      "y": 0.799
                                 }],
                    "error" : ""
                  })"_json;
        std::string j4_string = j4.dump(-1);
        std::vector<noos::object::point2d<float>> orb_reply;
        orb_reply = deserialize<orb_query,
                                typename orb_query::data_type>()(j4_string);
        REQUIRE(orb_reply.at(0).x == 0.999f);
        REQUIRE(orb_reply.at(0).y == 0.999f);
        REQUIRE(orb_reply.at(1).x == 0.899f);
        REQUIRE(orb_reply.at(1).y == 0.799f);
    }

    SECTION ("Gender detection") 
    {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto gender_detect = gender_detection(pic);
        REQUIRE(gender_detect.uri == "gender_detection"); 
        REQUIRE(gender_detect.is_single_callable() == true);

        auto gender_detect_batch = gender_detection();
        REQUIRE(gender_detect_batch.uri == "gender_detection");
        REQUIRE(gender_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                      "result":[{ 
                                  "gender": "male", 
                                  "probability" : 10
                                   
                                 }],
                      "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<std::pair<std::string,float>> gender;
        gender = deserialize<gender_detection,
                             typename gender_detection::data_type>()(j1_string);
        REQUIRE(gender.at(0).first == "male");
        REQUIRE(gender.at(0).second == 10);
    }

    SECTION ("Age detection") 
    {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto age_detect = age_detection(pic);
        REQUIRE(age_detect.uri == "age_detection"); 
        REQUIRE(age_detect.is_single_callable() == true);

        auto age_detect_batch = age_detection();
        REQUIRE(age_detect_batch.uri == "age_detection");
        REQUIRE(age_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                      "result":[{ 
                                  "age_range": "20-30", 
                                  "probability" : 10
                                   
                                 }],
                      "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<std::pair<std::string,float>> age;
        age = deserialize<age_detection,
                             typename age_detection::data_type>()(j1_string);
        REQUIRE(age.at(0).first == "20-30");
        REQUIRE(age.at(0).second == 10);
    }

    SECTION ("Object detection") 
    {
        //Construct
        auto pic = noos::object::picture("tests/data/object_classes_picture_10.jpg");
        auto object_detect = object_detection(pic); 
        REQUIRE(object_detect.uri == "object_detection"); 
        REQUIRE(object_detect.is_single_callable() == true);

        auto object_detect_batch = object_detection();
        REQUIRE(object_detect_batch.uri == "object_detection");
        REQUIRE(object_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                    "objects": [
                                {
                                    "confidence": 0.9681121706962585,
                                    "down_right_point": {
                                        "x": 467,
                                        "y": 489
                                    },
                                    "label": "chair",
                                    "up_left_point": {
                                        "x": 178,
                                        "y": 110
                                    }
                                }],
                     "error" : ""
                   })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<noos::object::object> objects;
        objects = deserialize<object_detection,
                            typename object_detection::data_type>()(j1_string);
        REQUIRE(objects.at(0).top_left_x == 178);
        REQUIRE(objects.at(0).top_left_y == 110);   
        REQUIRE(objects.at(0).bottom_right_x == 467);
        REQUIRE(objects.at(0).bottom_right_y == 489);
        REQUIRE(objects.at(0).confidence == 0.9681121706962585 );
        REQUIRE(objects.at(0).label == "chair");

    }
}

/**
 * \brief check the vision recognition classes 
 */
TEST_CASE("Test services vision recognition", "[vision_recognition]")
{
    using namespace noos::cloud;
    SECTION("Qr recognition") {
        auto pic_qr = noos::object::picture("tests/data/asio_classes_qr_code_1.png");
        auto qr_obj = qr_recognition(pic_qr);
        REQUIRE(qr_obj.uri == "qr_recognition"); 
        REQUIRE(qr_obj.is_single_callable() == true);

        auto qr_obj_batch = qr_recognition();
        REQUIRE(qr_obj_batch.uri == "qr_recognition");
        REQUIRE(qr_obj_batch.is_single_callable() == false);

        auto j1 = R"(
                  {
                    "qrs":[{ 
                            "x": 1, 
                            "y": 2,
                            "size": 10,
                            "message": "label"
                          }], 
                    "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<noos::object::qr_code> qr_reply;
        qr_reply = deserialize<qr_recognition,
                                typename qr_recognition::data_type>()(j1_string);
        REQUIRE(qr_reply.at(0).message == "label");
        REQUIRE(qr_reply.at(0).centre_x == 1);
        REQUIRE(qr_reply.at(0).centre_y == 2);
        REQUIRE(qr_reply.at(0).size == 10);
    }

    SECTION("Object recognition") {
        //Class object_recognition
        auto pic = noos::object::picture("tests/data/object_classes_picture_2.jpg");
        auto obj_recognition = object_recognition(pic);
        REQUIRE(obj_recognition.uri == "object_recognition");
        REQUIRE(obj_recognition.is_single_callable() == true);

        auto obj_recog_batch = object_recognition();
        REQUIRE(obj_recog_batch.uri == "object_recognition");
        REQUIRE(obj_recog_batch.is_single_callable() == false);

        auto j1 = R"(
                  {
                    "result" : [{ 
                                "label" : "name",
                                "probability" : 30
                               }],
                    "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        auto reply = deserialize<object_recognition,
                                        typename object_recognition::data_type>()(j1_string);
        REQUIRE(reply.at(0).first == "name");
        REQUIRE(reply.at(0).second == 30);
    }

    SECTION("Face recognition") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto face_recog = face_recognition(pic); 
        REQUIRE(face_recog.uri == "face_recognition"); 
        REQUIRE(face_recog.is_single_callable() == true);

        auto face_recog_batch = face_recognition();
        REQUIRE(face_recog_batch.uri == "face_recognition");
        REQUIRE(face_recog_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                    "faces":[{
                                "rect" : { 
                                            "up_left_point":{
                                                                "x": 1, 
                                                                "y": 2
                                            }, 
                                            "down_right_point":{
                                                                "x": 3, 
                                                                "y": 4
                                            }
                                         },
                                "confidence" : 100,
                                "label" : 2,
                                "name" : "name" 
                     }],
                     "error" : ""
                   })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<noos::object::person> faces;
        faces = deserialize<face_recognition,
                            typename face_recognition::data_type>()(j1_string);
        REQUIRE(faces.at(0).face_rect.top_left_x == 1);
        REQUIRE(faces.at(0).face_rect.top_left_y == 2);   
        REQUIRE(faces.at(0).face_rect.bottom_right_x == 3);
        REQUIRE(faces.at(0).face_rect.bottom_right_y == 4);
        REQUIRE(faces.at(0).confidence == 100);
        REQUIRE(faces.at(0).label == 2);
        REQUIRE(faces.at(0).name == "name");
    }

    SECTION("Face expression") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto expression_obj = face_expression(pic);
        REQUIRE(expression_obj.uri == "face_expression"); 
        REQUIRE(expression_obj.is_single_callable() == true);

        auto expression_obj_batch =face_expression();
        REQUIRE(expression_obj_batch.uri == "face_expression");
        REQUIRE(expression_obj_batch.is_single_callable() == false);

        auto j1 = R"(
                  {
                    "result":[{ 
                                "emotion": "happy", 
                                "probability": 50
                              }], 
                    "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::vector<std::pair<std::string, float>> reply;
        reply = deserialize<face_expression,
                            typename face_expression::data_type>()(j1_string);
        REQUIRE(reply.at(0).first == "happy");
        REQUIRE(reply.at(0).second == 50);
    }
}

/**
 * \brief check the vision batch class
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 */
TEST_CASE("Test service vision_batch", "[vision_batch]")
{
    using namespace noos::cloud;
    auto pic = noos::object::picture("tests/data/asio_classes_qr_code_1.png");

    //Class qr_recognition
    auto qr_call = [] (std::vector<noos::object::qr_code> qrs) {
        REQUIRE(qrs.at(0).message == "label");
        REQUIRE(qrs.at(0).centre_x == 1);
        REQUIRE(qrs.at(0).centre_y == 2);
        REQUIRE(qrs.at(0).size == 10);
    };

    //Class face_detection
    auto face_call = [] (std::vector<noos::object::face> faces) {
        REQUIRE(faces.at(0).top_left_x == 1);
        REQUIRE(faces.at(0).top_left_y == 2);   
        REQUIRE(faces.at(0).bottom_right_x == 3);
        REQUIRE(faces.at(0).bottom_right_y == 4);

    };

    vision_batch<tied<face_detection>,tied<qr_recognition>> 
          vision_batch_obj(pic,
                           tied<face_detection>(face_call),
                           tied<qr_recognition>(qr_call));    
    REQUIRE(vision_batch_obj.is_single_callable() == true);
    auto j1 = R"(
              [{
                    "face_detection" : { "faces":[{ 
                                                    "up_left_point":{
                                                                        "x": 1, 
                                                                        "y": 2
                                                    }, 
                                                    "down_right_point":{
                                                                        "x": 3, 
                                                                        "y": 4
                                                    } 
                                               }],
                                         "error" : ""
                                       },
                    "qr_recognition" : { "qrs":[{ 
                                                    "x": 1, 
                                                    "y": 2,
                                                    "size": 10,
                                                    "message": "label"
                                               }], 
                                         "error" : ""
                                       }
              }])"_json;
    std::string j1_str = j1.dump(-1);
    vision_batch_obj.process(j1_str);
}

/**
 * \brief check the navigation classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 */
TEST_CASE("Test navigation services", "[navigation]")
{
    using namespace noos::cloud;

    SECTION("Empty laser data") {
        noos::object::laser empty;
        REQUIRE_NOTHROW(icp_slam("new_map", "icp.ini", empty));
    }
    std::string string = read_json_file("tests/data/cloud_class_laser_data.json");
    REQUIRE(!string.empty());

    //Filling laser data
    auto json = nlohmann::json::parse(string);
    std::vector<float> laser_ranges = json["ranges"];
    std::vector<int> laser_intensities = json["intensities"];
    noos::object::laser laser;
    laser.ranges = laser_ranges;
    laser.intensities = laser_intensities;
    laser.aperture = 4.71239;
    laser.max_range = 10.0f;
    laser.std_error = 0.02;
    laser.right_to_left = true;
    laser.pose3d = noos::object::pose<float>(); 

    SECTION("Icp slam") {
        auto icp = icp_slam("new_map", "icp.ini", laser);
        REQUIRE(icp.uri == "slam");
        REQUIRE(icp.is_single_callable() == true);

        auto icp_obs = icp_slam(laser);
        REQUIRE(icp_obs.uri == "slam");
        REQUIRE(icp_obs.is_single_callable() == true);


        auto j1 = R"(
                    {
                        "pose": {
                                    "position": {
                                                    "x": 0.99991,
                                                    "y": 0.99992,
                                                    "z": 0.0
                                                },
                                    "orientation": {
                                                    "roll"  : 0.001,
                                                    "pitch" : 0.002,
                                                    "yaw"   : 0.175763
                                                   }
                                },
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto pose_obj = deserialize<icp_slam,
                                        typename icp_slam::data_type>()(j1_string);
        REQUIRE(pose_obj.coordinates.x == 0.99991f);
        REQUIRE(pose_obj.coordinates.y == 0.99992f);
        REQUIRE(pose_obj.coordinates.z == 0.0f);
        REQUIRE(pose_obj.angles.roll  == 0.001f);
        REQUIRE(pose_obj.angles.pitch == 0.002f);
        REQUIRE(pose_obj.angles.yaw   == 0.175763f);
    }

    SECTION("Rbpf slam") {
        noos::object::odometry increase_od;
        increase_od.inc_x = 0;
        increase_od.inc_y = 0;
        increase_od.inc_yaw = 0;
        auto rbpf = rbpf_slam("new_map", "rbpf.ini", laser, increase_od);
        REQUIRE(rbpf.uri == "slam");
        REQUIRE(rbpf.is_single_callable() == true);

        auto rbpf_obs = rbpf_slam(laser, increase_od);
        REQUIRE(rbpf_obs.uri == "slam");
        REQUIRE(rbpf_obs.is_single_callable() == true);



        auto j1 = R"(
                    {
                        "pose": {
                                    "position": {
                                                    "x": 0.99991,
                                                    "y": 0.99992,
                                                    "z": 0.0
                                                },
                                    "orientation": {
                                                    "roll"  : 0.001,
                                                    "pitch" : 0.002,
                                                    "yaw"   : 0.175763
                                                   }
                                },
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto pose_obj = deserialize<rbpf_slam,
                                        typename rbpf_slam::data_type>()(j1_string);
        REQUIRE(pose_obj.coordinates.x == 0.99991f);
        REQUIRE(pose_obj.coordinates.y == 0.99992f);
        REQUIRE(pose_obj.coordinates.z == 0.0f);
        REQUIRE(pose_obj.angles.roll  == 0.001f);
        REQUIRE(pose_obj.angles.pitch == 0.002f);
        REQUIRE(pose_obj.angles.yaw   == 0.175763f);
    }

    SECTION("Delete a map") {
        delete_map remove_map("old_map");
        REQUIRE(remove_map.uri == "delete_map");
        REQUIRE(remove_map.is_single_callable());
        auto j1 = R"(
                    {
                        "success": true,
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto success = deserialize<delete_map,
                                   typename delete_map::data_type>()(j1_string);
        REQUIRE(success);
    }

    SECTION("Upload a map") {
        auto pic = noos::object::picture("tests/data/map_picture.png");
        upload_map new_map("old_map", pic);
        REQUIRE(new_map.uri == "upload_map");
        REQUIRE(new_map.is_single_callable());
        auto j1 = R"(
                    {
                        "success": true,
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto success = deserialize<upload_map,
                                   typename upload_map::data_type>()(j1_string);
        REQUIRE(success);
    }

    SECTION("Upload a config_file") {
        auto file = noos::object::config_file("tests/data/config_file.ini");
        upload_slam_config_file new_file(file, "example.ini", slam_type::icp);
        REQUIRE(new_file.uri == "upload_slam_config_file");
        REQUIRE(new_file.is_single_callable());
        auto j1 = R"(
                    {
                        "success": true,
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto success = deserialize<upload_map,
                                   typename upload_slam_config_file::data_type>()(j1_string);
        REQUIRE(success);
    }

    SECTION("Get map") {
        get_map new_map("old_map");
        REQUIRE(new_map.uri == "get_map");
        REQUIRE(new_map.is_single_callable());

        std::string filename = "tests/data/get_map.json"; 
        std::ifstream f(filename.c_str());
        std::stringstream buffer;
        buffer << f.rdbuf();
        f.close();
        nlohmann::json j1 = json::parse(buffer.str());

        std::string j1_string = j1.dump(-1);
        auto success = deserialize<get_map,
                                   typename get_map::data_type>()(j1_string);
        REQUIRE(success);
    }

    SECTION("Path planning") {
        noos::object::pose2d<float> point = {0.0f, 0.0f, 0.0f};
        float resolution = 0.05;
        float robot_radius = 0.2;
        path_planning new_path(point,
                               point,
                               robot_radius,
                               resolution,
                               "map_name");
        REQUIRE(new_path.uri == "path_planning");
        REQUIRE(new_path.is_single_callable());
        auto j1 = R"(
                    {
                        "points": [{
                                      "x" : 1,
                                      "y" : 2
                                   },
                                   { 
                                     "x" : 2,
                                     "y" : 3
                                   }],
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto path = deserialize<path_planning,
                                typename path_planning::data_type>()(j1_string);
        REQUIRE(path.at(0).x == 1);
        REQUIRE(path.at(1).x == 2);
        REQUIRE(path.at(0).y == 2);
        REQUIRE(path.at(1).y == 3);
    }
}

/**
 * \brief check the navigation classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 */
TEST_CASE("Test chat services", "[chat]")
{
    SECTION("Chatbot") {
        noos::cloud::chatbot new_chat("Hello");
        REQUIRE(new_chat.uri == "chat");
        REQUIRE(new_chat.is_single_callable());
        auto j1 = R"(
                    {
                        "reply": "Hello",
                        "error" : ""
                    })"_json;
        std::string j1_string = j1.dump(-1);
        auto success = noos::cloud::deserialize<noos::cloud::chatbot,
                                                typename noos::cloud::chatbot::data_type>()(j1_string);
        REQUIRE(success == "Hello");
    }
}
