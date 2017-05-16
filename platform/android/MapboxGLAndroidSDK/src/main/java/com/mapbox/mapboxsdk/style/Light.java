// This file is generated. Edit android/platform/scripts/generate-style-code.js, then run `make android-style-code`.

package com.mapbox.mapboxsdk.style;

import android.support.annotation.UiThread;

/**
 * 
 *
 * @see <a href="https://www.mapbox.com/mapbox-gl-style-spec/#layers-">The online documentation</a>
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


  public void setColor(int color){
    nativeSetColor();
  }

  protected native void nativeSetColor();
}