package com.mapbox.mapboxsdk.testapp.style;

import android.graphics.Color;
import android.support.test.espresso.UiController;
import android.support.test.espresso.ViewAction;
import android.support.test.runner.AndroidJUnit4;
import android.view.View;

import com.mapbox.mapboxsdk.style.Light;
import com.mapbox.mapboxsdk.style.functions.Function;
import com.mapbox.mapboxsdk.style.functions.stops.IdentityStops;
import com.mapbox.mapboxsdk.style.layers.FillExtrusionLayer;
import com.mapbox.mapboxsdk.testapp.R;
import com.mapbox.mapboxsdk.testapp.activity.BaseActivityTest;
import com.mapbox.mapboxsdk.testapp.activity.style.FillExtrusionStyleTestActivity;

import junit.framework.Assert;

import org.hamcrest.Matcher;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.matcher.ViewMatchers.isDisplayed;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static com.mapbox.mapboxsdk.style.layers.Filter.eq;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.fillExtrusionBase;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.fillExtrusionColor;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.fillExtrusionHeight;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.fillExtrusionOpacity;

@RunWith(AndroidJUnit4.class)
public class LightTest extends BaseActivityTest {

  private Light light;

  @Test
  public void testGetLight() throws Exception {
    validateTestSetup();
    setupLayer();

    onView(withId(R.id.mapView)).perform(new ViewAction() {
      @Override
      public Matcher<View> getConstraints() {
        return isDisplayed();
      }

      @Override
      public String getDescription() {
        return getClass().getSimpleName();
      }

      @Override
      public void perform(UiController uiController, View view) {
        light = mapboxMap.getLight();
        light.setColor(Color.YELLOW);
        uiController.loopMainThreadForAtLeast(5000);
      }
    });

    Assert.assertNotNull(light);
  }

  private void setupLayer(){
    onView(withId(R.id.mapView)).perform(new ViewAction() {
      @Override
      public Matcher<View> getConstraints() {
        return isDisplayed();
      }

      @Override
      public String getDescription() {
        return getClass().getSimpleName();
      }

      @Override
      public void perform(UiController uiController, View view) {
        FillExtrusionLayer fillExtrusionLayer = new FillExtrusionLayer("3d-buildings", "composite");
        fillExtrusionLayer.setSourceLayer("building");
        fillExtrusionLayer.setFilter(eq("extrude", "true"));
        fillExtrusionLayer.setMinZoom(15);
        fillExtrusionLayer.setProperties(
          fillExtrusionColor(Color.LTGRAY),
          fillExtrusionHeight(Function.property("height", new IdentityStops<Float>())),
          fillExtrusionBase(Function.property("min_height", new IdentityStops<Float>())),
          fillExtrusionOpacity(0.6f)
        );
        mapboxMap.addLayer(fillExtrusionLayer);
        uiController.loopMainThreadForAtLeast(500);
      }
    });
  }

  @Override
  protected Class getActivityClass() {
    return FillExtrusionStyleTestActivity.class;
  }
}
