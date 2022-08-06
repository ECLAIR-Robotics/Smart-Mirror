#include <stdio.h>
#include <string>
#include <json/json.h>
#include <curl/curl.h>
#include <thread>
#include <iostream>
#include <raylib.h>
#include "Constants.h"
using namespace std;

size_t size_of_data(void *ptr, size_t size, size_t nmemb, std::string *s) {
    s->append(static_cast<char *>(ptr), size*nmemb);
    return size*nmemb;
}

void http_request(bool* finished, const string url, Json::Value* storage) {
    *finished = false;

    // Used for tests
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // Perform HTTP Request using libcurl
    CURL* curl;
    CURLcode response;
    string resp_data;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        cout << "Request at: " << url << "\n";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, size_of_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp_data);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        response = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if (response != CURLE_OK) {
            // Request failed! :(
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        } else {
            // Convert the resulting output string into an easy-to-use json
            Json::CharReaderBuilder jsonBuilder;
            Json::CharReader* JsonReader(jsonBuilder.newCharReader());
            bool success = JsonReader->parse(resp_data.c_str(), resp_data.c_str() + resp_data.size(), storage, nullptr);

            if (!success) {
                fprintf(stderr, "JSON Parsing failed\n");
            }
        }
    }

    curl_global_cleanup();

    *finished = true;
}

void get_http_request(bool* finished, const string url, Json::Value* storage) {
    thread t(&http_request, finished, url, storage);
    t.detach();
}


void draw_loading_wheel(uint32_t x, uint32_t y, uint32_t r) {

    DrawCircleSectorLines(
        Vector2{x, y}, r, 0.0, 0.5, 1, MAIN_COLOR
    )
}
