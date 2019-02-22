#ifndef __LIBCURL_H__
#define __LIBCURL_H__
 
#include <string>
#include <iostream>
#include "curl/curl.h"
 
 
static char error_buffer[CURL_ERROR_SIZE];
static int writer(char*, size_t, size_t, std::string*);
static bool init(CURL*&, const char*, std::string*);
 
 
static bool init(CURL*& conn, const char* url, std::string* p_buffer)
{
	CURLcode code;
 
	conn = curl_easy_init();
	if (NULL == conn)
	{
		std::cout << stderr <<  " Failed to create CURL connection" << std::endl;
		exit(EXIT_FAILURE);
	}
 
	code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set error buffer " << code << std::endl;
		return false;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_URL, url);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set URL " << error_buffer << std::endl;
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_SSL_VERIFYPEER ,false);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set CURLOPT_SSL_VERIFYPEER " << error_buffer << std::endl;
		return false;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set redirect option " << error_buffer << std::endl;
		return false;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set writer " << error_buffer << std::endl;
		return false;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, p_buffer);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set write data " << error_buffer << std::endl;
		return false;
	}
 
	return true;
}
 
static int writer(char* data, size_t size, size_t nmemb, std::string* writer_data)
{
	unsigned long sizes = size * nmemb;
 
	if (NULL == writer_data)
	{
		return 0;
	}
 
	writer_data->append(data, sizes);
	
	return sizes;
}
 
 
 
int libcurl_get(const char* url, std::string& buffer, std::string& errinfo)
{
 
	CURL *conn = NULL;
	CURLcode code;
 
	curl_global_init(CURL_GLOBAL_DEFAULT);
 
	if (!init(conn, url, &buffer))
	{
		std::cout << stderr << " Connection initializion failed" << std::endl;
		errinfo = "Connection initializion failed\n";
 
		return -1;
	}
 
	code = curl_easy_perform(conn);
 
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to get" << url  << error_buffer << std::endl;
		
		errinfo.append("Failed to get ");
		errinfo.append(url);
 
		return -2;
	}
 
	curl_easy_cleanup(conn);
	
	return 1;
}
 
 
 
int libcurl_post(const char* url, const char* data, std::string& buffer, std::string& errinfo)
{
	CURL *conn = NULL;
	CURLcode code;
 
	curl_global_init(CURL_GLOBAL_DEFAULT);
 
	if (!init(conn, url, &buffer))
	{
		std::cout << stderr << " Connection initializion failed" << std::endl;
		
		errinfo = "Connection initializion failed\n";
 
		return -1;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_POST, true);
 
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set CURLOPT_POST " << error_buffer << std::endl;
		return -1;
	}
 
	code = curl_easy_setopt(conn, CURLOPT_POSTFIELDS, data);
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to set CURLOPT_POSTFIELDS " << error_buffer << std::endl;
		return -1;
	}
 
	code = curl_easy_perform(conn);
 
	if (code != CURLE_OK)
	{
		std::cout << stderr << " Failed to post " << url << error_buffer << std::endl;
 
		errinfo.append("Failed to post ");
		errinfo.append(url);
 
		return -2;
	}
 
	curl_easy_cleanup(conn);
	
	return 1;
}
 
#endif
