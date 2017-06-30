#include "http_request.hpp"

namespace noos {
namespace cloud {

template <typename... Args>
void http_request::add_content(Args... args)
{
    post_->add_content(std::forward<Args>(args)...);
}

}
}
