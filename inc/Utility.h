#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <raylib.h>
#include <string>
#include <json/json.h>
#include <curl/curl.h>
#include <string>
using namespace std;


/*
    In this function, a new thread is created to create a HTTP request to a given url.
    After the asynchronous call is made, a json storage value is populated with the
    information returned from the API. Then, finished is updated to be true right before
    the thread is complete.

    For proper use, use a default value until finished is updated to true.
*/
void get_http_request(bool* finished, string* url, Json::Value* storage);

#endif