#pragma once

#include <mbgl/map/map.hpp>
#include <mbgl/style/light.hpp>

#include "light.hpp"

#include <jni/jni.hpp>

namespace mbgl {
namespace android {

/**
 * Create a non-owning peer
 */
jni::jobject* createJavaLightPeer(jni::JNIEnv&, mbgl::Map&, mbgl::style::Light&);

/**
 * Create an owning peer
 */
jni::jobject* createJavaLightPeer(jni::JNIEnv&, mbgl::Map&, mbgl::style::Light&);

void registerNativeLights(jni::JNIEnv&);

}
}
