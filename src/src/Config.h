#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

struct ConfigEntry {
    std::string name;
    std::string creator;
    std::string date;
    std::string path;
};

namespace Config {
    // Save/Load
    bool Save(const char* name);
    bool Load(const char* name);
    bool Delete(const char* name);
    
    // Config management
    std::vector<ConfigEntry> GetConfigList();
    bool ConfigExists(const char* name);
    
    // Path management
    std::string GetConfigPath();
    void SetConfigPath(const char* path);
    
    // Default config
    void LoadDefault();
    void SaveDefault();
}

#endif // CONFIG_H
