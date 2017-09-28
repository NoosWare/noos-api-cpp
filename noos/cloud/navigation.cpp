#include "navigation.hpp"
namespace noos {
namespace cloud {

//service names
const std::string icp_slam::uri = "slam";
const std::string rbpf_slam::uri = "slam";
const std::string delete_map::uri = "delete_map";
const std::string upload_map::uri = "upload_map";
const std::string upload_slam_config_file::uri = "upload_slam_config_file";
const std::string get_map::uri = "get_map";

std::map<slam_type, std::string> 
      upload_slam_config_file::config_type {{slam_type::icp, "icp"},
                                            {slam_type::rbpf, "rbpf"},
                                            {slam_type::not_selected, "other"}};

//Class icp_slam 
icp_slam::icp_slam(const std::string map_name,
                   const std::string config_file_name,
                   const noos::object::laser laser_data)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = { {"map_name", map_name},
                                {"config_file", config_file_name},
                                {"laser", laser_data.to_json()}
                              };
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

//Class rbpf_slam 
rbpf_slam::rbpf_slam(const std::string map_name,
                     const std::string config_file_name,
                     const noos::object::laser laser_data,
                     const noos::object::odometry & odometry)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = { {"map_name", map_name},
                                {"config_file", config_file_name},
                                {"laser", laser_data.to_json()},
                                {"odometry", odometry.to_json()}
                              };
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

delete_map::delete_map(const std::string name)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"name", name}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

upload_map::upload_map(const std::string name,
                       const noos::object::picture & image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    if (image.type() != "png") {
        throw std::runtime_error("Only PNG images are allowed in this service");
    }
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"name", name}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}


upload_slam_config_file::upload_slam_config_file(noos::object::config_file & file,
                                                 std::string name,
                                                 slam_type type)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    if (config_type.find(type) == config_type.end()) {
        throw std::runtime_error("Incorrect slam type");
    }
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"file", file.get_data()},
                               {"config_name", name},
                               {"slam_type", config_type[type]}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

get_map::get_map(std::string map_name)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"map_name", map_name}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

}
}
