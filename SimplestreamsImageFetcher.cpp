#include "SimplestreamsImageFetcher.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <curl/curl.h>

constexpr const char* JSON_URL =
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

SimplestreamsImageFetcher::SimplestreamsImageFetcher() {
    fetch_data();
}

void SimplestreamsImageFetcher::fetch_data() {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    curl_easy_setopt(curl, CURLOPT_URL, JSON_URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("Failed to download JSON: " + std::string(curl_easy_strerror(res)));
    }

    json_data = nlohmann::json::parse(readBuffer);
}

std::vector<std::string> SimplestreamsImageFetcher::get_supported_releases() const {
    std::vector<std::string> releases;

    for (const auto& [path, item] : json_data["products"].items()) {
        if (item.contains("version") && item.contains("arch")) {
            std::string release = item["version"];
            std::string arch = item["arch"];
            if (!release.empty() && arch == "amd64") {
                releases.emplace_back(release);
            }
        }
    }

    return releases;
}



std::string SimplestreamsImageFetcher::get_current_lts() const {
    std::string lts_version;

    for (const auto& [path, item] : json_data["products"].items()) {
        if (item.contains("release_title") &&
            item["release_title"].get<std::string>().find("LTS") != std::string::npos) {
            std::string version = item["version"];
            if (version > lts_version) {
                lts_version = version;
            }
        }
    }

    return lts_version;
}


std::string SimplestreamsImageFetcher::get_sha256(const std::string& release) const {
    for (const auto& [product_key, product] : json_data["products"].items()) {
        if (product.contains("versions")) {
            for (const auto& [version_key, version_data] : product["versions"].items()) {
                if (version_data.contains("items")) {
                    for (const auto& [item_key, item_data] : version_data["items"].items()) {
                        if (item_data.contains("path") &&
                            item_data["path"].get<std::string>().find("disk1.img") != std::string::npos &&
                            item_data.contains("sha256")) {
                            return item_data["sha256"];
                        }
                    }
                }
            }
        }
        
    }

    throw std::runtime_error("SHA256 for disk1.img not found for release: " + release);
}

