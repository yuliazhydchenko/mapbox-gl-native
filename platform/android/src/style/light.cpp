// This file is generated. Edit android/platform/scripts/generate-style-code.js, then run `make android-style-code`.

#include <mbgl/map/map.hpp>
#include "light.hpp"
#include "conversion/transition_options.hpp"

namespace mbgl {
namespace android {

Light::Light(mbgl::Map& map, mbgl::style::Light& coreLight) : light(coreLight) , map(&map) {
}

jni::Class<Light> Light::javaClass;

jni::jobject* Light::createJavaPeer(jni::JNIEnv& env) {
    static auto constructor = Light::javaClass.template GetConstructor<jni::jlong>(env);
    return Light::javaClass.New(env, constructor, reinterpret_cast<jni::jlong>(this));
}

void Light::setAnchor(jni::JNIEnv& env, PropertyValue<LightAnchorType> property) {
    light.setAnchor(property);
}

void Light::setPosition(jni::JNIEnv& env, PropertyValue<Position> property) {
    light.setPosition(property);
}

jni::Object<TransitionOptions> Light::getPositionTransition(jni::JNIEnv& env) {
   using namespace mbgl::android::conversion;
   mbgl::style::TransitionOptions options = light.getPositionTransition();
   return *convert<jni::Object<TransitionOptions>>(env, options);
}

void Light::setPositionTransition(jni::JNIEnv&, jlong duration, jlong delay) {
   mbgl::style::TransitionOptions options;
   options.duration.emplace(mbgl::Milliseconds(duration));
   options.delay.emplace(mbgl::Milliseconds(delay));
   light.setPositionTransition(options);
}

void Light::setColor(jni::JNIEnv& env, PropertyValue<Color> property) {
    light.setColor(property);
}

jni::Object<TransitionOptions> Light::getColorTransition(jni::JNIEnv& env) {
   using namespace mbgl::android::conversion;
   mbgl::style::TransitionOptions options = light.getColorTransition();
   return *convert<jni::Object<TransitionOptions>>(env, options);
}

void Light::setColorTransition(jni::JNIEnv&, jlong duration, jlong delay) {
   mbgl::style::TransitionOptions options;
   options.duration.emplace(mbgl::Milliseconds(duration));
   options.delay.emplace(mbgl::Milliseconds(delay));
   light.setColorTransition(options);
}

void Light::setIntensity(jni::JNIEnv& env, PropertyValue<float> property) {
    light.setIntensity(property);
}

jni::Object<TransitionOptions> Light::getIntensityTransition(jni::JNIEnv& env) {
   using namespace mbgl::android::conversion;
   mbgl::style::TransitionOptions options = light.getIntensityTransition();
   return *convert<jni::Object<TransitionOptions>>(env, options);
}

void Light::setIntensityTransition(jni::JNIEnv&, jlong duration, jlong delay) {
   mbgl::style::TransitionOptions options;
   options.duration.emplace(mbgl::Milliseconds(duration));
   options.delay.emplace(mbgl::Milliseconds(delay));
   light.setIntensityTransition(options);
}

void Light::registerNative(jni::JNIEnv& env) {
    // Lookup the class
    Light::javaClass = *jni::Class<Light>::Find(env).NewGlobalRef(env).release();

#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)
    // Register the peer
    jni::RegisterNativePeer<Light>(env, Light::javaClass, "nativePtr",
    METHOD(&Light::setAnchor, "nativeSetAnchor"),
    METHOD(&Light::getPositionTransition, "nativeGetPositionTransition"),
    METHOD(&Light::setPositionTransition, "nativeSetPositionTransition"),
    METHOD(&Light::setPosition, "nativeSetPosition"),
    METHOD(&Light::getColorTransition, "nativeGetColorTransition"),
    METHOD(&Light::setColorTransition, "nativeSetColorTransition"),
    METHOD(&Light::setColor, "nativeSetColor"),
    METHOD(&Light::getIntensityTransition, "nativeGetIntensityTransition"),
    METHOD(&Light::setIntensityTransition, "nativeSetIntensityTransition"),
    METHOD(&Light::setIntensity, "nativeSetIntensity"));
}

} // namespace android
} // namespace mb
