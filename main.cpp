#include "SimplestreamsImageFetcher.h"
#include <iostream>

#include <iostream>
#include <string>
#include <vector>

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [--list | --lts | --sha256 <release> | --help]\n";
    std::cout << "  --list               List supported Ubuntu releases with arch amd64\n";
    std::cout << "  --lts                Show current LTS Ubuntu version\n";
    std::cout << "  --sha256 <release>   Show SHA256 hash of 'disk1.img' for the specified release\n";
    std::cout << "  --help               Show this help message\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    try {
        SimplestreamsImageFetcher fetcher;
        std::string option = argv[1];

        if (option == "--list") {
            auto supported_releases = fetcher.get_supported_releases();
            std::cout << "Supported Ubuntu Releases with arch amd64:\n";
            for (const auto& version : supported_releases) {
                std::cout << "Version: " << version  << "\n";
            }
        }
        else if (option == "--lts") {
            std::cout << "Current LTS: " << fetcher.get_current_lts() << "\n";
        }
        else if (option == "--sha256") {
            if (argc < 3) {
                std::cerr << "Error: --sha256 requires a release name (e.g., jammy)\n";
                return 1;
            }
            std::string rel = argv[2];
            std::cout << "SHA256 for " << rel << ": " << fetcher.get_sha256(rel) << "\n";
        }
        else if (option == "--help") {
            print_usage(argv[0]);
        }
        else {
            std::cerr << "Unknown option: " << option << "\n";
            print_usage(argv[0]);
            return 1;
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}


// int main(int argc, char* argv[]) {
//     try {
//         SimplestreamsImageFetcher fetcher;

//         auto supported_releases = fetcher.get_supported_releases();
//         std::cout << "Supported Ubuntu Releases with arch amd64:\n";
//         for (const auto& version: supported_releases) {
//             std::cout << "Version: " << version<< "\n";
//         }

//         std::cout << "\nCurrent LTS: " << fetcher.get_current_lts() << "\n";

//         std::string rel = "jammy";
//         std::cout << "SHA256 for " << rel << ": " << fetcher.get_sha256(rel) << "\n";

//     } catch (const std::exception& ex) {
//         std::cerr << "Error: " << ex.what() << "\n";
//     }
// }
