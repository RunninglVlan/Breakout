#include "Utility.h"

#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <format>
#include <string>
#include <vector>

#include "log.h"

#define CHECK_ERROR(e) case e: logError("GL Error: "#e); break;

bool Utility::checkAndLogGlError(bool alwaysLog) {
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) {
        if (alwaysLog) {
            logDebug("No GL error");
        }
        return true;
    } else {
        switch (error) {
            CHECK_ERROR(GL_INVALID_ENUM);
            CHECK_ERROR(GL_INVALID_VALUE);
            CHECK_ERROR(GL_INVALID_OPERATION);
            CHECK_ERROR(GL_INVALID_FRAMEBUFFER_OPERATION);
            CHECK_ERROR(GL_OUT_OF_MEMORY);
            default:
                logError(std::string("Unknown GL error: ") + (const char *) error);
        }
        return false;
    }
}

std::string Utility::loadStringFromAsset(AAssetManager *assetManager, const char *path) {
    std::string outString;
    AAsset *asset = AAssetManager_open(assetManager, path, AASSET_MODE_BUFFER);
    if (asset == nullptr) {
        logError(std::format("Failed to open asset: {}", path));
        assert(asset != nullptr);
    }
    auto length = AAsset_getLength(asset);
    std::vector<char> buffer(length);
    AAsset_read(asset, buffer.data(), length);
    outString.assign(buffer.begin(), buffer.end());
    AAsset_close(asset);
    return outString;
}
