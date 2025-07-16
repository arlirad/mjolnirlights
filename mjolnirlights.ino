#include <Adafruit_NeoPixel.h>

constexpr auto BUTTON_PIN = 11;
constexpr auto LED_TORSO_FRONT_LEFT = 2; // responsible for the left arm too
constexpr auto LED_TORSO_RIGHT_BACK = 3;
constexpr auto LED_ARM_RIGHT = 4;
constexpr auto LED_THIGH_LEFT = 5;
constexpr auto LED_THIGH_RIGHT = 6;

enum emitter_id {
  EM_TORSO_FL, // torso, front left
  EM_TORSO_FM, // torso, front middle
  EM_TORSO_FR, // torso, front right
  EM_TORSO_BL, // torso, back left
  EM_TORSO_BM, // torso, back middle
  EM_TORSO_BR, // torso, back right
  EM_TORSO_AL, // arm left
  EM_TORSO_AR, // arm right
  EM_TORSO_TL, // thigh left
  EM_TORSO_TR, // thigh right
};

class emitter {
  public:
  emitter() {}

  emitter(Adafruit_NeoPixel& pixels, int offset, int count, bool reverse) : _pixels(pixels) {
    this->_offset = offset;
    this->_count = count;
    this->_reverse = reverse;
  }

  void setColorRGB(int r, int g, int b) {
    for (int i = 0; i < this->_count; i++)
      setPixelColorRGBInternal(i, r, g, b);
  }

  void setColorHSV(uint16_t h, uint8_t s, uint8_t v) {
    for (int i = 0; i < this->_count; i++)
      setPixelColorHSVInternal(i, h, s, v);
  }

  void setPixelColor(int index, int r, int g, int b) {
    if (this->_reverse)
      index = (this->_count - 1) - index;

    setPixelColorRGBInternal(index, r, g, b);
  }

  private:
  Adafruit_NeoPixel& _pixels;
  int _offset;
  int _count;
  bool _reverse;

  constexpr void setPixelColorRGBInternal(int index, int r, int g, int b) {
    _pixels.setPixelColor(index + _offset, _pixels.Color(r, g / 2, b));
  }

  constexpr void setPixelColorHSVInternal(int index, uint16_t h, uint8_t s, uint8_t v) {
    _pixels.setPixelColor(index + _offset, _pixels.ColorHSV(h, s, v));
  }
};

Adafruit_NeoPixel pixels[] = {
  Adafruit_NeoPixel(6, LED_TORSO_FRONT_LEFT, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(7, LED_TORSO_RIGHT_BACK, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(1, LED_ARM_RIGHT, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(2, LED_THIGH_LEFT, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(2, LED_THIGH_RIGHT, NEO_GRB + NEO_KHZ800),
};

// convention is left to right from the front, top to bottom
emitter emitters[] = {
  emitter(pixels[0], 2, 3, true), // EM_TORSO_FL
  emitter(pixels[0], 0, 2, false), // EM_TORSO_FM
  emitter(pixels[1], 0, 3, true), // EM_TORSO_FR
  emitter(pixels[1], 6, 1, false), // EM_TORSO_BL
  emitter(pixels[1], 4, 2, true), // EM_TORSO_BM
  emitter(pixels[1], 3, 1, false), // EM_TORSO_BR
  emitter(pixels[0], 5, 1, false), // EM_TORSO_AL
  emitter(pixels[2], 0, 1, false), // EM_TORSO_AR
  emitter(pixels[3], 0, 2, false), // EM_TORSO_TL
  emitter(pixels[4], 0, 2, false), // EM_TORSO_TR
};

int current_mode = 0;
void (*modes[])(uint64_t msecs) = {
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    for (auto& emitter : emitters)
      emitter.setColorRGB(205 + strober, 205 + strober, 0);
  },
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    for (auto& emitter : emitters)
      emitter.setColorRGB(205 + strober, (205 + strober) / 2, 0);
  },
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    for (auto& emitter : emitters)
      emitter.setColorRGB(205 + strober, 205 + strober, 205 + strober);
  },
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    for (auto& emitter : emitters)
      emitter.setColorRGB(0, (205 + strober) / 4, 205 + strober);
  },
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    for (auto& emitter : emitters)
      emitter.setColorHSV((msecs * 11) % 65536, 255, 255);
  },
  [](uint64_t msecs) {
    int cycler = msecs % 1000;

    emitters[EM_TORSO_FL].setColorRGB(255, 0, 0);
    emitters[EM_TORSO_FM].setColorRGB(255, 255, 255);
    emitters[EM_TORSO_FR].setColorRGB(0, 255, 0);
    emitters[EM_TORSO_BL].setColorRGB(192, 192, 192);
    emitters[EM_TORSO_BM].setColorRGB(127, 127, 127);
    emitters[EM_TORSO_BR].setColorRGB(192, 192, 192);
    emitters[EM_TORSO_AL].setColorRGB(255, 0, 0);
    emitters[EM_TORSO_AR].setColorRGB(0, 255, 0);
    emitters[EM_TORSO_TL].setColorRGB(255, 0, 0);
    emitters[EM_TORSO_TR].setColorRGB(0, 255, 0);

    if (cycler < 50 || (cycler >= 200 && cycler < 250)) {
      emitters[EM_TORSO_AL].setColorRGB(255, 255, 255);
      emitters[EM_TORSO_AR].setColorRGB(255, 255, 255);
    }

    if (cycler >= 100 && cycler < 150)
      emitters[EM_TORSO_BM].setColorRGB(255, 255, 255);
  },
  [](uint64_t msecs) {
    int strober = 40 * sin((((float) msecs) / 1000) * M_PI);

    emitters[EM_TORSO_FL].setColorRGB(205 + strober, (205 + strober) / 2, 0);
    emitters[EM_TORSO_FM].setColorRGB(205 + strober, 205 + strober, 205 + strober);
    emitters[EM_TORSO_FR].setColorRGB(205 + strober, (205 + strober) / 2, 0);
    emitters[EM_TORSO_BL].setColorRGB(205 + strober, 0, 0);
    emitters[EM_TORSO_BM].setColorRGB(205 + strober, 0, 0);
    emitters[EM_TORSO_BR].setColorRGB(205 + strober, 0, 0);
    emitters[EM_TORSO_AL].setColorRGB(205 + strober, (205 + strober) / 2, 0);
    emitters[EM_TORSO_AR].setColorRGB(205 + strober, (205 + strober) / 2, 0);
    emitters[EM_TORSO_TL].setColorRGB(205 + strober, (205 + strober) / 2, 0);
    emitters[EM_TORSO_TR].setColorRGB(205 + strober, (205 + strober) / 2, 0);
  },
  nullptr,
};

void setup() {
  Serial.begin(9600);
  Serial.println("mjolnrer");

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (auto& pixel : pixels) {
    pixel.begin();
    pixel.clear();
  }
}

void loop() {
  mode_toggle();
  modes[current_mode](millis());

  for (auto& pixel : pixels)
    pixel.show();

  delay(10);
}

void mode_toggle() {
  static int debounce = 0;
  static bool triggered = false;
  bool pressed = !digitalRead(BUTTON_PIN);

  debounce = max(min(debounce + (pressed ? 1 : -1), 6), 0);

  if (debounce == 0)
    triggered = false;

  if (debounce == 6 && !triggered) {
    triggered = true;
    current_mode++;

    if (!modes[current_mode])
      current_mode = 0;
  }
}