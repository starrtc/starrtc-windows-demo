#ifndef __LIBCURL_H__
#define __LIBCURL_H__
 
#include <string>

int libcurl_get(const char* url, std::string& buffer, std::string& errinfo);
int libcurl_post(const char* url, const char* data, std::string& buffer, std::string& errinfo);

#endif
