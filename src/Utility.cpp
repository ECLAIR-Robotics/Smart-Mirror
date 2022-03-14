#include <stdio.h>
#include <raylib.h>
#include <string>
#include <json/json.h>
#include <curl/curl.h>
#include <thread>
using namespace std;

void http_request(bool* finished, string& url, Json::Value* storage) {
    *finished = false;

    // Perform HTTP Request using libcurl
    CURL *curl;
    CURLcode response;
    string resp_data;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, &url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp_data);
        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            // Request failed! :(
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        } else {
            // Convert the resulting output into a string

            Json::Reader reader;
            bool success = reader.parse(resp_data, *storage);

            if (!success) {
                fprintf(stderr, "JSON Parsing failed\n");
            }

        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    *finished = true;
}

void get_http_request(bool* finished, string& url, Json::Value* storage) {
    thread t(&http_request, finished, url, storage);
}