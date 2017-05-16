#include <mbgl/map/map.hpp>
#include "light.hpp"

namespace mbgl {
namespace android {

Light::Light(mbgl::Map& map, mbgl::style::Light& coreLight) : light(coreLight) , map(&map) {
}

jni::Class<Light> Light::javaClass;

jni::jobject* Light::createJavaPeer(jni::JNIEnv& env) {
    static auto constructor = Light::javaClass.template GetConstructor<jni::jlong>(env);
    return Light::javaClass.New(env, constructor, reinterpret_cast<jni::jlong>(this));
}

void Light::setColor(jni::JNIEnv&) {
    light.setColor(Color::red());
}

void Light::registerNative(jni::JNIEnv& env) {
    // Lookup the class
    Light::javaClass = *jni::Class<Light>::Find(env).NewGlobalRef(env).release();

#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)
    // Register the peer
    jni::RegisterNativePeer<Light>(env, Light::javaClass, "nativePtr",
                                   METHOD(&Light::setColor, "nativeSetColor")
    );
}

} // namespace android
} // namespace mb

