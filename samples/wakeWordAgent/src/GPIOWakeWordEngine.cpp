#include "GPIOWakeWordEngine.h"
#include "Logger.h"
#include "WakeWordUtils.h"
#include "WakeWordException.h"

//#include <wiringPi.h>
//#include <gpio.h>
#include "libsoc_board.h"
#include "libsoc_gpio.h"
#include "gpio.h"
#include <unistd.h>

#define BUTTON "GPIO-A"

//#ifdef __cplusplus
//extern "C" {
//#endif
//  unsigned int gpio_id(const char *pin_name);
//  int digitalRead(unsigned int gpio_id);
//#ifdef __cplusplus
//}
//#endif


namespace AlexaWakeWord {

static const int GPIO_PIN = 2;
static const int MICROSECONDS_BETWEEN_READINGS = 1000;

GPIOWakeWordEngine::GPIOWakeWordEngine(WakeWordDetectedInterface* interface) :
    WakeWordEngine(interface), m_isRunning { false } {

  try {
    init();
  } catch (WakeWordException& e) {
    log(Logger::ERROR,
        std::string("GPIOWakeWordEngine: Initialization error:") + e.what());
    throw;
  }

}

void GPIOWakeWordEngine::pause() {

  log(Logger::INFO, "GPIOWakeWordEngine: handling pause");
}

void GPIOWakeWordEngine::resume() {

  log(Logger::INFO, "GPIOWakeWordEngine: handling resume");
}

void GPIOWakeWordEngine::init() {

  log(Logger::DEBUG, "GPIOWakeWordEngine: initializing");
  //if (wiringPiSetup() < 0) {
  //  std::string errorMsg = "Failed to initialize WiringPi library";
  //  throw WakeWordException(errorMsg);
  //}

  // INPUT is defined in "wiringPi.h"
  //pinMode(GPIO_PIN, INPUT);
  if (gpio_open(gpio_id(BUTTON), "in")){
    std::string errorMsg = "Failed to initialize WiringPi library";
    throw WakeWordException(errorMsg);
  }

  log(Logger::DEBUG, "Starting GPIO reading thread");
  m_isRunning = true;
  m_thread = make_unique<std::thread>(&GPIOWakeWordEngine::mainLoop, this);
}

void GPIOWakeWordEngine::mainLoop() {

  bool gpioReady { true };

  while (m_isRunning) {
    //int gpioValue = digitalRead(GPIO_PIN);
    int gpioValue = digitalRead(gpio_id(BUTTON));

    // HIGH and LOW are defined in "wiringPi.h"
    // The following detects the rising edge of GPIO input
    if (gpioReady && (gpioValue == HIGH)) {
      gpioReady = false;
      wakeWordDetected();
    } else if (!gpioReady && (gpioValue == LOW)) {
      gpioReady = true;
    }

    usleep(MICROSECONDS_BETWEEN_READINGS);
  }
}

} // namespace AlexaWakeWord
