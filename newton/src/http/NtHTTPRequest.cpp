// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <iostream>

void NtHTTPRequest::parseRequestLine()
{
    if (m_startLine == "")
        return;

    size_t pos = 0;
    std::string part = "";

    while (pos < m_startLine.size() && m_startLine[pos] != ' ')
        part += m_startLine[pos++];
    ++pos;

    if (part == "OPTIONS") {
        m_method = RequestMethod::OPTIONS;
    } else if (part == "GET") {
        m_method = RequestMethod::GET;
    } else if (part == "HEAD") {
        m_method = RequestMethod::HEAD;
    } else if (part == "POST") {
        m_method = RequestMethod::POST;
    } else if (part == "PUT") {
        m_method = RequestMethod::PUT;
    } else if (part == "DELETE") {
        m_method = RequestMethod::DELETE;
    } else if (part == "TRACE") {
        m_method = RequestMethod::TRACE;
    } else if (part == "CONNECT") {
        m_method = RequestMethod::CONNECT;
    } else {
        m_method = RequestMethod::UNKNOWN;
    }

    part = "";

    while (pos < m_startLine.size() && m_startLine[pos] != ' ')
        part += m_startLine[pos++];
    ++pos;

    m_requestURI = part;
    part = "";

    while (pos < m_startLine.size())
        part += m_startLine[pos++];

    if (part == "HTTP/0.9") {
        m_version = NtHTTPVersion::HTTP_0_9;
    } else if (part == "HTTP/1.0") {
        m_version = NtHTTPVersion::HTTP_1_0;
    } else if (part == "HTTP/1.1") {
        m_version = NtHTTPVersion::HTTP_1_1;
    } else if (part == "HTTP/2.0") {
        m_version = NtHTTPVersion::HTTP_2_0;
    } else if (part == "HTTP/3.0") {
        m_version = NtHTTPVersion::HTTP_3_0;
    } else {
        m_version = NtHTTPVersion::HTTP_VERSION_UNKNOWN;
    }
}

NtHTTPRequest* newton::NtParseHTTPRequest(char* buf, size_t len)
{
    size_t pos = 0;
    NtHTTPRequest* req = new NtHTTPRequest();
    std::string reqline = "";

    while (pos < len && buf[pos] != '\r') {
        reqline += buf[pos++];
    }
    pos += 2;

    req->setRequestLine(reqline);

    while (pos < len && buf[pos] != '\r') {
        std::string name = "";
        std::string value = "";

        while (pos < len && buf[pos] != ':')
            name += buf[pos++];

        ++pos;

        if (buf[pos] == ' ')
            ++pos;

        while (pos < len && buf[pos] != '\r')
            value += buf[pos++];

        pos += 2;

        NtHTTPHeader* hdr = new NtHTTPHeader(name, value);
        req->addHeader(hdr);
    }

    pos += 2;

    return req;
}
