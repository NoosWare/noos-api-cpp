#include "http_request.hpp"
namespace noos {
namespace cloud {

http_request::http_request(const std::string uri)
{
    if (uri.empty()) {
        throw std::runtime_error("empty uri param");
    }
    header_ = std::make_shared<noos::cloud::http_header>(uri);
    post_   = std::make_shared<noos::cloud::http_post>(header_->get_boundary());
    assert(header_ && post_);
}

http_request::http_request(const std::string uri,
                           bool keep_alive)
{
    if (uri.empty()) {
        throw std::runtime_error("empty uri param");
    }
    header_ = std::make_shared<noos::cloud::http_header>(uri, keep_alive);
    post_   = std::make_shared<noos::cloud::http_post>(header_->get_boundary());
    assert(header_ && post_);
}

http_request::http_request(const http_request & arg)
{
    this->header_ = arg.header_;
    this->post_   = arg.post_;
}

void http_request::fill_buffer(
                                boost::asio::streambuf & buffer,
                                noos::cloud::platform info
                              ) 
{
	std::ostream http_request_stream(&buffer);
	http_request_stream << header_->to_string(info, post_->size());
    if (post_->size() > 0) {
        http_request_stream << post_->to_string();
    }
}

void http_request::close()
{
    assert(post_);
    post_->end();
}

std::string http_request::to_string(noos::cloud::platform info) const
{
    assert(header_ && post_);
    if (post_->size() > 0) {
        return header_->to_string(info, post_->size()) + post_->to_string();
    }
    else {
        return header_->to_string(info, 0);
    }
}

std::string http_request::to_post() const
{
    assert(post_);
    return post_->to_string();
}

bool http_request::operator==(const http_request & rhs) const
{
    assert(header_ && post_);
    return (this->header_ == rhs.header_) && (this->post_ == rhs.post_);
}

void http_request::make_multipart_form()
{
    assert(header_);
    this->header_->make_multipart_form();
}

}
}
