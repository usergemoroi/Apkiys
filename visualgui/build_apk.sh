#!/bin/bash

# Build script for VisualGUI APK

set -e

echo "=================================="
echo "VisualGUI APK Builder"
echo "=================================="
echo ""

# Check for Android SDK
if [ -z "$ANDROID_SDK_ROOT" ] && [ -z "$ANDROID_HOME" ]; then
    echo "ERROR: ANDROID_SDK_ROOT or ANDROID_HOME environment variable is not set!"
    echo "Please set it to your Android SDK location."
    echo "Example: export ANDROID_SDK_ROOT=/home/user/Android/Sdk"
    exit 1
fi

SDK_ROOT="${ANDROID_SDK_ROOT:-$ANDROID_HOME}"
echo "Android SDK: $SDK_ROOT"

# Check for NDK
NDK_PATH="${SDK_ROOT}/ndk"
if [ ! -d "$NDK_PATH" ]; then
    echo "WARNING: NDK not found at $NDK_PATH"
    echo "Please install NDK through Android Studio SDK Manager"
fi

# Clean previous build
echo ""
echo "Step 1: Cleaning previous build..."
./gradlew clean

# Build debug APK
echo ""
echo "Step 2: Building Debug APK..."
./gradlew assembleDebug

# Build release APK
echo ""
echo "Step 3: Building Release APK..."
./gradlew assembleRelease

echo ""
echo "=================================="
echo "Build completed successfully!"
echo "=================================="
echo ""
echo "APK files:"
echo "  Debug:   app/build/outputs/apk/debug/app-debug.apk"
echo "  Release: app/build/outputs/apk/release/app-release-unsigned.apk"
echo ""
echo "To install on device:"
echo "  adb install -r app/build/outputs/apk/debug/app-debug.apk"
echo ""
