#define BOOST_TEST_MODULE ServiceTest
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <rapp/misc/json.hpp>
#include <rapp/cloud.hpp>

BOOST_AUTO_TEST_SUITE (cloud_calls)

/**
 * \brief check rapp::cloud::available_services
 * A callback function is done to check that the 
 * desearialization is correct.
 * A json is done manually to be sure about results.
 */    
/*
BOOST_AUTO_TEST_CASE(available_services_cloud_test)
{
    auto callback = [] (std::vector<std::pair<std::string, std::string>> service) {
        BOOST_CHECK_EQUAL(service.at(0).first, "name");
        BOOST_CHECK_EQUAL(service.at(0).second, "url");
    };
    rapp::cloud::available_services as1(callback);
    auto j1 = R"(
              {
                "services" : [{
                               "name" : "name",
                               "url" : "url"
                              }],
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    as1.deserialise(j1_string);
}
*/

/**
 * \brief check the vision detection classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */  
BOOST_AUTO_TEST_CASE(vision_detection_cloud_test)
{
    //Class face_detection
    auto face_call = [] (std::vector<rapp::object::face> faces) {
        BOOST_CHECK_EQUAL(faces.at(0).get_left_x(), 1);
        BOOST_CHECK_EQUAL(faces.at(0).get_left_y(), 2);   
        BOOST_CHECK_EQUAL(faces.at(0).get_right_x(), 3);
        BOOST_CHECK_EQUAL(faces.at(0).get_right_y(), 4);

    };
    auto pic = rapp::object::picture("tests/data/object_classes_picture_1.png");
    auto fd = std::make_shared<rapp::cloud::face_detection>(pic, false, face_call); 
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
    fd->process(j1_string);
    //Class door_angle_detection
    auto door_call = [] (double angle) {
        BOOST_CHECK_EQUAL(angle, 5);
    };
    auto dad = std::make_shared<rapp::cloud::door_angle_detection>(pic, door_call);
    auto j2 = R"(
              {
                "door_angle" : 5,
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    dad->process(j2_string);
    //Class light_detection
    auto light_call = [] (int level) {
       BOOST_CHECK_EQUAL(level, 500);
    };
    auto ld = std::make_shared<rapp::cloud::light_detection>(pic, light_call);
    auto j3 = R"(
              {
                "light_level" : 500,
                "error" : ""
              })"_json;
    std::string j3_string = j3.dump(-1);
    ld->process(j3_string); 
    //Class human_detection
    auto human_call = [] (std::vector<rapp::object::human> humans) {
        BOOST_CHECK_EQUAL(humans.at(0).get_left_x(), 1);
        BOOST_CHECK_EQUAL(humans.at(0).get_left_y(), 2);   
        BOOST_CHECK_EQUAL(humans.at(0).get_right_x(), 3);
        BOOST_CHECK_EQUAL(humans.at(0).get_right_y(), 4);

    };
    auto hd = std::make_shared<rapp::cloud::human_detection>(pic, human_call);
    auto j4 = R"(
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
    std::string j4_string = j4.dump(-1);
    hd->process(j4_string);

    //Class object_detection_learn_object
    auto learn_call = [] (int result)
    {
        BOOST_CHECK_EQUAL(result, 0);
    };
    auto odlo = std::make_shared<rapp::cloud::object_detection_learn_object>(pic, "cat", "user", learn_call);
    auto j5 = R"(
              {
                  "result" : 0,
                  "error" : ""
              })"_json;
    std::string j5_string = j5.dump(-1);
    odlo->process(j5_string);

    //Class object_detection_clear_models
    auto clear_call = [] (int result)
    {
        BOOST_CHECK_EQUAL(result, 0);
    };
    rapp::cloud::object_detection_clear_models odcm("user", clear_call);
    auto j6 = R"(
              {
                  "result" : 0,
                  "error" : ""
              })"_json;
    std::string j6_string = j6.dump(-1);
    odcm.process(j6_string);

    //Class object_detection_load_models
    auto load_call = [] (int result) {
        BOOST_CHECK_EQUAL(result, 0);
    };

    std::vector<std::string> names = {"cat"};
    rapp::cloud::object_detection_load_models odlm("user", names, load_call);
    auto j7 = R"(
              {
                  "result" : 0,
                  "error" : ""
              })"_json;
    std::string j7_string = j7.dump(-1);
    odlm.process(j7_string);

    //Class object_detection_find_objects 
    auto find_call = [] (rapp::object::orb_object orb)
    {
        BOOST_CHECK_EQUAL(orb.names.at(0), "cat");
        BOOST_CHECK_EQUAL(orb.points.at(0).get_x(), 0.999);      
        BOOST_CHECK_EQUAL(orb.points.at(0).get_y(), 0.999);
        BOOST_CHECK_EQUAL(orb.scores.at(0), 0.9);
        BOOST_CHECK_EQUAL(orb.result, 0);
    };
    auto odfo = std::make_shared<rapp::cloud::object_detection_find_objects>(pic, "user", 1, find_call);
    auto j8 = R"(
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
    std::string j8_string = j8.dump(-1);
    odfo->process(j8_string);
}

/**
 * \brief check the vision recognition classes 
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(vision_recognition_cloud_test)
{
    //Class qr_recognition
    auto qr_call = [] (std::vector<rapp::object::qr_code> qrs) {
        BOOST_CHECK_EQUAL(qrs.at(0).label(), "label");
        rapp::object::qr_code qr2(1 ,2, "label");
        BOOST_CHECK(qrs.at(0) == qr2);
    };
    auto pic_qr = rapp::object::picture("tests/data/asio_classes_qr_code_1.png");
    auto qd = std::make_shared<rapp::cloud::qr_recognition>(pic_qr, qr_call);
    auto j1 = R"(
              {
                "qr_centers":[{ 
                                "x": 1, 
                                "y": 2
                              }], 
                "qr_messages":["label"],
                "error" : ""
              })"_json;
    std::string j1_string = j1.dump(-1);
    qd->process(j1_string);

    //Class object_recognition
    auto object_call = [] (std::string object) {
        BOOST_CHECK_EQUAL(object, "something");
    };
    auto pic = rapp::object::picture("tests/data/object_classes_picture_2.jpg");
    auto objr = std::make_shared<rapp::cloud::object_recognition>(pic, object_call);
    auto j2 = R"(
              {
                "object_class" : "something",
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    objr->process(j2_string);
}

/**
 * \brief check the vision batch class
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(vision_batch_test)
{
    //Vision batch
    auto pic = rapp::object::picture("tests/data/asio_classes_qr_code_1.png");

    //Class qr_recognition
    auto qr_call = [] (std::vector<rapp::object::qr_code> qrs) {
        BOOST_CHECK_EQUAL(qrs.at(0).label(), "label");
        rapp::object::qr_code qr2(1 ,2, "label");
        BOOST_CHECK(qrs.at(0) == qr2);
    };

    //Class face_detection
    auto face_call = [] (std::vector<rapp::object::face> faces) {
        BOOST_CHECK_EQUAL(faces.at(0).get_left_x(), 1);
        BOOST_CHECK_EQUAL(faces.at(0).get_left_y(), 2);   
        BOOST_CHECK_EQUAL(faces.at(0).get_right_x(), 3);
        BOOST_CHECK_EQUAL(faces.at(0).get_right_y(), 4);

    };

    rapp::cloud::vision_batch<rapp::cloud::face_detection,
                              rapp::cloud::qr_recognition> vb( pic,
                                                               rapp::cloud::face_detection(false, face_call),
                                                               rapp::cloud::qr_recognition(qr_call)
                                                              );    


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
                    "qr_detection" :   { "qr_centers":[{ 
                                                        "x": 1, 
                                                        "y": 2
                                                      }], 
                                         "qr_messages":["label"],
                                         "error" : ""
                                       }
              }])"_json;
    std::string j1_str = j1.dump(-1);
    vb.process(j1_str);

}

BOOST_AUTO_TEST_SUITE_END()
