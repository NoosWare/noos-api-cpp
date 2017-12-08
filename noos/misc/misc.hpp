#ifndef NOOS_MISC
#define NOOS_MISC
#include "includes.ihh"
namespace noos {
/**
 * @brief common misc helper functions
 * @version 0.7.3
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @date 10 June 2017
 */
namespace misc {

/// @brief decode base64
/// @param val must be encoded using base64
inline std::string decode64(const std::string &val)
{
	if (val.empty()) {
		throw std::runtime_error("empty string param");
	}
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), 
                                                            It(std::end(val))), 
                                                            [](char c) {return c == '\0';});
}

/// @brief encode base64
/// @param val must be plain-text string
/// @return a base64 encoded string
inline std::string encode64(const std::string &val)
{
	if (val.empty()) {
		throw std::runtime_error("empty string param");
	}
    using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
    return tmp.append((3 - val.size() % 3) % 3, '=');
}

/// @brief Create a random boundary for the multipart/form in HTTP
inline std::string random_boundary()
{
    std::string chars("abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "1234567890");
    std::random_device rng;
    std::mt19937 gen(rng());
    std::string uid;

    // Randomly chose 16 characters
    std::uniform_int_distribution<> index_dist(0, (chars.size() - 1));
    for (int i = 0; i < 16; ++i){
        uid.push_back(chars[index_dist(rng)]);
    }
    return uid;
}

/// @brief escape JSON strings when sending them over the socket
/// @param str will be escaped and returned
inline std::string escape_string(const std::string & str)
{
	if (str.empty()) {
		throw std::runtime_error("empty string param");
	}
    std::ostringstream ss;
    for (auto iter = str.cbegin(); iter != str.cend(); iter++) {
        switch (*iter) {
            case '\\': ss << "\\\\"; break;
            case '"': ss << "\\\""; break;
            case '/': ss << "\\/"; break;
            case '\b': ss << "\\b"; break;
            case '\f': ss << "\\f"; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default: ss << *iter; break;
        }
    }
    return ss.str();
} 

/**
 * @brief expand variadic arguments using a fold expression
 * @param f of template parameter F is the function (a lambda) receiving the expanded object
 * @param args is the variadic list of args
 */
template <class F, class... Args>
void for_each_arg(F&& f, Args&&... args) 
{
    using swallow = int[];
    (void)swallow{0, (void(f(std::forward<Args>(args))), 0)...};
}

/**
 * @brief method to check if the string exists in the actual json
 */
template<typename T>
T get_json_value(const std::string key, const nlohmann::json & json_f)
{
    auto it = json_f.find(key);
    if (it == json_f.end()) {
        throw std::runtime_error("key " + key + " not found");    
    }
    return it->get<T>();
}

/// \brief method to check if JSON data is correct
inline bool check_json(
                         nlohmann::json & json,
                         const std::string json_str
                      )
{
    try {
        json = nlohmann::json::parse(json_str);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
} 

/// \brief function to check if an error has been received from
//         the platform
inline bool check_error(
                         const nlohmann::json json,
                         const std::string error_str = "error"
                       )
{
    auto error = misc::get_json_value<std::string>(error_str, json);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
        return false;
    }
    return true;
}

/// @brief take decoded data and save it into an image
/// @param std::string data is the image data before decoding
/// @param filename is path where to save the image
inline bool save_dec_image(std::string data,
                           std::string filename)
{
    std::string temporary = "tmp";
    std::ofstream tmp(temporary);
    tmp << misc::decode64(data);
    tmp.close();
    noos::object::picture result(temporary);
    std::remove(temporary.c_str());
    return result.save(filename);
}

}
}

// c++11 - add `std::make_unique`
#if __cplusplus==201103L
namespace std {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif

//
#endif
