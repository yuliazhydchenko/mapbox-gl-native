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
import com.mapbox.mapboxsdk.style.layers.TransitionOptions;
import com.mapbox.mapboxsdk.testapp.R;
import com.mapbox.mapboxsdk.testapp.activity.BaseActivityTest;
import com.mapbox.mapboxsdk.testapp.activity.style.FillExtrusionStyleTestActivity;

import junit.framework.Assert;

import timber.log.Timber;

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

import static junit.framework.Assert.assertEquals;
import static junit.framework.Assert.assertNotNull;

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
       // light.setColor(Color.YELLOW);
        uiController.loopMainThreadForAtLeast(5000);
      }
    });

    Assert.assertNotNull(light);
  }


  @Test
  public void testSetAnchor() {
    validateTestSetup();
    setupLayer();
    Timber.i("anchor");
    assertNotNull(light);

    // Set and Get
    light.setAnchor(anchor(ANCHOR_MAP));
  }

  @Test
  public void testPositionTransition() {
    validateTestSetup();
    setupLayer();
    Timber.i("positionTransitionOptions");
    assertNotNull(light);

    // Set and Get
    TransitionOptions options = new TransitionOptions(300, 100);
    light.setPositionTransition(options);
  }

  @Test
  public void testSetPosition() {
    validateTestSetup();
    setupLayer();
    Timber.i("position");
    assertNotNull(light);

    // Set and Get
    light.setPosition(position(new Float[]{0f,0f,0f}));
  }

  @Test
  public void testColorTransition() {
    validateTestSetup();
    setupLayer();
    Timber.i("colorTransitionOptions");
    assertNotNull(light);

    // Set and Get
    TransitionOptions options = new TransitionOptions(300, 100);
    light.setColorTransition(options);
  }

  @Test
  public void testSetColor() {
    validateTestSetup();
    setupLayer();
    Timber.i("color");
    assertNotNull(light);

    // Set and Get
    light.setColor(color("rgba(0, 0, 0, 1)"));
  }

  @Test
  public void testIntensityTransition() {
    validateTestSetup();
    setupLayer();
    Timber.i("intensityTransitionOptions");
    assertNotNull(light);

    // Set and Get
    TransitionOptions options = new TransitionOptions(300, 100);
    light.setIntensityTransition(options);
  }

  @Test
  public void testSetIntensity() {
    validateTestSetup();
    setupLayer();
    Timber.i("intensity");
    assertNotNull(light);

    // Set and Get
    light.setIntensity(intensity(0.3f));
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
