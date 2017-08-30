#define CATCH_CONFIG_MAIN
#include <tests/Catch/single_include/catch.hpp>
#include <fstream>
#include <noos/misc/json/src/json.hpp>
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
/**
 * \brief check noos::cloud::callable
 */
SCENARIO("A service needs to be call")
{
    using namespace noos::cloud;
    GIVEN("A service and its callback") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto face_request = face_detection(pic);
        auto callback = [&](std::vector<noos::object::face> faces) { 
            REQUIRE(faces.size() == 1);
        };
        THEN("A call can be made") {
            callable<face_detection,false>callable_obj(face_request, callback);
            REQUIRE(callable_obj.object.uri == "face_detection");
        }
    }
    GIVEN("A platform and a service known") {
        THEN("A callable object can be done") {
            auto callable_obj = std::make_unique<callable<face_detection>>(default_node);
            REQUIRE(callable_obj);
        }
    }
    GIVEN("A vision batch service and its callback") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto face_cb = [&](std::vector<noos::object::face> faces) {};
        auto human_cb = [&](std::vector<noos::object::human> humans) {};
        vision_batch<std::pair<face_detection,face_detection::callback>,
                 std::pair<human_detection,human_detection::callback>>
                 batch(pic, 
                       std::make_pair(face_detection(), face_cb), 
                       std::make_pair(human_detection(), human_cb));        

        THEN("A call can be made") {
            auto callable_obj = std::make_unique<callable<decltype(batch)>>(batch);
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
                "services" : [{
                               "name" : "name"
                              }],
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
    SECTION ("Face detection") {
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

    SECTION ("Light detection") {
        //Construct
        auto pic = noos::object::picture("tests/data/object_classes_picture_1.png");
        auto light_detect = light_detection(pic);
        REQUIRE(light_detect.uri == "light_detection"); 
        REQUIRE(light_detect.is_single_callable() == true);

        auto light_detect_batch = light_detection();
        REQUIRE(light_detect_batch.uri == "light_detection");
        REQUIRE(light_detect_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                    "light_level" : 500,
                    "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        int light = deserialize<light_detection,
                                typename light_detection::data_type>()(j1_string);    
        REQUIRE(light == 500);
    }

    SECTION ("Human detection") {
        //Construct
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

    SECTION("Orb algorthim") {
        auto pic = noos::object::picture("tests/data/object_classes_picture_2.jpg");
        auto orb_learn_obj = orb_learn_object(pic, "cat");
        REQUIRE(orb_learn_obj.uri == "orb_learn_object"); 
        REQUIRE(orb_learn_obj.is_single_callable() == true);

        auto orb_learn_obj_batch = orb_learn_object("cat");
        REQUIRE(orb_learn_obj_batch.uri == "orb_learn_object");
        REQUIRE(orb_learn_obj_batch.is_single_callable() == false);

        //Deserialize
        auto j1 = R"(
                  {
                      "result" : 0,
                      "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        int learn_reply = deserialize<orb_learn_object,
                                      typename orb_learn_object::data_type>()(j1_string);
        REQUIRE(learn_reply == 0);

        //Class object_detection_clear_models
        orb_clear_models orb_clear("user");
        REQUIRE(orb_clear.uri == "orb_clear_models"); 
        REQUIRE(orb_clear.is_single_callable() == true);

        //Deserialize
        auto j2 = R"(
                  {
                      "result" : 0,
                      "error" : ""
                  })"_json;
        std::string j2_string = j2.dump(-1);
        int clear_reply = deserialize<orb_clear_models,
                                      typename orb_clear_models::data_type>()(j2_string);
        REQUIRE(clear_reply == 0);

        //Class object_detection_load_models
        std::vector<std::string> names = {"cat"};
        orb_load_models load_models(names);
        REQUIRE(load_models.uri == "orb_load_models"); 
        REQUIRE(load_models.is_single_callable() == true);

        auto j3 = R"(
                  {
                      "result" : 0,
                      "error" : ""
                  })"_json;
        std::string j3_string = j3.dump(-1);
        int load_models_reply = deserialize<orb_load_models,
                                            typename orb_load_models::data_type>()(j3_string);
        REQUIRE(load_models_reply == 0);

        //Class object_detection_find_objects 
        auto orb_find_obj = orb_find_objects(pic, 1);
        REQUIRE(orb_find_obj.uri == "orb_find_objects"); 
        REQUIRE(orb_find_obj.is_single_callable() == true);

        auto orb_find_obj_batch = orb_find_objects(1);
        REQUIRE(orb_find_obj_batch.uri == "orb_find_objects");
        REQUIRE(orb_find_obj_batch.is_single_callable() == false);
        auto j4 = R"(
                  {
                    "found_names": ["cat"],
                    "found_centers": [{
                                          "x": 0.999,
                                          "y": 0.999,
                                          "z": 0 
                                     },
                                     {
                                          "x": 0.899,
                                          "y": 0.799,
                                          "z": 0 
                                     }],
                    "found_scores": [0.9],
                    "result": 0,
                    "error": ""
                  })"_json;
        std::string j4_string = j4.dump(-1);
        noos::object::orb_object orb_reply;
        orb_reply = deserialize<orb_find_objects,
                                typename orb_find_objects::data_type>()(j4_string);
        REQUIRE(orb_reply.names.at(0) == "cat");
        REQUIRE(orb_reply.points.at(0).x == 0.999);
        REQUIRE(orb_reply.points.at(0).y == 0.999);
        REQUIRE(orb_reply.points.at(0).z == 0);
        REQUIRE(orb_reply.points.at(1).x == 0.899);
        REQUIRE(orb_reply.points.at(1).y == 0.799);
        REQUIRE(orb_reply.points.at(1).z == 0);
        REQUIRE(orb_reply.scores.at(0) == 0.9);
        REQUIRE(orb_reply.result == 0);

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
    }

    SECTION("Object recognition") {
        //Class object_recognition
        auto pic = noos::object::picture("tests/data/object_classes_picture_2.jpg");
        auto obj_recognition = object_recognition(pic);
        REQUIRE(obj_recognition.uri == "object_recognition_caffe");
        REQUIRE(obj_recognition.is_single_callable() == true);

        auto obj_recog_batch = object_recognition();
        REQUIRE(obj_recog_batch.uri == "object_recognition_caffe");
        REQUIRE(obj_recog_batch.is_single_callable() == false);

        auto j1 = R"(
                  {
                    "object_class" : "something",
                    "error" : ""
                  })"_json;
        std::string j1_string = j1.dump(-1);
        std::string reply = deserialize<object_recognition,
                                        typename object_recognition::data_type>()(j1_string);
        REQUIRE(reply == "something");
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
    };

    //Class face_detection
    auto face_call = [] (std::vector<noos::object::face> faces) {
        REQUIRE(faces.at(0).top_left_x == 1);
        REQUIRE(faces.at(0).top_left_y == 2);   
        REQUIRE(faces.at(0).bottom_right_x == 3);
        REQUIRE(faces.at(0).bottom_right_y == 4);

    };

    vision_batch<std::pair<face_detection, face_detection::callback>,
                 std::pair<qr_recognition, qr_recognition::callback>> 
                                  vision_batch_obj( pic,
                                                    std::make_pair(face_detection(), face_call),
                                                    std::make_pair(qr_recognition(), qr_call)
                                                  );    
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
    SECTION("Icp slam") {
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

        auto icp = icp_slam(laser);
        REQUIRE(icp.uri == "slam");
        REQUIRE(icp.is_single_callable() == true);

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
}
