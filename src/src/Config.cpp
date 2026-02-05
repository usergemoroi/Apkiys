#include "Config.h"

namespace Config {
    bool Save(const char* name) {
        return true;
    }

    bool Load(const char* name) {
        return true;
    }

    bool Delete(const char* name) {
        return true;
    }

    std::vector<ConfigEntry> GetConfigList() {
        static std::vector<ConfigEntry> configList;
        return configList;
    }

    bool ConfigExists(const char* name) {
        return false;
    }

    std::string GetConfigPath() {
        return "";
    }

    void SetConfigPath(const char* path) {
        // Stub implementation
    }

    void LoadDefault() {
        // Stub implementation
    }

    void SaveDefault() {
        // Stub implementation
    }
}