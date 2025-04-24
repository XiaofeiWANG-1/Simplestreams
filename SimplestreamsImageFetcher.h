#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

class UbuntuImageFetcher {
public:
    virtual std::vector<std::string> get_supported_releases() const = 0;
    virtual std::string get_current_lts() const = 0;
    virtual std::string get_sha256(const std::string& release) const = 0;
    virtual ~UbuntuImageFetcher() = default;
};

class SimplestreamsImageFetcher : public UbuntuImageFetcher {
public:
    SimplestreamsImageFetcher();  // fetches and parses the JSON

    std::vector<std::string> get_supported_releases() const override;

    std::string get_current_lts() const override;
    std::string get_sha256(const std::string& release) const override;

private:
    nlohmann::json json_data;
    void fetch_data();
};
