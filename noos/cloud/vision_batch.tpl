namespace noos {
namespace cloud {

template <class cloud_type>
tied<cloud_type>::tied(tied::callback functor)
: object(cloud_type()),
  functor(functor)
{}

template <class cloud_type>
tied<cloud_type> make_tie(typename cloud_type::callback functor)
{
    return tied<cloud_type>(functor);
}

template <class... ties>
vision_batch<ties...>::vision_batch(noos::object::picture image,
                                           ties... args)
: http_request(cloud_base<bool>::make_http_uri("vision_batch")), 
  cloud_base<bool>(true),
  image__(image),
  batch__(std::make_tuple((args)...))
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image__.type();
    http_request::add_content("file", fname, image.bytearray());
    misc::for_each_arg([&](const auto & pair) {
        assert(!pair.object.is_single_callable());
        if (pair.object.is_single_callable()) {
            throw std::runtime_error(
                    "single callable objects aren't allowed in a vision batch");
        }
        static_assert(std::is_base_of<vision_base, decltype(pair.object)>::value,
        "template types used in `vision_batch` must be derived from `vision_class`");
        this->add_content(pair.object.uri, pair.object.json, true);
    }, args...);
    http_request::close();
}

template <class... ties>
void vision_batch<ties...>::process(std::string json)
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
    if (nlohmann_json.is_array()) {
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
    else {
        misc::check_error(nlohmann_json);
    }
}

template<class... ties>
template<std::size_t... batch_size>
void vision_batch<ties...>::expand_batch(
                                                 std::string json, 
                                                 std::string key,
                                                 std::index_sequence<batch_size...>
                                               ) 
{
    find_cloud_type(std::get<batch_size>(batch__)..., json, key);
}

template <class... ties>
void vision_batch<ties...>::find_cloud_type(
                                                    ties... args, 
                                                    std::string json, 
                                                    std::string key
                                                  )
{
    misc::for_each_arg([&](const auto & pair){
        auto first = pair.object;
        if (first.uri == key) {
            pair.functor(deserialize<decltype(first), typename decltype(first)::data_type>()(json));
        }
    }, args...);
}
}
}
