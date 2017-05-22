// This file is generated. Edit android/platform/scripts/generate-style-code.js, then run `make android-style-code`.

package com.mapbox.mapboxsdk.style;

import android.support.annotation.UiThread;
import com.mapbox.mapboxsdk.style.layers.TransitionOptions;
import com.mapbox.mapboxsdk.style.layers.PropertyValue;

/**
 * 
 *
 * @see <a href="https://www.mapbox.com/mapbox-gl-style-spec/#light>">The online documentation</a>
 */
@UiThread
public class Light {

  private long nativePtr;

  /**
   * Creates a Light.
   *
   * @param nativePtr pointer used by core
   */
  public Light(long nativePtr) {
    this.nativePtr = nativePtr;
  }

  /**
   * Set the Anchor property.
   *
   * @param String value of anchor
   */
  public void setAnchor(String anchor) {
    nativeSetAnchor(new PropertyValue<>("anchor", anchor));
  }

  /**
   * Set the Position property.
   *
   * @param Float[] value of position
   */
  public void setPosition(Float[] position) {
    nativeSetPosition(new PropertyValue<>("position", position));
  }

  /**
   * Get the Position property transition options.
   *
   * @return transition options for Float[]
   */
  public TransitionOptions getPositionTransition() {
    return nativeGetPositionTransition();
  }

  /**
   * Set the Position property transition options.
   *
   * @param options transition options for Float[]
   */
  public void setPositionTransition(TransitionOptions options) {
    nativeSetPositionTransition(options.getDuration(), options.getDelay());
  }

  /**
   * Set the Color property.
   *
   * @param String value of color
   */
  public void setColor(String color) {
    nativeSetColor(new PropertyValue<>("color", color));
  }

  /**
   * Get the Color property transition options.
   *
   * @return transition options for String
   */
  public TransitionOptions getColorTransition() {
    return nativeGetColorTransition();
  }

  /**
   * Set the Color property transition options.
   *
   * @param options transition options for String
   */
  public void setColorTransition(TransitionOptions options) {
    nativeSetColorTransition(options.getDuration(), options.getDelay());
  }

  /**
   * Set the Intensity property.
   *
   * @param Float value of intensity
   */
  public void setIntensity(Float intensity) {
    nativeSetIntensity(new PropertyValue<>("intensity", intensity));
  }

  /**
   * Get the Intensity property transition options.
   *
   * @return transition options for Float
   */
  public TransitionOptions getIntensityTransition() {
    return nativeGetIntensityTransition();
  }

  /**
   * Set the Intensity property transition options.
   *
   * @param options transition options for Float
   */
  public void setIntensityTransition(TransitionOptions options) {
    nativeSetIntensityTransition(options.getDuration(), options.getDelay());
  }

  private native void nativeSetAnchor(PropertyValue<String> property);
  private native void nativeSetPosition(PropertyValue<Float[]> property);
  private native TransitionOptions nativeGetPositionTransition();
  private native void nativeSetPositionTransition(long duration, long delay);
  private native void nativeSetColor(PropertyValue<String> property);
  private native TransitionOptions nativeGetColorTransition();
  private native void nativeSetColorTransition(long duration, long delay);
  private native void nativeSetIntensity(PropertyValue<Float> property);
  private native TransitionOptions nativeGetIntensityTransition();
  private native void nativeSetIntensityTransition(long duration, long delay);
}