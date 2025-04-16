#pragma once

#include <boost/asio.hpp>

using io_context_t = boost::asio::io_context;
using acceptor_t = boost::asio::ip::tcp::acceptor;
using socket_t = boost::asio::ip::tcp::socket;
using endpoint_t = boost::asio::ip::tcp::endpoint;
using resolver_t = boost::asio::ip::tcp::resolver;
using error_code_t = boost::system::error_code;
using system_error_t = boost::system::system_error;
using buffer_t = boost::asio::buffer;