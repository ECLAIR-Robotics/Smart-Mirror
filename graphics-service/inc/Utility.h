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
    Example usage:

        Json::Value data(new Json::Value());
        bool finished = false;

        get_http_request(&finished, "http://date.jsontest.com", &data);

*/
void get_http_request(bool* finished, const string url, Json::Value* storage);

void draw_loading_wheel(uint32_t r1, uint32_t r2, uint32_t x, uint32_t y);

#endif