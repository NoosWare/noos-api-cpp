namespace noos {
namespace cloud {

template <class... cloud_pairs>
vision_batch<cloud_pairs...>::vision_batch(
                                         const noos::object::picture & image,
                                         cloud_pairs... args
                                       )
: http_request(cloud_base<bool>::make_http_uri("vision_batch")), 
  cloud_base<bool>(true),
  image__(image),
  batch__(std::make_tuple((args)...))
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image__.type();
    http_request::add_content("file", fname, image.bytearray());
    misc::for_each_arg([&](const auto & pair) {
        assert(!pair.first.is_single_callable());
        if (pair.first.is_single_callable()) {
            throw std::runtime_error("you can't use single callable objects in a vision batch");
        }
        static_assert(std::is_base_of<vision_base, decltype(pair.first)>::value,
                      "objects used in `vision_batch` must be derived from `vision_class`");
        this->add_content(pair.first.uri, pair.first.json, true);
    }, args...);
    http_request::close();
}

template <class... cloud_pairs>
void vision_batch<cloud_pairs...>::process(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json nlohmann_json;
    try {
        nlohmann_json = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    constexpr auto tuple_size = std::tuple_size<decltype(batch__)>::value;
    for (auto json_object : nlohmann_json) {
		for (json::iterator it = json_object.begin(); it != json_object.end(); ++it) {
            std::string json = it.value().dump(-1);
            expand_batch(json, 
                         it.key(), 
                         std::make_index_sequence<tuple_size>());
        }
    }
}

template<class... cloud_pairs>
template<std::size_t... batch_size>
void vision_batch<cloud_pairs...>::expand_batch(
                                                 std::string json, 
                                                 std::string key,
                                                 std::index_sequence<batch_size...>
                                               ) 
{
    find_cloud_type(std::get<batch_size>(batch__)..., json, key);
}

template <class... cloud_pairs>
void vision_batch<cloud_pairs...>::find_cloud_type(
                                                    cloud_pairs... args, 
                                                    std::string json, 
                                                    std::string key
                                                  )
{
    misc::for_each_arg([&](const auto & pair){
        auto first = std::get<0>(pair);
        if (first.uri == key) {
            auto second = std::get<1>(pair);
            second(deserialize<decltype(first), typename decltype(first)::data_type>()(json));
        }
    }, args...);
}
}
}