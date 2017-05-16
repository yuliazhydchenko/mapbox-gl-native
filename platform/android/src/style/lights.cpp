#include "lights.hpp"

namespace mbgl {
namespace android {

static Light* initializeLightPeer(mbgl::Map& map, mbgl::style::Light& coreLight) {
    return new Light(map, coreLight);
}

//template <class LayerType, class PeerType>
//static PeerType* createPeer(Map& map, std::unique_ptr<mbgl::style::Light> light) {
//    return new PeerType(map, std::move(std::unique_ptr<LayerType>(light.release()->as<LayerType>())));
//}
//
//static Light* initializeLightPeer(Map& map, std::unique_ptr<mbgl::style::Light> coreLight) {
//    return createPeer(map, coreLight);
//}

jni::jobject* createJavaLightPeer(jni::JNIEnv& env, Map& map, mbgl::style::Light& coreLight) {
    std::unique_ptr<Light> peerLight = std::unique_ptr<Light>(initializeLightPeer(map, coreLight));
    jni::jobject* result = peerLight->createJavaPeer(env);
    peerLight.release();
    return result;
}

void registerNativeLights(jni::JNIEnv& env) {
    Light::registerNative(env);
}

} // namespace android
} // namespace mbgl