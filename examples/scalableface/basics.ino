#include <Arduino.h>
#include <Avatar.h>
#include <M5Unified.h>
#include <Properties.h>

using namespace m5avatar;

Avatar avatar;

int width;
int height;

class MyCustomFace : public Face {
 public:
  MyCustomFace()
      : Face(new Mouth(
                 (int)(((float)MOUTH_WIDTH_MIN / CORE_WIDTH) * height * 1.5),
                 (int)(((float)MOUTH_WIDTH_MAX / CORE_WIDTH) * height * 1.5),
                 (int)((float)MOUTH_HEIGHT_MIN / CORE_HEIGHT * height),
                 (int)((float)MOUTH_HEIGHT_MAX / CORE_HEIGHT * height)),
             new BoundingRect((int)((float)(height * MOUTH_TOP) / CORE_HEIGHT),
                              (int)(((float)(MOUTH_LEFT - (CORE_WIDTH / 2)) /
                                     (CORE_WIDTH / 2)) *
                                        (float)((float)height * 1.5 / 2) +
                                    (width / 2))),
             new Eye((int)((((float)EYE_DIAMETER) / CORE_HEIGHT) * height),
                     false),
             new BoundingRect((int)(height * EYE_R_TOP / CORE_HEIGHT),
                              (int)(((float)(EYE_R_LEFT - (CORE_WIDTH / 2)) /
                                     (CORE_WIDTH / 2)) *
                                        (float)((float)height * 1.5 / 2) +
                                    (width / 2))),
             new Eye((int)((((float)EYE_DIAMETER) / CORE_HEIGHT) * height),
                     true),
             new BoundingRect((int)(height * EYE_L_TOP / CORE_HEIGHT),
                              (int)(((float)(EYE_L_LEFT - (CORE_WIDTH / 2)) /
                                     (CORE_WIDTH / 2)) *
                                        (float)((float)height * 1.5 / 2) +
                                    (width / 2))),
             new Eyeblow(EYEBLOW_WIDTH, EYEBLOW_HEIGHT, false),
             new BoundingRect(EYE_R_TOP, EYEBLOW_R_LEFT),
             new Eyeblow(EYEBLOW_WIDTH, EYEBLOW_HEIGHT, true),
             new BoundingRect(EYE_L_TOP, EYEBLOW_L_LEFT)) {}
};

void setup() {
  M5.begin();
  Serial.begin(115200);
  // 画面を横長にするs
  width = M5.Display.width();
  height = M5.Display.height();
  Serial.printf("Display: %dx%d\n", width, height);
  if (width < height) {
    // rotate display if needed
    M5.Display.setRotation(1);
    width = M5.Display.width();
    height = M5.Display.height();
    Serial.printf("Display: %dx%d\n", width, height);
  }
  Serial.printf("MOUTHX=%d\n",
                (int)(((float)(MOUTH_LEFT - 160) / 160) * width + (width / 2)));

  Serial.printf(
      "MOUTH_LEFT=%d, width=%d, result=%d\n", MOUTH_LEFT, width,
      (int)(((float)(MOUTH_LEFT - 160) / 160) * (width / 2) + (width / 2)));
  avatar.setFace(new MyCustomFace());
  avatar.setPosition(0, 0);
  avatar.init();  // start drawing
}

void loop() {
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
