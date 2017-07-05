#ifndef NOOS_NODE_CONNECTION
#define NOOS_NODE_CONNECTION
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include "noos/cloud/asio/platform.hpp"
namespace noos {
namespace cloud {
/**
 *  @brief default platform where to connect
 *  @version 0.7.3
 *  @date 05.07.2017
 */
const platform default_node = {"10.130.3.17", "8080", "mysecret", "alex"};

/**
 *  @brief european platform
 *  @version 0.7.3
 *  @date 05.07.2017
 */
const platform eu_node = {"10.130.3.17", "8080", "mysecret", "alex"};

/**
 * TODO: Add nodes depending the continent
 */
}
}

#endif
