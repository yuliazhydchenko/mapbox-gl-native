#pragma once

#include <mbgl/util/noncopyable.hpp>

#include <jni/jni.hpp>
#include <mbgl/style/light.hpp>

namespace mbgl {
namespace android {

class Light : private mbgl::util::noncopyable {
public:

    static constexpr auto Name() { return "com/mapbox/mapboxsdk/style/Light"; };

    static jni::Class<Light> javaClass;

    static void registerNative(jni::JNIEnv&);

    /*
     * Called when a Java object is created on the c++ side
     */
    Light(mbgl::Map&, mbgl::style::Light&);

    jni::jobject* createJavaPeer(jni::JNIEnv&);

    void setColor(jni::JNIEnv&);

protected:

    // Raw reference to the light
    mbgl::style::Light& light;

    // Map is set when the light is retrieved
    mbgl::Map* map;
};
} // namespace android
} // namespace mbgl