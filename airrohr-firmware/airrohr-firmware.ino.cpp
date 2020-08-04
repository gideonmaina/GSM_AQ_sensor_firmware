# 1 "c:\\users\\jacka\\appdata\\local\\temp\\tmpdxn6s7"
#include <Arduino.h>
# 1 "F:/EMBEDDED SOFTWARE/CFA/sensors.AFRICA-AQ-sensors-software/airrohr-firmware/airrohr-firmware.ino"
# 59 "F:/EMBEDDED SOFTWARE/CFA/sensors.AFRICA-AQ-sensors-software/airrohr-firmware/airrohr-firmware.ino"
#include <WString.h>
#include <pgmspace.h>


#define SOFTWARE_VERSION_STR "NRZ-2020-129"
String SOFTWARE_VERSION(SOFTWARE_VERSION_STR);





#if defined(ESP8266)
#include <FS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <Hash.h>
#include <ctime>
#include <coredecls.h>
#include <sntp.h>
#endif

#if defined(ESP32)
#define FORMAT_SPIFFS_IF_FAILED true
#include <FS.h>
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HardwareSerial.h>
#include <hwcrypto/sha.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#endif


#include "./oledfont.h"
#include <SSD1306.h>
#include <SH1106.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include "./DHT.h"
#include <PCF8575.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_SHT31.h>
#include <StreamString.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>
#include "./bmx280_i2c.h"
#include "./sps30_i2c.h"
#include "./dnms_i2c.h"
#include "./SPH0645.h"

#if defined(INTL_BG)
#include "intl_bg.h"
#elif defined(INTL_CZ)
#include "intl_cz.h"
#elif defined(INTL_DE)
#include "intl_de.h"
#elif defined(INTL_DK)
#include "intl_dk.h"
#elif defined(INTL_EN)
#include "intl_en.h"
#elif defined(INTL_ES)
#include "intl_es.h"
#elif defined(INTL_FR)
#include "intl_fr.h"
#elif defined(INTL_IT)
#include "intl_it.h"
#elif defined(INTL_LU)
#include "intl_lu.h"
#elif defined(INTL_NL)
#include "intl_nl.h"
#elif defined(INTL_PL)
#include "intl_pl.h"
#elif defined(INTL_PT)
#include "intl_pt.h"
#elif defined(INTL_RS)
#include "intl_rs.h"
#elif defined(INTL_RU)
#include "intl_ru.h"
#elif defined(INTL_SE)
#include "intl_se.h"
#elif defined(INTL_TR)
#include "intl_tr.h"
#elif defined(INTL_UA)
#include "intl_ua.h"
#else
#warning No language defined
#include "intl_en.h"
#endif

#include "defines.h"
#include "ext_def.h"
#include "html-content.h"
#include "ca-root.h"




constexpr unsigned SMALL_STR = 64-1;
constexpr unsigned MED_STR = 256-1;
constexpr unsigned LARGE_STR = 512-1;
constexpr unsigned XLARGE_STR = 1024-1;

#define RESERVE_STRING(name,size) String name((const char*)nullptr); name.reserve(size)

const unsigned long SAMPLETIME_MS = 30000;
const unsigned long SAMPLETIME_SDS_MS = 1000;
const unsigned long WARMUPTIME_SDS_MS = 15000;
const unsigned long READINGTIME_SDS_MS = 5000;
const unsigned long SAMPLETIME_GPS_MS = 50;
const unsigned long DISPLAY_UPDATE_INTERVAL_MS = 5000;
const unsigned long ONE_DAY_IN_MS = 24 * 60 * 60 * 1000;
const unsigned long PAUSE_BETWEEN_UPDATE_ATTEMPTS_MS = ONE_DAY_IN_MS;
const unsigned long DURATION_BEFORE_FORCED_RESTART_MS = ONE_DAY_IN_MS * 28;
# 193 "F:/EMBEDDED SOFTWARE/CFA/sensors.AFRICA-AQ-sensors-software/airrohr-firmware/airrohr-firmware.ino"
namespace cfg {
 unsigned debug = DEBUG;

 unsigned time_for_wifi_config = 600000;
 unsigned sending_intervall_ms = 145000;

 char current_lang[3];


 bool www_basicauth_enabled = WWW_BASICAUTH_ENABLED;
 char www_username[LEN_WWW_USERNAME];
 char www_password[LEN_CFG_PASSWORD];


 char wlanssid[LEN_WLANSSID];
 char wlanpwd[LEN_CFG_PASSWORD];


 char fs_ssid[LEN_FS_SSID] = FS_SSID;
 char fs_pwd[LEN_CFG_PASSWORD] = FS_PWD;


 bool sph0645_read = SPHO645_READ;
 bool dht_read = DHT_READ;
 bool htu21d_read = HTU21D_READ;
 bool ppd_read = PPD_READ;
 bool sds_read = SDS_READ;
 bool pms_read = PMS_READ;
 bool hpm_read = HPM_READ;
 bool sps30_read = SPS30_READ;
 bool bmp_read = BMP_READ;
 bool bmx280_read = BMX280_READ;
 bool sht3x_read = SHT3X_READ;
 bool ds18b20_read = DS18B20_READ;
 bool dnms_read = DNMS_READ;
 char dnms_correction[LEN_DNMS_CORRECTION] = DNMS_CORRECTION;
 bool gps_read = GPS_READ;
 bool rtc_read = RTC_READ;
 bool sd_read = SD_READ;


 bool send2cfa = SEND2CFA;
 bool send2dusti = SEND2SENSORCOMMUNITY;
 bool send2madavi = SEND2MADAVI;
 bool send2sensemap = SEND2SENSEMAP;
 bool send2fsapp = SEND2FSAPP;
 bool send2aircms = SEND2AIRCMS;
 bool send2custom = SEND2CUSTOM;
 bool send2influx = SEND2INFLUX;
 bool send2csv = SEND2CSV;
 bool send2sd = SEND2SD;

 bool auto_update = AUTO_UPDATE;
 bool use_beta = USE_BETA;

 bool wifi_enabled = WIFI_ENABLED;


 bool has_display = HAS_DISPLAY;
 bool has_sh1106 = HAS_SH1106;
 bool has_flipped_display = HAS_FLIPPED_DISPLAY;
 bool has_lcd1602 = HAS_LCD1602;
 bool has_lcd1602_27 = HAS_LCD1602_27;
 bool has_lcd2004 = HAS_LCD2004;
 bool has_lcd2004_27 = HAS_LCD2004_27;

 bool display_wifi_info = DISPLAY_WIFI_INFO;
 bool display_device_info = DISPLAY_DEVICE_INFO;


 bool ssl_cfa = SSL_CFA;
 bool ssl_madavi = SSL_MADAVI;
 bool ssl_dusti = SSL_SENSORCOMMUNITY;
 char senseboxid[LEN_SENSEBOXID] = SENSEBOXID;

 char host_influx[LEN_HOST_INFLUX];
 char url_influx[LEN_URL_INFLUX];
 unsigned port_influx = PORT_INFLUX;
 char user_influx[LEN_USER_INFLUX] = USER_INFLUX;
 char pwd_influx[LEN_CFG_PASSWORD] = PWD_INFLUX;
 char measurement_name_influx[LEN_MEASUREMENT_NAME_INFLUX];
 bool ssl_influx = SSL_INFLUX;

 char host_custom[LEN_HOST_CUSTOM];
 char url_custom[LEN_URL_CUSTOM];
 bool ssl_custom = SSL_CUSTOM;
 unsigned port_custom = PORT_CUSTOM;
 char user_custom[LEN_USER_CUSTOM] = USER_CUSTOM;
 char pwd_custom[LEN_CFG_PASSWORD] = PWD_CUSTOM;

 void initNonTrivials(const char* id) {
  strcpy(cfg::current_lang, CURRENT_LANG);
  strcpy_P(www_username, WWW_USERNAME);
  strcpy_P(www_password, WWW_PASSWORD);
  strcpy_P(wlanssid, WLANSSID);
  strcpy_P(wlanpwd, WLANPWD);
  strcpy_P(host_custom, HOST_CUSTOM);
  strcpy_P(url_custom, URL_CUSTOM);
  strcpy_P(host_influx, HOST_INFLUX);
  strcpy_P(url_influx, URL_INFLUX);
  strcpy_P(measurement_name_influx, MEASUREMENT_NAME_INFLUX);

  if (!*fs_ssid) {
   strcpy(fs_ssid, SSID_BASENAME);
   strcat(fs_ssid, id);
  }
 }
}

#define JSON_BUFFER_SIZE 2300

enum class PmSensorCmd {
 Start,
 Stop,
 ContinuousMode
};

LoggerConfig loggerConfigs[LoggerCount];

long int sample_count = 0;
bool htu21d_init_failed = false;
bool bmp_init_failed = false;
bool bmx280_init_failed = false;
bool sht3x_init_failed = false;
bool dnms_init_failed = false;
bool gps_init_failed = false;
bool rtc_init_failed = false;
bool airrohr_selftest_failed = false;

#if defined(ESP8266)
ESP8266WebServer server(80);
#endif
#if defined(ESP32)
WebServer server(80);
#endif

#include "./airrohr-cfg.h"




float last_value_dnms_laeq = -1.0;
float last_value_dnms_la_min = -1.0;
float last_value_dnms_la_max = -1.0;




SSD1306 display(0x3c, I2C_PIN_SDA, I2C_PIN_SCL);
SH1106 display_sh1106(0x3c, I2C_PIN_SDA, I2C_PIN_SCL);
LiquidCrystal_I2C* lcd_1602 = nullptr;
LiquidCrystal_I2C* lcd_2004 = nullptr;




#if defined(ESP8266)
SoftwareSerial serialSDS;
SoftwareSerial* serialGPS;
#endif
#if defined(ESP32)
#define serialSDS (Serial1)
#define serialGPS (&(Serial2))
#endif





SoftwareSerial atmega328p;




DHT dht(ONEWIRE_PIN, DHT_TYPE);




PCF8575 pcf8575(0x20);




Adafruit_HTU21DF htu21d;




Adafruit_BMP085 bmp;




BMX280 bmx280;




Adafruit_SHT31 sht3x;




OneWire oneWire(ONEWIRE_PIN);
DallasTemperature ds18b20(&oneWire);




TinyGPSPlus gps;




RTC_DS1307 rtc;




SoftwareSerial serialSD;
File sensor_readings;






boolean trigP1 = false;
boolean trigP2 = false;
unsigned long trigOnP1;
unsigned long trigOnP2;

unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

bool send_now = false;
unsigned long starttime;
unsigned long time_point_device_start_ms;
unsigned long starttime_SDS;
unsigned long starttime_GPS;
unsigned long act_micro;
unsigned long act_milli;
unsigned long last_micro = 0;
unsigned long min_micro = 1000000000;
unsigned long max_micro = 0;

bool is_SDS_running = true;
bool is_PMS_running = true;
bool is_HPM_running = true;

unsigned long sending_time = 0;
unsigned long last_update_attempt;
int last_update_returncode;
int last_sendData_returncode;

float last_value_BMP_T = -128.0;
float last_value_BMP_P = -1.0;
float last_value_BMX280_T = -128.0;
float last_value_BMX280_P = -1.0;
float last_value_BME280_H = -1.0;
float last_value_DHT_T = -128.0;
float last_value_DHT_H = -1.0;
float last_value_DS18B20_T = -1.0;
float last_value_HTU21D_T = -128.0;
float last_value_HTU21D_H = -1.0;
float last_value_SHT3X_T = -128.0;
float last_value_SHT3X_H = -1.0;

uint32_t sds_pm10_sum = 0;
uint32_t sds_pm25_sum = 0;
uint32_t sds_val_count = 0;
uint32_t sds_pm10_max = 0;
uint32_t sds_pm10_min = 20000;
uint32_t sds_pm25_max = 0;
uint32_t sds_pm25_min = 20000;

int pms_pm1_sum = 0;
int pms_pm10_sum = 0;
int pms_pm25_sum = 0;
int pms_val_count = 0;
int pms_pm1_max = 0;
int pms_pm1_min = 20000;
int pms_pm10_max = 0;
int pms_pm10_min = 20000;
int pms_pm25_max = 0;
int pms_pm25_min = 20000;
bool readPMSFromAtmega = true;

int hpm_pm10_sum = 0;
int hpm_pm25_sum = 0;
int hpm_val_count = 0;
int hpm_pm10_max = 0;
int hpm_pm10_min = 20000;
int hpm_pm25_max = 0;
int hpm_pm25_min = 20000;

float last_value_SPS30_P0 = -1.0;
float last_value_SPS30_P1 = -1.0;
float last_value_SPS30_P2 = -1.0;
float last_value_SPS30_P4 = -1.0;
float last_value_SPS30_N05 = -1.0;
float last_value_SPS30_N1 = -1.0;
float last_value_SPS30_N25 = -1.0;
float last_value_SPS30_N4 = -1.0;
float last_value_SPS30_N10 = -1.0;
float last_value_SPS30_TS = -1.0;
float value_SPS30_P0 = 0.0;
float value_SPS30_P1 = 0.0;
float value_SPS30_P2 = 0.0;
float value_SPS30_P4 = 0.0;
float value_SPS30_N05 = 0.0;
float value_SPS30_N1 = 0.0;
float value_SPS30_N25 = 0.0;
float value_SPS30_N4 = 0.0;
float value_SPS30_N10 = 0.0;
float value_SPS30_TS = 0.0;


float value_SPH0645 = 0.0;


uint16_t SPS30_measurement_count = 0;
unsigned long SPS30_read_counter = 0;
unsigned long SPS30_read_error_counter = 0;
unsigned long SPS30_read_timer = 0;
bool sps30_init_failed = false;

float last_value_PPD_P1 = -1.0;
float last_value_PPD_P2 = -1.0;
float last_value_SDS_P1 = -1.0;
float last_value_SDS_P2 = -1.0;
float last_value_PMS_P0 = -1.0;
float last_value_PMS_P1 = -1.0;
float last_value_PMS_P2 = -1.0;
float last_value_HPM_P1 = -1.0;
float last_value_HPM_P2 = -1.0;
double last_value_GPS_lat = -200.0;
double last_value_GPS_lon = -200.0;
double last_value_GPS_alt = -1000.0;
String last_value_GPS_date;
String last_value_GPS_time;
String last_value_GPS_timestamp;
String timestamp;
String last_data_string;
int last_signal_strength;
int switchState = 0;
bool readGPSFromAtmega = true;

bool readDHTFromAtmega = true;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String esp_chipid;
String last_value_SDS_version;

unsigned long SDS_error_count;
unsigned long sendData_error_count;
unsigned long WiFi_error_count;

unsigned long last_page_load = millis();

bool wificonfig_loop = false;
uint8_t sntp_time_set;

unsigned long count_sends = 0;
unsigned long last_display_millis = 0;
uint8_t next_display_count = 0;

struct struct_wifiInfo {
 char ssid[LEN_WLANSSID];
 uint8_t encryptionType;
 int32_t RSSI;
 int32_t channel;
#if defined(ESP8266)
 bool isHidden;
 uint8_t unused[3];
#endif
};

struct struct_wifiInfo *wifiInfo;
uint8_t count_wifiInfo;

template<typename T, std::size_t N> constexpr std::size_t array_num_elements(const T(&)[N]) {
 return N;
}

#define msSince(timestamp_before) (act_milli - (timestamp_before))

const char data_first_part[] PROGMEM = "{\"software_version\": \"" SOFTWARE_VERSION_STR "\", \"sensordatavalues\":[";
const char JSON_SENSOR_DATA_VALUES[] PROGMEM = "sensordatavalues";





#define debug_level_check(level) { if (level > cfg::debug) return; }
static void debug_out(const String& text, unsigned int level);
static void debug_out(const __FlashStringHelper* text, unsigned int level);
static void debug_outln(const String& text, unsigned int level);
static void debug_outln_info(const String& text);
static void debug_outln_verbose(const String& text);
static void debug_outln_error(const __FlashStringHelper* text);
static void debug_outln_info(const __FlashStringHelper* text);
static void debug_outln_verbose(const __FlashStringHelper* text);
static void debug_outln_info(const __FlashStringHelper* text, const String& option);
static void debug_outln_info(const __FlashStringHelper* text, float value);
static void debug_outln_verbose(const __FlashStringHelper* text, const String& option);
static void debug_outln_info_bool(const __FlashStringHelper* text, const bool option);
static void display_debug(const String& text1, const String& text2);
static String check_display_value(double value, double undef, uint8_t len, uint8_t str_len);
static void add_Value2Json(String& res, const __FlashStringHelper* type, const String& value);
static void add_Value2Json(String& res, const __FlashStringHelper* type, const __FlashStringHelper* debug_type, const float& value);
static void SDS_rawcmd(const uint8_t cmd_head1, const uint8_t cmd_head2, const uint8_t cmd_head3);
static bool SDS_cmd(PmSensorCmd cmd);
static bool PMS_cmd(PmSensorCmd cmd);
static bool HPM_cmd(PmSensorCmd cmd);
static void yield_for_serial_buffer(size_t length);
static String SDS_version_date();
static void disable_unneeded_nmea();
static bool boolFromJSON(const DynamicJsonDocument& json, const __FlashStringHelper* key);
static void init_config();
static void writeConfig();
static void createLoggerConfigs();
static String sha1Hex(const String& s);
static String hmac1(const String& secret, const String& s);
static void start_html_page(String& page_content, const String& title);
static void end_html_page(String& page_content);
static void add_form_input(String& page_content, const ConfigShapeId cfgid, const __FlashStringHelper* info, const int length);
static String form_checkbox(const ConfigShapeId cfgid, const String& info, const bool linebreak);
static String form_submit(const String& value);
static String form_select_lang();
static String tmpl(const __FlashStringHelper* patt, const String& value);
static void add_line_value(String& s, const __FlashStringHelper* name, const String& value);
static void add_line_value_bool(String& s, const __FlashStringHelper* name, const bool value);
static void add_line_value_bool(String&s, const __FlashStringHelper* patt, const __FlashStringHelper* name, const bool value);
static void add_table_row_from_value(String& page_content, const __FlashStringHelper* sensor, const __FlashStringHelper* param, const String& value, const String& unit);
static int32_t calcWiFiSignalQuality(int32_t rssi);
static String wlan_ssid_to_table_row(const String& ssid, const String& encryption, int32_t rssi);
static void add_warning_first_cycle(String& page_content);
static void add_age_last_values(String& s);
static String add_sensor_type(const String& sensor_text);
static bool webserver_request_auth();
static void sendHttpRedirect();
static void webserver_root();
static void webserver_config_send_body_get(String& page_content);
static void webserver_config_send_body_post(String& page_content);
static void webserver_config();
static void sensor_restart();
static void webserver_wifi();
static void webserver_values();
static String delayToString(unsigned time_ms);
static void webserver_status();
static void webserver_debug_level();
static void webserver_removeConfig();
static void webserver_reset();
static void webserver_data_json();
static void webserver_prometheus_endpoint();
static void webserver_images();
static void webserver_not_found();
static void setup_webserver();
static int selectChannelForAp();
void enableWebServerOffline();
static void wifiConfig();
static void waitForWifiToConnect(int maxRetries);
static void connectWifi();
static void configureCACertTrustAnchor(WiFiClientSecure* client);
static WiFiClient* getNewLoggerWiFiClient(const LoggerEntry logger);
static void create_influxdb_string_from_data(String& data_4_influxdb, const String& data);
static void send_csv(const String& data);
static void fetchSensorDHT(String& s);
void parseDHTPayloadForDebug(String &dht_data);
String fetchSensorDHTFromAtmega();
static void fetchSensorHTU21D(String& s);
static void fetchSensorBMP(String& s);
static void fetchSensorSHT3x(String& s);
static void fetchSensorBMX280(String& s);
static void fetchSensorDS18B20(String& s);
static void fetchSensorSDS(String& s);
static void fetchSensorPMS(String& s);
void parsePMSPayloadForDebug(String &pms_data);
String fetchSensorPMSFromAtmega();
static void fetchSensorHPM(String& s);
static void fetchSensorPPD(String& s);
static void fetchSensorSPS30(String& s);
static float readDNMScorrection();
static void fetchSensorDNMS(String& s);
static void fetchSensorGPS(String& s);
void parseGPSPayloadForDebug(String &gps_data);
String fetchSensorGPSFromAtmega();
void init_PCF8575();
void init_SPH0645();
void Reinit_SPH0645();
void fetchSensorSPH0645(String& s);
void init_RTC();
void obtain_sendTime();
static bool fwDownloadStream(WiFiClientSecure& client, const String& url, Stream* ostream);
static bool fwDownloadStreamFile(WiFiClientSecure& client, const String& url, const String& fname);
static bool launchUpdateLoader(const String& md5);
static void twoStageOTAUpdate();
static String displayGenerateFooter(unsigned int screen_count);
static void display_values();
static void init_display();
static void init_lcd();
static bool initBMX280(char addr);
static void initSPS30();
static void init_SD();
static void initDNMS();
static void powerOnTestSensors();
static void logEnabledAPIs();
static void logEnabledDisplays();
static void setupNetworkTime();
void openLoggingFile();
void setup(void);
void loop(void);
#line 591 "F:/EMBEDDED SOFTWARE/CFA/sensors.AFRICA-AQ-sensors-software/airrohr-firmware/airrohr-firmware.ino"
static void debug_out(const String& text, unsigned int level) {
 debug_level_check(level); Serial.print(text);
}

static void debug_out(const __FlashStringHelper* text, unsigned int level) {
 debug_level_check(level); Serial.print(text);
}

static void debug_outln(const String& text, unsigned int level) {
 debug_level_check(level); Serial.println(text);
}

static void debug_outln_info(const String& text) {
 debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

static void debug_outln_verbose(const String& text) {
 debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

static void debug_outln_error(const __FlashStringHelper* text) {
 debug_level_check(DEBUG_ERROR); Serial.println(text);
}

static void debug_outln_info(const __FlashStringHelper* text) {
 debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

static void debug_outln_verbose(const __FlashStringHelper* text) {
 debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

static void debug_outln_info(const __FlashStringHelper* text, const String& option) {
 debug_level_check(DEBUG_MIN_INFO);
 Serial.print(text);
 Serial.println(option);
}

static void debug_outln_info(const __FlashStringHelper* text, float value) {
 debug_outln_info(text, String(value));
}

static void debug_outln_verbose(const __FlashStringHelper* text, const String& option) {
 debug_level_check(DEBUG_MED_INFO);
 Serial.print(text);
 Serial.println(option);
}

static void debug_outln_info_bool(const __FlashStringHelper* text, const bool option) {
 debug_level_check(DEBUG_MIN_INFO);
 Serial.print(text);
 Serial.println(String(option));
}

#undef debug_level_check




static void display_debug(const String& text1, const String& text2) {
 debug_outln_info(F("output debug text to displays..."));
 if (cfg::has_display) {
  display.clear();
  display.displayOn();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 12, text1);
  display.drawString(0, 24, text2);
  display.display();
 }
 if (cfg::has_sh1106) {
  display_sh1106.clear();
  display_sh1106.displayOn();
  display_sh1106.setTextAlignment(TEXT_ALIGN_LEFT);
  display_sh1106.drawString(0, 12, text1);
  display_sh1106.drawString(0, 24, text2);
  display_sh1106.display();
 }
 if (lcd_1602) {
  lcd_1602->clear();
  lcd_1602->setCursor(0, 0);
  lcd_1602->print(text1);
  lcd_1602->setCursor(0, 1);
  lcd_1602->print(text2);
 }
 if (lcd_2004) {
  lcd_2004->clear();
  lcd_2004->setCursor(0, 0);
  lcd_2004->print(text1);
  lcd_2004->setCursor(0, 1);
  lcd_2004->print(text2);
 }
}




static String check_display_value(double value, double undef, uint8_t len, uint8_t str_len) {
 RESERVE_STRING(s, 15);
 s = (value != undef ? String(value, len) : String("-"));
 while (s.length() < str_len) {
  s = " " + s;
 }
 return s;
}




static void add_Value2Json(String& res, const __FlashStringHelper* type, const String& value) {
 RESERVE_STRING(s, SMALL_STR);

 s = F("{\"value_type\":\"{t}\",\"value\":\"{v}\"},");
 s.replace("{t}", String(type));
 s.replace("{v}", value);
 res += s;
}

static void add_Value2Json(String& res, const __FlashStringHelper* type, const __FlashStringHelper* debug_type, const float& value) {
 debug_outln_info(FPSTR(debug_type), value);
 add_Value2Json(res, type, String(value));
}





static bool SDS_checksum_valid(const uint8_t (&data)[8]) {
    uint8_t checksum_is = 0;
    for (unsigned i = 0; i < 6; ++i) {
        checksum_is += data[i];
    }
    return (data[7] == 0xAB && checksum_is == data[6]);
}

static void SDS_rawcmd(const uint8_t cmd_head1, const uint8_t cmd_head2, const uint8_t cmd_head3) {
 constexpr uint8_t cmd_len = 19;

 uint8_t buf[cmd_len];
 buf[0] = 0xAA;
 buf[1] = 0xB4;
 buf[2] = cmd_head1;
 buf[3] = cmd_head2;
 buf[4] = cmd_head3;
 for (unsigned i = 5; i < 15; ++i) {
  buf[i] = 0x00;
 }
 buf[15] = 0xFF;
 buf[16] = 0xFF;
 buf[17] = cmd_head1 + cmd_head2 + cmd_head3 - 2;
 buf[18] = 0xAB;
 serialSDS.write(buf, cmd_len);
}

static bool SDS_cmd(PmSensorCmd cmd) {
 switch (cmd) {
 case PmSensorCmd::Start:
  SDS_rawcmd(0x06, 0x01, 0x01);
  break;
 case PmSensorCmd::Stop:
  SDS_rawcmd(0x06, 0x01, 0x00);
  break;
 case PmSensorCmd::ContinuousMode:

  SDS_rawcmd(0x08, 0x01, 0x00);
  SDS_rawcmd(0x02, 0x01, 0x00);
  break;
 }

 return cmd != PmSensorCmd::Stop;
}




static bool PMS_cmd(PmSensorCmd cmd) {
 static constexpr uint8_t start_cmd[] PROGMEM = {
  0x42, 0x4D, 0xE4, 0x00, 0x01, 0x01, 0x74
 };
 static constexpr uint8_t stop_cmd[] PROGMEM = {
  0x42, 0x4D, 0xE4, 0x00, 0x00, 0x01, 0x73
 };
 static constexpr uint8_t continuous_mode_cmd[] PROGMEM = {
  0x42, 0x4D, 0xE1, 0x00, 0x01, 0x01, 0x71
 };
 constexpr uint8_t cmd_len = array_num_elements(start_cmd);

 uint8_t buf[cmd_len];
 switch (cmd) {
 case PmSensorCmd::Start:
  memcpy_P(buf, start_cmd, cmd_len);
  break;
 case PmSensorCmd::Stop:
  memcpy_P(buf, stop_cmd, cmd_len);
  break;
 case PmSensorCmd::ContinuousMode:
  memcpy_P(buf, continuous_mode_cmd, cmd_len);
  break;
 }
 serialSDS.write(buf, cmd_len);
 return cmd != PmSensorCmd::Stop;
}




static bool HPM_cmd(PmSensorCmd cmd) {
 static constexpr uint8_t start_cmd[] PROGMEM = {
  0x68, 0x01, 0x01, 0x96
 };
 static constexpr uint8_t stop_cmd[] PROGMEM = {
  0x68, 0x01, 0x02, 0x95
 };
 static constexpr uint8_t continuous_mode_cmd[] PROGMEM = {
  0x68, 0x01, 0x40, 0x57
 };
 constexpr uint8_t cmd_len = array_num_elements(start_cmd);

 uint8_t buf[cmd_len];
 switch (cmd) {
 case PmSensorCmd::Start:
  memcpy_P(buf, start_cmd, cmd_len);
  break;
 case PmSensorCmd::Stop:
  memcpy_P(buf, stop_cmd, cmd_len);
  break;
 case PmSensorCmd::ContinuousMode:
  memcpy_P(buf, continuous_mode_cmd, cmd_len);
  break;
 }
 serialSDS.write(buf, cmd_len);
 return cmd != PmSensorCmd::Stop;
}


static void yield_for_serial_buffer(size_t length) {
 unsigned long startMillis = millis();
 unsigned long yield_timeout = length * 9 * 1000 / 9600;

 while (serialSDS.available() < (int) length &&
    millis() - startMillis < yield_timeout) {
  yield();
  serialSDS.perform_work();
 }
}




static String SDS_version_date() {

 if (cfg::sds_read && !last_value_SDS_version.length()) {
  debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(DBG_TXT_SDS011_VERSION_DATE));
  is_SDS_running = SDS_cmd(PmSensorCmd::Start);
  delay(250);
  serialSDS.perform_work();
  serialSDS.flush();

  SDS_rawcmd(0x07, 0x00, 0x00);
  delay(400);
  const constexpr uint8_t header_cmd_response[2] = { 0xAA, 0xC5 };
  while (serialSDS.find(header_cmd_response, sizeof(header_cmd_response))) {
   uint8_t data[8];
   yield_for_serial_buffer(sizeof(data));
   unsigned r = serialSDS.readBytes(data, sizeof(data));
   if (r == sizeof(data) && data[0] == 0x07 && SDS_checksum_valid(data)) {
    char tmp[20];
    snprintf_P(tmp, sizeof(tmp), PSTR("%02d-%02d-%02d(%02x%02x)"),
     data[1], data[2], data[3], data[4], data[5]);
    last_value_SDS_version = tmp;
    break;
   }
  }
  debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(DBG_TXT_SDS011_VERSION_DATE));
 }

 return last_value_SDS_version;
}




static void disable_unneeded_nmea() {
 serialGPS->println(F("$PUBX,40,GLL,0,0,0,0*5C"));

 serialGPS->println(F("$PUBX,40,GSA,0,0,0,0*4E"));

 serialGPS->println(F("$PUBX,40,GSV,0,0,0,0*59"));
 serialGPS->println(F("$PUBX,40,VTG,0,0,0,0*5E"));
}







static bool boolFromJSON(const DynamicJsonDocument& json, const __FlashStringHelper* key)
{
 if (json[key].is<char*>()) {
  return !strcmp_P(json[key].as<char*>(), PSTR("true"));
 }
 return json[key].as<bool>();
}

static void readConfig(bool oldconfig = false) {
 bool rewriteConfig = false;

 String cfgName(F("/config.json"));
 if (oldconfig) {
  cfgName += F(".old");
 }

 File configFile = SPIFFS.open(cfgName, "r");
 if (!configFile) {
  if (!oldconfig) {
   return readConfig(true );
  }

  debug_outln_error(F("failed to open config file."));
  return;
 }

 debug_outln_info(F("opened config file..."));
 DynamicJsonDocument json(JSON_BUFFER_SIZE);
 DeserializationError err = deserializeJson(json, configFile);
 configFile.close();

 if (!err) {
  debug_outln_info(F("parsed json..."));
  for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
   ConfigShapeEntry c;
   memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
   if (json[c.cfg_key].isNull()) {
    continue;
   }
   switch (c.cfg_type) {
    case Config_Type_Bool:
     *(c.cfg_val.as_bool) = boolFromJSON(json, c.cfg_key);
     break;
    case Config_Type_UInt:
    case Config_Type_Time:
     *(c.cfg_val.as_uint) = json[c.cfg_key].as<unsigned int>();
     break;
    case Config_Type_String:
    case Config_Type_Password:
     strncpy(c.cfg_val.as_str, json[c.cfg_key].as<char*>(), c.cfg_len);
     c.cfg_val.as_str[c.cfg_len] = '\0';
     break;
   };
  }
  String writtenVersion(json["SOFTWARE_VERSION"].as<char*>());
  if (writtenVersion.length() && writtenVersion[0] == 'N' && SOFTWARE_VERSION != writtenVersion) {
   debug_outln_info(F("Rewriting old config from: "), writtenVersion);



   rewriteConfig = true;
  }
  if (strcmp_P(cfg::senseboxid, PSTR("00112233445566778899aabb")) == 0) {
   cfg::senseboxid[0] = '\0';
   cfg::send2sensemap = false;
   rewriteConfig = true;
  }
  if (strlen(cfg::measurement_name_influx) == 0) {
   strcpy_P(cfg::measurement_name_influx, MEASUREMENT_NAME_INFLUX);
   rewriteConfig = true;
  }
  if (strcmp_P(cfg::host_influx, PSTR("api.luftdaten.info")) == 0) {
   cfg::host_influx[0] = '\0';
   cfg::send2influx = false;
   rewriteConfig = true;
  }
  if (boolFromJSON(json, F("pm24_read")) || boolFromJSON(json, F("pms32_read"))) {
   cfg::pms_read = true;
   rewriteConfig = true;
  }
  if (boolFromJSON(json, F("bmp280_read")) || boolFromJSON(json, F("bme280_read"))) {
   cfg::bmx280_read = true;
   rewriteConfig = true;
  }
 } else {
  debug_outln_error(F("failed to load json config"));

  if (!oldconfig) {
   return readConfig(true );
  }
 }

 if (rewriteConfig) {
  writeConfig();
 }
}

static void init_config() {

 debug_outln_info(F("mounting FS..."));
#if defined(ESP32)
 bool spiffs_begin_ok = SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED);
#else
 bool spiffs_begin_ok = SPIFFS.begin();
#endif

 if (!spiffs_begin_ok) {
  debug_outln_error(F("failed to mount FS"));
  return;
 }
 readConfig();
}




static void writeConfig() {
 DynamicJsonDocument json(JSON_BUFFER_SIZE);
 debug_outln_info(F("Saving config..."));
 json["SOFTWARE_VERSION"] = SOFTWARE_VERSION;

 for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
  ConfigShapeEntry c;
  memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
  switch (c.cfg_type) {
  case Config_Type_Bool:
   json[c.cfg_key].set(*c.cfg_val.as_bool);
   break;
  case Config_Type_UInt:
  case Config_Type_Time:
   json[c.cfg_key].set(*c.cfg_val.as_uint);
   break;
  case Config_Type_Password:
  case Config_Type_String:
   json[c.cfg_key].set(c.cfg_val.as_str);
   break;
  };
 }

 SPIFFS.remove(F("/config.json.old"));
 SPIFFS.rename(F("/config.json"), F("/config.json.old"));

 File configFile = SPIFFS.open(F("/config.json"), "w");
 if (configFile) {
  serializeJson(json, configFile);
  configFile.close();
  debug_outln_info(F("Config written successfully."));
 } else {
  debug_outln_error(F("failed to open config file for writing"));
 }
}




static void createLoggerConfigs() {
#if defined(ESP8266)
 auto new_session = []() { return new BearSSL::Session; };
#else
 auto new_session = []() { return nullptr; };
#endif
   if (cfg::send2cfa) {
     loggerConfigs[LoggerCFA].destport = 80;
     if (cfg::ssl_cfa) {
        loggerConfigs[LoggerCFA].destport = 80;
        loggerConfigs[LoggerCFA].session = new_session();
     }
   }
 if (cfg::send2dusti) {
  loggerConfigs[LoggerSensorCommunity].destport = 80;
  if (cfg::ssl_dusti) {
   loggerConfigs[LoggerSensorCommunity].destport = 443;
   loggerConfigs[LoggerSensorCommunity].session = new_session();
  }
 }
 loggerConfigs[LoggerMadavi].destport = PORT_MADAVI;
 if (cfg::send2madavi && cfg::ssl_madavi) {
  loggerConfigs[LoggerMadavi].destport = 443;
  loggerConfigs[LoggerMadavi].session = new_session();
 }
 loggerConfigs[LoggerSensemap].destport = PORT_SENSEMAP;
 loggerConfigs[LoggerSensemap].session = new_session();
 loggerConfigs[LoggerFSapp].destport = PORT_FSAPP;
 loggerConfigs[LoggerFSapp].session = new_session();
 loggerConfigs[Loggeraircms].destport = PORT_AIRCMS;
 loggerConfigs[LoggerInflux].destport = cfg::port_influx;
 if (cfg::send2influx && cfg::ssl_influx) {
  loggerConfigs[LoggerInflux].session = new_session();
 }
 loggerConfigs[LoggerCustom].destport = cfg::port_custom;
 if (cfg::send2custom && (cfg::ssl_custom || (cfg::port_custom == 443))) {
  loggerConfigs[LoggerCustom].session = new_session();
 }
}




static String sha1Hex(const String& s) {
 char sha1sum_output[20];

#if defined(ESP8266)
 br_sha1_context sc;

 br_sha1_init(&sc);
 br_sha1_update(&sc, s.c_str(), s.length());
 br_sha1_out(&sc, sha1sum_output);
#endif
#if defined(ESP32)
 esp_sha(SHA1, (const unsigned char*) s.c_str(), s.length(), (unsigned char*)sha1sum_output);
#endif
 String r;
 for (uint16_t i = 0; i < 20; i++) {
  char hex[3];
  snprintf(hex, sizeof(hex), "%02x", sha1sum_output[i]);
  r += hex;
 }
 return r;
}

static String hmac1(const String& secret, const String& s) {
 String str = sha1Hex(s);
 str = secret + str;
 return sha1Hex(str);
}





static void start_html_page(String& page_content, const String& title) {
 last_page_load = millis();

 RESERVE_STRING(s, LARGE_STR);
 s = FPSTR(WEB_PAGE_HEADER);
 s.replace("{t}", title);
 server.setContentLength(CONTENT_LENGTH_UNKNOWN);
 server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), s);

 server.sendContent_P(WEB_PAGE_HEADER_HEAD);

 s = FPSTR(WEB_PAGE_HEADER_BODY);
 s.replace("{t}", title);
 if (title != " ") {
  s.replace("{n}", F("&raquo;"));
 } else {
  s.replace("{n}", emptyString);
 }
 s.replace("{id}", esp_chipid);
 s.replace("{mac}", WiFi.macAddress());
 page_content += s;
}

static void end_html_page(String& page_content) {
 if (page_content.length()) {
  server.sendContent(page_content);
 }
 server.sendContent_P(WEB_PAGE_FOOTER);
}

static void add_form_input(String& page_content, const ConfigShapeId cfgid, const __FlashStringHelper* info, const int length) {
 RESERVE_STRING(s, MED_STR);
 s = F("<tr>"
   "<td title='[&lt;= {l}]'>{i}:&nbsp;</td>"
   "<td style='width:{l}em'>"
   "<input type='{t}' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/>"
   "</td></tr>");
 String t_value;
 ConfigShapeEntry c;
 memcpy_P(&c, &configShape[cfgid], sizeof(ConfigShapeEntry));
 switch (c.cfg_type) {
 case Config_Type_UInt:
  t_value = String(*c.cfg_val.as_uint);
  s.replace("{t}", F("number"));
  break;
 case Config_Type_Time:
  t_value = String((*c.cfg_val.as_uint) / 1000);
  s.replace("{t}", F("number"));
  break;
 default:
  t_value = c.cfg_val.as_str;
  t_value.replace("'", "&#39;");
  if (c.cfg_type == Config_Type_Password) {
   s.replace("{t}", F("password"));
  } else {
   s.replace("{t}", F("text"));
  }
 }
 s.replace("{i}", info);
 s.replace("{n}", String(c.cfg_key));
 s.replace("{v}", t_value);
 s.replace("{l}", String(length));
 page_content += s;
}

static String form_checkbox(const ConfigShapeId cfgid, const String& info, const bool linebreak) {
 RESERVE_STRING(s, MED_STR);
 s = F("<label for='{n}'>"
 "<input type='checkbox' name='{n}' value='1' id='{n}' {c}/>"
 "<input type='hidden' name='{n}' value='0'/>"
 "{i}</label><br/>");
 if (*configShape[cfgid].cfg_val.as_bool) {
  s.replace("{c}", F(" checked='checked'"));
 } else {
  s.replace("{c}", emptyString);
 };
 s.replace("{i}", info);
 s.replace("{n}", String(configShape[cfgid].cfg_key));
 if (! linebreak) {
  s.replace("<br/>", emptyString);
 }
 return s;
}

static String form_submit(const String& value) {
 String s = F( "<tr>"
     "<td>&nbsp;</td>"
     "<td>"
     "<input type='submit' name='submit' value='{v}' />"
     "</td>"
     "</tr>");
 s.replace("{v}", value);
 return s;
}

static String form_select_lang() {
 String s_select = F(" selected='selected'");
 String s = F( "<tr>"
     "<td>" INTL_LANGUAGE ":&nbsp;</td>"
     "<td>"
     "<select id='current_lang' name='current_lang'>"
     "<option value='BG'>Bulgarian (BG)</option>"
     "<option value='CZ'>Český (CZ)</option>"
     "<option value='DE'>Deutsch (DE)</option>"
     "<option value='DK'>Dansk (DK)</option>"
     "<option value='EN'>English (EN)</option>"
     "<option value='ES'>Español (ES)</option>"
     "<option value='FR'>Français (FR)</option>"
     "<option value='IT'>Italiano (IT)</option>"
     "<option value='LU'>Lëtzebuergesch (LU)</option>"
     "<option value='NL'>Nederlands (NL)</option>"
     "<option value='PL'>Polski (PL)</option>"
     "<option value='PT'>Português (PT)</option>"
     "<option value='RS'>Srpski (RS)</option>"
     "<option value='RU'>Русский (RU)</option>"
     "<option value='SE'>Svenska (SE)</option>"
     "<option value='TR'>Türkçe (TR)</option>"
     "<option value='UA'>український (UA)</option>"
     "</select>"
     "</td>"
     "</tr>");

 s.replace("'" + String(cfg::current_lang) + "'>", "'" + String(cfg::current_lang) + "'" + s_select + ">");
 return s;
}

static String tmpl(const __FlashStringHelper* patt, const String& value) {
 String s = patt;
 s.replace("{v}", value);
 return s;
}

static void add_line_value(String& s, const __FlashStringHelper* name, const String& value) {
 s += F("<br/>");
 s += name;
 s += ": ";
 s += value;
}

static void add_line_value_bool(String& s, const __FlashStringHelper* name, const bool value) {
 add_line_value(s, name, String(value));
}

static void add_line_value_bool(String&s, const __FlashStringHelper* patt, const __FlashStringHelper* name, const bool value) {
 s += F("<br/>");
 s += tmpl(patt, name);
 s += ": ";
 s += String(value);
}

static void add_table_row_from_value(String& page_content, const __FlashStringHelper* sensor, const __FlashStringHelper* param, const String& value, const String& unit) {
 RESERVE_STRING(s, MED_STR);
 s = F("<tr><td>{s}</td><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
 s.replace("{s}", sensor);
 s.replace("{p}", param);
 s.replace("{v}", value);
 s.replace("{u}", unit);
 page_content += s;
}

static void add_table_row_from_value(String& page_content, const __FlashStringHelper* param, const String& value, const char* unit = nullptr) {
 RESERVE_STRING(s, MED_STR);
 s = F("<tr><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
 s.replace("{p}", param);
 s.replace("{v}", value);
 s.replace("{u}", String(unit));
 page_content += s;
}

static int32_t calcWiFiSignalQuality(int32_t rssi) {

 if (rssi >= 0 || rssi < -100) {
  rssi = -100;
 }
 if (rssi > -50) {
  rssi = -50;
 }
 return (rssi + 100) * 2;
}

static String wlan_ssid_to_table_row(const String& ssid, const String& encryption, int32_t rssi) {
 String s = F( "<tr>"
     "<td>"
     "<a href='#wlanpwd' onclick='setSSID(this)' class='wifi'>{n}</a>&nbsp;{e}"
     "</td>"
     "<td style='width:80%;vertical-align:middle;'>"
     "{v}%"
     "</td>"
     "</tr>");
 s.replace("{n}", ssid);
 s.replace("{e}", encryption);
 s.replace("{v}", String(calcWiFiSignalQuality(rssi)));
 return s;
}

static void add_warning_first_cycle(String& page_content) {
 String s = FPSTR(INTL_TIME_TO_FIRST_MEASUREMENT);
 unsigned int time_to_first = cfg::sending_intervall_ms - msSince(starttime);
 if (time_to_first > cfg::sending_intervall_ms) {
  time_to_first = 0;
 }
 s.replace("{v}", String(((time_to_first + 500) / 1000)));
 page_content += s;
}

static void add_age_last_values(String& s) {
 s += "<b>";
 unsigned int time_since_last = msSince(starttime);
 if (time_since_last > cfg::sending_intervall_ms) {
  time_since_last = 0;
 }
 s += String((time_since_last + 500) / 1000);
 s += FPSTR(INTL_TIME_SINCE_LAST_MEASUREMENT);
 s += FPSTR(WEB_B_BR_BR);
}

static String add_sensor_type(const String& sensor_text) {
 RESERVE_STRING(s, SMALL_STR);
 s = sensor_text;
 s.replace("{pm}", FPSTR(INTL_PARTICULATE_MATTER));
 s.replace("{t}", FPSTR(INTL_TEMPERATURE));
 s.replace("{h}", FPSTR(INTL_HUMIDITY));
 s.replace("{p}", FPSTR(INTL_PRESSURE));
 s.replace("{l_a}", FPSTR(INTL_LEQ_A));
 return s;
}






static bool webserver_request_auth() {
 if (cfg::www_basicauth_enabled && ! wificonfig_loop) {
  debug_outln_info(F("validate request auth..."));
  if (!server.authenticate(cfg::www_username, cfg::www_password)) {
   server.requestAuthentication(BASIC_AUTH, "Sensor Login", F("Authentication failed"));
   return false;
  }
 }
 return true;
}

static void sendHttpRedirect() {
 server.sendHeader(F("Location"), F("http://192.168.4.1/config"));
 server.send(302, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), emptyString);
}




static void webserver_root() {
 if (WiFi.status() != WL_CONNECTED) {
  sendHttpRedirect();
 } else {
  if (!webserver_request_auth())
  { return; }

  RESERVE_STRING(page_content, XLARGE_STR);
  start_html_page(page_content, emptyString);
  debug_outln_info(F("ws: root ..."));


  page_content += FPSTR(WEB_ROOT_PAGE_CONTENT);
  page_content.replace(F("{t}"), FPSTR(INTL_CURRENT_DATA));
  page_content.replace(F("{s}"), FPSTR(INTL_DEVICE_STATUS));
  page_content.replace(F("{conf}"), FPSTR(INTL_CONFIGURATION));
  page_content.replace(F("{restart}"), FPSTR(INTL_RESTART_SENSOR));
  page_content.replace(F("{debug_setting}"), FPSTR(INTL_DEBUG_SETTING_TO));
  end_html_page(page_content);
 }
}





static void webserver_config_send_body_get(String& page_content) {
 using namespace cfg;

 auto add_form_checkbox = [&page_content](const ConfigShapeId cfgid, const String& info) {
  page_content += form_checkbox(cfgid, info, true);
 };

 auto add_form_checkbox_sensor = [&add_form_checkbox](const ConfigShapeId cfgid, __const __FlashStringHelper* info) {
  add_form_checkbox(cfgid, add_sensor_type(info));
 };

 debug_outln_info(F("begin webserver_config_body_get ..."));
 page_content += F("<form method='POST' action='/config' style='width:100%;'>\n<b>" INTL_WIFI_SETTINGS "</b><br/>");
 debug_outln_info(F("ws: config page 1"));
 if (wificonfig_loop) {
  page_content += F("<div id='wifilist'>" INTL_WIFI_NETWORKS "</div><br/>");
 }
 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_wlanssid, FPSTR(INTL_FS_WIFI_NAME), LEN_WLANSSID-1);
 add_form_input(page_content, Config_wlanpwd, FPSTR(INTL_PASSWORD), LEN_CFG_PASSWORD-1);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);
 page_content += F("<hr/>\n<br/><b>");

 page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
 page_content += FPSTR(WEB_B_BR);
 page_content += FPSTR(BR_TAG);


 server.sendContent(page_content);
 page_content = emptyString;

 add_form_checkbox(Config_www_basicauth_enabled, FPSTR(INTL_BASICAUTH));
 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_www_username, FPSTR(INTL_USER), LEN_WWW_USERNAME-1);
 add_form_input(page_content, Config_www_password, FPSTR(INTL_PASSWORD), LEN_CFG_PASSWORD-1);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);
 page_content += FPSTR(BR_TAG);


 server.sendContent(page_content);

 if (! wificonfig_loop) {
  page_content = FPSTR(INTL_FS_WIFI_DESCRIPTION);
  page_content += FPSTR(BR_TAG);

  page_content += FPSTR(TABLE_TAG_OPEN);
  add_form_input(page_content, Config_fs_ssid, FPSTR(INTL_FS_WIFI_NAME), LEN_FS_SSID-1);
  add_form_input(page_content, Config_fs_pwd, FPSTR(INTL_PASSWORD), LEN_CFG_PASSWORD-1);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);


  server.sendContent(page_content);
 }
 page_content = FPSTR(WEB_BR_LF_B);
 page_content += F(INTL_FIRMWARE "</b>&nbsp;");
 add_form_checkbox(Config_auto_update, FPSTR(INTL_AUTO_UPDATE));
 add_form_checkbox(Config_use_beta, FPSTR(INTL_USE_BETA));

 page_content += FPSTR(TABLE_TAG_OPEN);
 page_content += form_select_lang();
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);

 page_content += F("<script>"
     "var $ = function(e) { return document.getElementById(e); };"
     "function updateOTAOptions() { "
  "$('current_lang').disabled = $('use_beta').disabled = !$('auto_update').checked; "
  "}; updateOTAOptions(); $('auto_update').onchange = updateOTAOptions;"
  "</script>");

 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_debug, FPSTR(INTL_DEBUG_LEVEL), 1);
 add_form_input(page_content, Config_sending_intervall_ms, FPSTR(INTL_MEASUREMENT_INTERVAL), 5);
 add_form_input(page_content, Config_time_for_wifi_config, FPSTR(INTL_DURATION_ROUTER_MODE), 5);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);

 server.sendContent(page_content);
 page_content = FPSTR(WEB_BR_LF_B);
 page_content += FPSTR(INTL_MORE_SETTINGS);
 page_content += FPSTR(WEB_B_BR);

 add_form_checkbox(Config_wifi_enabled, FPSTR(INTL_ENABLE_WIFI));
 add_form_checkbox(Config_has_display, FPSTR(INTL_DISPLAY));
 add_form_checkbox(Config_has_sh1106, FPSTR(INTL_SH1106));
 add_form_checkbox(Config_has_flipped_display, FPSTR(INTL_FLIP_DISPLAY));
 add_form_checkbox(Config_has_lcd1602_27, FPSTR(INTL_LCD1602_27));
 add_form_checkbox(Config_has_lcd1602, FPSTR(INTL_LCD1602_3F));


 server.sendContent(page_content);
 page_content = emptyString;

 add_form_checkbox(Config_wifi_enabled, FPSTR(INTL_ENABLE_WIFI));
 add_form_checkbox(Config_has_lcd2004_27, FPSTR(INTL_LCD2004_27));
 add_form_checkbox(Config_has_lcd2004, FPSTR(INTL_LCD2004_3F));
 add_form_checkbox(Config_display_wifi_info, FPSTR(INTL_DISPLAY_WIFI_INFO));
 add_form_checkbox(Config_display_device_info, FPSTR(INTL_DISPLAY_DEVICE_INFO));

 server.sendContent(page_content);
 page_content = FPSTR(WEB_BR_LF_B);
 page_content += FPSTR(INTL_SENSORS);
 page_content += FPSTR(WEB_B_BR);
 add_form_checkbox_sensor(Config_sds_read, FPSTR(INTL_SDS011));
 add_form_checkbox_sensor(Config_hpm_read, FPSTR(INTL_HPM));
 add_form_checkbox_sensor(Config_sps30_read, FPSTR(INTL_SPS30));


 server.sendContent(page_content);
 page_content = emptyString;

 add_form_checkbox_sensor(Config_sph0645_read, FPSTR(INTL_SPH0645));
 add_form_checkbox_sensor(Config_dht_read, FPSTR(INTL_DHT22));
 add_form_checkbox_sensor(Config_htu21d_read, FPSTR(INTL_HTU21D));
 add_form_checkbox_sensor(Config_bmx280_read, FPSTR(INTL_BMX280));
 add_form_checkbox_sensor(Config_sht3x_read, FPSTR(INTL_SHT3X));
 add_form_checkbox_sensor(Config_ds18b20_read, FPSTR(INTL_DS18B20));


 server.sendContent(page_content);
 page_content = emptyString;

 add_form_checkbox_sensor(Config_dnms_read, FPSTR(INTL_DNMS));
 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_dnms_correction, FPSTR(INTL_DNMS_CORRECTION), LEN_DNMS_CORRECTION-1);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);

 page_content += FPSTR(WEB_BR_LF_B);
 page_content += FPSTR(INTL_MORE_SENSORS);
 page_content += FPSTR(WEB_B_BR);

 add_form_checkbox_sensor(Config_pms_read, FPSTR(INTL_PMS));
 add_form_checkbox_sensor(Config_bmp_read, FPSTR(INTL_BMP180));
 add_form_checkbox(Config_gps_read, FPSTR(INTL_NEO6M));

 page_content += FPSTR(WEB_BR_LF_B);
 page_content += F("APIs");
 page_content += FPSTR(WEB_B_BR);

 server.sendContent(page_content);

 page_content = form_checkbox(Config_send2dusti, F("API Sensor.Community"), false);
 page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
 page_content += form_checkbox(Config_ssl_dusti, FPSTR(WEB_HTTPS), false);
 page_content += FPSTR(WEB_BRACE_BR);
 page_content += form_checkbox(Config_send2madavi, F("API Madavi.de"), false);
 page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
 page_content += form_checkbox(Config_ssl_madavi, FPSTR(WEB_HTTPS), false);
 page_content += FPSTR(WEB_BRACE_BR);
 add_form_checkbox(Config_send2csv, tmpl(FPSTR(INTL_SEND_TO), FPSTR(WEB_CSV)));
 add_form_checkbox(Config_send2fsapp, tmpl(FPSTR(INTL_SEND_TO), FPSTR(WEB_FEINSTAUB_APP)));
 add_form_checkbox(Config_send2aircms, tmpl(FPSTR(INTL_SEND_TO), F("aircms.online")));
 add_form_checkbox(Config_send2sensemap, tmpl(FPSTR(INTL_SEND_TO), F("OpenSenseMap")));
 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_senseboxid, F("senseBox&nbsp;ID"), LEN_SENSEBOXID-1);

 server.sendContent(page_content);
 page_content = FPSTR(TABLE_TAG_CLOSE_BR);
 page_content += FPSTR(BR_TAG);
 page_content += form_checkbox(Config_send2custom, FPSTR(INTL_SEND_TO_OWN_API), false);
 page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
 page_content += form_checkbox(Config_ssl_custom, FPSTR(WEB_HTTPS), false);
 page_content += FPSTR(WEB_BRACE_BR);

 server.sendContent(page_content);
 page_content = FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_host_custom, FPSTR(INTL_SERVER), LEN_HOST_CUSTOM-1);
 add_form_input(page_content, Config_url_custom, FPSTR(INTL_PATH), LEN_URL_CUSTOM-1);
 add_form_input(page_content, Config_port_custom, FPSTR(INTL_PORT), MAX_PORT_DIGITS);
 add_form_input(page_content, Config_user_custom, FPSTR(INTL_USER), LEN_USER_CUSTOM-1);
 add_form_input(page_content, Config_pwd_custom, FPSTR(INTL_PASSWORD), LEN_CFG_PASSWORD-1);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);

 page_content += FPSTR(BR_TAG);

 server.sendContent(page_content);
 page_content = form_checkbox(Config_send2influx, tmpl(FPSTR(INTL_SEND_TO), F("InfluxDB")), false);

 page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
 page_content += form_checkbox(Config_ssl_influx, FPSTR(WEB_HTTPS), false);
 page_content += FPSTR(WEB_BRACE_BR);
 page_content += FPSTR(TABLE_TAG_OPEN);
 add_form_input(page_content, Config_host_influx, FPSTR(INTL_SERVER), LEN_HOST_INFLUX-1);
 add_form_input(page_content, Config_url_influx, FPSTR(INTL_PATH), LEN_URL_INFLUX-1);
 add_form_input(page_content, Config_port_influx, FPSTR(INTL_PORT), MAX_PORT_DIGITS);
 add_form_input(page_content, Config_user_influx, FPSTR(INTL_USER), LEN_USER_INFLUX-1);
 add_form_input(page_content, Config_pwd_influx, FPSTR(INTL_PASSWORD), LEN_CFG_PASSWORD-1);
 add_form_input(page_content, Config_measurement_name_influx, F("Measurement"), LEN_MEASUREMENT_NAME_INFLUX-1);
 page_content += FPSTR(TABLE_TAG_CLOSE_BR);
 page_content += form_submit(FPSTR(INTL_SAVE_AND_RESTART));
 page_content += FPSTR(BR_TAG);
 page_content += FPSTR(WEB_BR_FORM);
 if (wificonfig_loop) {
  page_content += F("<script>window.setTimeout(load_wifi_list,1000);</script>");
 }

 server.sendContent(page_content);
 page_content = emptyString;
}

static void webserver_config_send_body_post(String& page_content) {
 String masked_pwd;

 using namespace cfg;

 for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
  ConfigShapeEntry c;
  memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
  const String s_param(c.cfg_key);
  if (!server.hasArg(s_param)) {
   continue;
  }

  switch (c.cfg_type) {
  case Config_Type_UInt:
   *(c.cfg_val.as_uint) = server.arg(s_param).toInt();
   break;
  case Config_Type_Time:
   *(c.cfg_val.as_uint) = server.arg(s_param).toInt() * 1000;
   break;
  case Config_Type_Bool:
   *(c.cfg_val.as_bool) = (server.arg(s_param) == "1");
   break;
  case Config_Type_String:
   strncpy(c.cfg_val.as_str, server.arg(s_param).c_str(), c.cfg_len);
   c.cfg_val.as_str[c.cfg_len] = '\0';
   break;
  case Config_Type_Password:
   const String server_arg(server.arg(s_param));
   masked_pwd = emptyString;
   for (uint8_t i=0;i<server_arg.length();i++)
    masked_pwd += '*';
   if (masked_pwd != server_arg || !server_arg.length()) {
    server_arg.toCharArray(c.cfg_val.as_str, LEN_CFG_PASSWORD);
   }
   break;
  }
 }

 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Sensor.Community"), send2dusti);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Madavi"), send2madavi);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_SPH0645), sph0645_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_DHT22), dht_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_HTU21D), htu21d_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_SDS011), sds_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_PMSx003), pms_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_HPM), hpm_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_SPS30), sps30_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_PPD42NS), ppd_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_BMX280), bmx280_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_SHT3X), sht3x_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_DS18B20), ds18b20_read);
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_DNMS), dnms_read);
 add_line_value(page_content, FPSTR(INTL_DNMS_CORRECTION), String(dnms_correction));
 add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("GPS"), gps_read);


 server.sendContent(page_content);
 page_content = emptyString;

 add_line_value_bool(page_content, FPSTR(INTL_ENABLE_WIFI), wifi_enabled);
 add_line_value_bool(page_content, FPSTR(INTL_DISPLAY), has_display);
 add_line_value_bool(page_content, FPSTR(INTL_SH1106), has_sh1106);
 add_line_value_bool(page_content, FPSTR(INTL_FLIP_DISPLAY), has_flipped_display);
 add_line_value_bool(page_content, FPSTR(INTL_LCD1602_27), has_lcd1602_27);
 add_line_value_bool(page_content, FPSTR(INTL_LCD1602_3F), has_lcd1602);
 add_line_value_bool(page_content, FPSTR(INTL_LCD2004_27), has_lcd2004_27);
 add_line_value_bool(page_content, FPSTR(INTL_LCD2004_3F), has_lcd2004);
 add_line_value_bool(page_content, FPSTR(INTL_DISPLAY_WIFI_INFO), display_wifi_info);
 add_line_value_bool(page_content, FPSTR(INTL_DISPLAY_DEVICE_INFO), display_device_info);
 add_line_value_bool(page_content, FPSTR(INTL_AUTO_UPDATE), auto_update);
 add_line_value_bool(page_content, FPSTR(INTL_USE_BETA), use_beta);
 add_line_value(page_content, FPSTR(INTL_DEBUG_LEVEL), String(debug));
 add_line_value(page_content, FPSTR(INTL_MEASUREMENT_INTERVAL), String(sending_intervall_ms));
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Feinstaub-App"), send2fsapp);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("aircms.online"), send2aircms);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), FPSTR(WEB_CSV), send2csv);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), FPSTR(WEB_FEINSTAUB_APP), send2fsapp);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("opensensemap"), send2sensemap);


 server.sendContent(page_content);
 page_content = emptyString;

 page_content += F("<br/>senseBox-ID ");
 page_content += senseboxid;
 page_content += FPSTR(WEB_BR_BR);
 add_line_value_bool(page_content, FPSTR(INTL_SEND_TO_OWN_API), send2custom);
 add_line_value(page_content, FPSTR(INTL_SERVER), host_custom);
 add_line_value(page_content, FPSTR(INTL_PATH), url_custom);
 add_line_value(page_content, FPSTR(INTL_PORT), String(port_custom));
 add_line_value(page_content, FPSTR(INTL_USER), user_custom);
 add_line_value(page_content, FPSTR(INTL_PASSWORD), pwd_custom);
 page_content += F("<br/><br/>InfluxDB: ");
 page_content += String(send2influx);
 add_line_value(page_content, FPSTR(INTL_SERVER), host_influx);
 add_line_value(page_content, FPSTR(INTL_PATH), url_influx);
 add_line_value(page_content, FPSTR(INTL_PORT), String(port_influx));
 add_line_value(page_content, FPSTR(INTL_USER), user_influx);
 add_line_value(page_content, FPSTR(INTL_PASSWORD), pwd_influx);
 add_line_value(page_content, F("Measurement"), measurement_name_influx);
 add_line_value(page_content, F("SSL"), String(ssl_influx));
 page_content += FPSTR(WEB_BR_BR);
 page_content += FPSTR(INTL_SENSOR_IS_REBOOTING);

 server.sendContent(page_content);
 page_content = emptyString;
}

static void webserver_config() {
 if (!webserver_request_auth())
 { return; }

 debug_outln_info(F("ws: config page ..."));

 server.sendHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
 server.sendHeader(F("Pragma"), F("no-cache"));
 server.sendHeader(F("Expires"), F("0"));

 server.setContentLength(CONTENT_LENGTH_UNKNOWN);

 RESERVE_STRING(page_content, XLARGE_STR);

 start_html_page(page_content, FPSTR(INTL_CONFIGURATION));
 if (wificonfig_loop) {
  page_content += FPSTR(WEB_CONFIG_SCRIPT);
 }

 if (server.method() == HTTP_GET) {
  webserver_config_send_body_get(page_content);
 } else {
  webserver_config_send_body_post(page_content);
 }
 end_html_page(page_content);

 if (server.method() == HTTP_POST) {
  display_debug(F("Writing config"), F("and restarting"));
  writeConfig();
  sensor_restart();
 }
}

static void sensor_restart() {
#if defined(ESP8266)
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  delay(100);
#endif
  SPIFFS.end();
  serialSDS.end();
  debug_outln_info(F("Restart."));
  delay(500);
  ESP.restart();

  while(true) { yield(); }
}




static void webserver_wifi() {
 String page_content;

 debug_outln_info(F("wifi networks found: "), String(count_wifiInfo));
 if (count_wifiInfo == 0) {
  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(INTL_NO_NETWORKS);
  page_content += FPSTR(BR_TAG);
 } else {
  std::unique_ptr<int[]> indices(new int[count_wifiInfo]);
  debug_outln_info(F("ws: wifi ..."));
  for (unsigned i = 0; i < count_wifiInfo; ++i) {
   indices[i] = i;
  }
  for (unsigned i = 0; i < count_wifiInfo; i++) {
   for (unsigned j = i + 1; j < count_wifiInfo; j++) {
    if (wifiInfo[indices[j]].RSSI > wifiInfo[indices[i]].RSSI) {
     std::swap(indices[i], indices[j]);
    }
   }
  }
  int duplicateSsids = 0;
  for (int i = 0; i < count_wifiInfo; i++) {
   if (indices[i] == -1) {
    continue;
   }
   for (int j = i + 1; j < count_wifiInfo; j++) {
    if (strncmp(wifiInfo[indices[i]].ssid, wifiInfo[indices[j]].ssid, sizeof(wifiInfo[0].ssid)) == 0) {
     indices[j] = -1;
     ++duplicateSsids;
    }
   }
  }

  page_content += FPSTR(INTL_NETWORKS_FOUND);
  page_content += String(count_wifiInfo - duplicateSsids);
  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(BR_TAG);
  page_content += FPSTR(TABLE_TAG_OPEN);

  for (int i = 0; i < count_wifiInfo; ++i) {
   if (indices[i] == -1
 #if defined (ESP8266)
    || wifiInfo[indices[i]].isHidden
 #endif
   ) {
    continue;
   }

#if defined(ESP8266)
   page_content += wlan_ssid_to_table_row(wifiInfo[indices[i]].ssid, ((wifiInfo[indices[i]].encryptionType == ENC_TYPE_NONE) ? " " : u8"🔒"), wifiInfo[indices[i]].RSSI);
#endif
#if defined(ESP32)
   page_content += wlan_ssid_to_table_row(wifiInfo[indices[i]].ssid, ((wifiInfo[indices[i]].encryptionType == WIFI_AUTH_OPEN) ? " " : u8"🔒"), wifiInfo[indices[i]].RSSI);
#endif
  }
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  page_content += FPSTR(BR_TAG);
 }
 server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}




static void webserver_values() {
 if ((WiFi.status() != WL_CONNECTED) && cfg::wifi_enabled) {
  sendHttpRedirect();
 } else {
  RESERVE_STRING(page_content, XLARGE_STR);
  start_html_page(page_content, FPSTR(INTL_CURRENT_DATA));
  const String unit_PM("µg/m³");
  const String unit_Deg("°");
  const String unit_T("°C");
  const String unit_H("%");
  const String unit_P("hPa");
  const String unit_NC(F("#/cm³"));
  const String unit_TS("µm");
  const String unit_LA(F("dB(A)"));

  const int signal_quality = calcWiFiSignalQuality(last_signal_strength);
  debug_outln_info(F("ws: values ..."));
  if (!count_sends) {
   page_content += F("<b style='color:red'>");
   add_warning_first_cycle(page_content);
   page_content += FPSTR(WEB_B_BR_BR);
  } else {
   add_age_last_values(page_content);
  }

  server.sendContent(page_content);
  page_content = F("<table cellspacing='0' border='1' cellpadding='5'>\n"
      "<tr><th>" INTL_SENSOR "</th><th> " INTL_PARAMETER "</th><th>" INTL_VALUE "</th></tr>");
  if (cfg::ppd_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_PPD42NS), FPSTR(WEB_PM1), check_display_value(last_value_PPD_P1, -1, 1, 0), FPSTR(INTL_PARTICLES_PER_LITER));
   add_table_row_from_value(page_content, FPSTR(SENSORS_PPD42NS), FPSTR(WEB_PM25), check_display_value(last_value_PPD_P2, -1, 1, 0), FPSTR(INTL_PARTICLES_PER_LITER));
  }
  if (cfg::sds_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), FPSTR(WEB_PM25), check_display_value(last_value_SDS_P2, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), FPSTR(WEB_PM10), check_display_value(last_value_SDS_P1, -1, 1, 0), unit_PM);
  }
  if (cfg::pms_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM1), check_display_value(last_value_PMS_P0, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM25), check_display_value(last_value_PMS_P2, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM10), check_display_value(last_value_PMS_P1, -1, 1, 0), unit_PM);
  }
  if (cfg::hpm_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_HPM), FPSTR(WEB_PM25), check_display_value(last_value_HPM_P2, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_HPM), FPSTR(WEB_PM10), check_display_value(last_value_HPM_P1, -1, 1, 0), unit_PM);
  }
  if (cfg::sps30_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM1), check_display_value(last_value_SPS30_P0, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM25), check_display_value(last_value_SPS30_P2, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM4), check_display_value(last_value_SPS30_P4, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM10), check_display_value(last_value_SPS30_P1, -1, 1, 0), unit_PM);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC0k5), check_display_value(last_value_SPS30_N05, -1, 0, 0), unit_NC);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC1k0), check_display_value(last_value_SPS30_N1, -1, 0, 0), unit_NC);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC2k5), check_display_value(last_value_SPS30_N25, -1, 0, 0), unit_NC);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC4k0), check_display_value(last_value_SPS30_N4, -1, 0, 0), unit_NC);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC10), check_display_value(last_value_SPS30_N10, -1, 0, 0), unit_NC);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_TPS), check_display_value(last_value_SPS30_TS, -1, 1, 0), unit_TS);
  }

  if (cfg::dht_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DHT22), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_DHT_T, -128, 1, 0), unit_T);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DHT22), FPSTR(INTL_HUMIDITY), check_display_value(last_value_DHT_H, -1, 1, 0), unit_H);
  }
  if (cfg::htu21d_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_HTU21D), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_HTU21D_T, -128, 1, 0), unit_T);
   add_table_row_from_value(page_content, FPSTR(SENSORS_HTU21D), FPSTR(INTL_HUMIDITY), check_display_value(last_value_HTU21D_H, -1, 1, 0), unit_H);
  }
  if (cfg::bmp_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_BMP180), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_BMP_T, -128, 1, 0), unit_T);
   add_table_row_from_value(page_content, FPSTR(SENSORS_BMP180), FPSTR(INTL_PRESSURE), check_display_value(last_value_BMP_P / 100.0f, (-1 / 100.0f), 2, 0), unit_P);
  }
  if (cfg::bmx280_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_BMX280_T, -128, 1, 0), unit_T);
   add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_PRESSURE), check_display_value(last_value_BMX280_P / 100.0f, (-1 / 100.0f), 2, 0), unit_P);
   if (bmx280.sensorID() == BME280_SENSOR_ID) {
    add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_HUMIDITY), check_display_value(last_value_BME280_H, -1, 1, 0), unit_H);
   }
  }
  if (cfg::sht3x_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SHT3X), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_SHT3X_T, -128, 1, 0), unit_T);
   add_table_row_from_value(page_content, FPSTR(SENSORS_SHT3X), FPSTR(INTL_HUMIDITY), check_display_value(last_value_SHT3X_H, -1, 1, 0), unit_H);
  }
  if (cfg::ds18b20_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DS18B20), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_DS18B20_T, -128, 1, 0), unit_T);
  }
  if (cfg::dnms_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LEQ_A), check_display_value(last_value_dnms_laeq, -1, 1, 0), unit_LA);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LA_MIN), check_display_value(last_value_dnms_la_min, -1, 1, 0), unit_LA);
   add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LA_MAX), check_display_value(last_value_dnms_la_max, -1, 1, 0), unit_LA);
  }
  if (cfg::gps_read) {
   page_content += FPSTR(EMPTY_ROW);
   add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_LATITUDE), check_display_value(last_value_GPS_lat, -200.0, 6, 0), unit_Deg);
   add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_LONGITUDE), check_display_value(last_value_GPS_lon, -200.0, 6, 0), unit_Deg);
   add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_ALTITUDE), check_display_value(last_value_GPS_alt, -1000.0, 2, 0), "m");
   add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_DATE), last_value_GPS_date, emptyString);
   add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_TIME), last_value_GPS_time, emptyString);
  }

  server.sendContent(page_content);
  page_content = FPSTR(EMPTY_ROW);

  add_table_row_from_value(page_content, F("WiFi"), FPSTR(INTL_SIGNAL_STRENGTH), String(last_signal_strength), "dBm");
  add_table_row_from_value(page_content, F("WiFi"), FPSTR(INTL_SIGNAL_QUALITY), String(signal_quality), "%");

  page_content += FPSTR(EMPTY_ROW);
  page_content += FPSTR(TABLE_TAG_CLOSE_BR);
  end_html_page(page_content);
 }
}

static String delayToString(unsigned time_ms) {

 char buf[64];
 String s;

 if (time_ms > 2 * 1000 * 60 * 60 * 24) {
  sprintf_P(buf, PSTR("%d days, "), time_ms / (1000 * 60 * 60 * 24));
  s += buf;
  time_ms %= 1000 * 60 * 60 * 24;
 }

 if (time_ms > 2 * 1000 * 60 * 60) {
  sprintf_P(buf, PSTR("%d hours, "), time_ms / (1000 * 60 * 60));
  s += buf;
  time_ms %= 1000 * 60 * 60;
 }

 if (time_ms > 2 * 1000 * 60) {
  sprintf_P(buf, PSTR("%d min, "), time_ms / (1000 * 60));
  s += buf;
  time_ms %= 1000 * 60;
 }

 if (time_ms > 2 * 1000) {
  sprintf_P(buf, PSTR("%ds, "), time_ms / 1000);
  s += buf;
 }

 if (s.length() > 2) {
  s = s.substring(0, s.length() - 2);
 }

 return s;
}




static void webserver_status() {
 if ((WiFi.status() != WL_CONNECTED) && cfg::wifi_enabled) {
  sendHttpRedirect();
  return;
 }

 RESERVE_STRING(page_content, XLARGE_STR);
 start_html_page(page_content, FPSTR(INTL_DEVICE_STATUS));

 debug_outln_info(F("ws: status ..."));
 server.sendContent(page_content);
 page_content = F("<table cellspacing='0' border='1' cellpadding='5'>\n"
   "<tr><th> " INTL_PARAMETER "</th><th>" INTL_VALUE "</th></tr>");
 String versionHtml(SOFTWARE_VERSION);
 versionHtml += F("/ST:");
 versionHtml += String(!airrohr_selftest_failed);
 versionHtml += '/';
 versionHtml += ESP.getFullVersion();
 versionHtml.replace("/", FPSTR(BR_TAG));
 add_table_row_from_value(page_content, FPSTR(INTL_FIRMWARE), versionHtml);
 add_table_row_from_value(page_content, F("Free Memory"), String(ESP.getFreeHeap()));
 add_table_row_from_value(page_content, F("Heap Fragmentation"), String(ESP.getHeapFragmentation()), "%");
 if (cfg::auto_update) {
  add_table_row_from_value(page_content, F("Last OTA"), delayToString(millis() - last_update_attempt));
 }
#if defined(ESP8266)
 add_table_row_from_value(page_content, F("NTP Sync"), String(sntp_time_set));
 StreamString ntpinfo;

 for (unsigned i = 0; i < SNTP_MAX_SERVERS; i++) {
  const ip_addr_t* sntp = sntp_getserver(i);
  if (sntp && !ip_addr_isany(sntp)) {
   const char* name = sntp_getservername(i);
   if (!ntpinfo.isEmpty()) {
    ntpinfo.print(FPSTR(BR_TAG));
   }
   ntpinfo.printf_P(PSTR("%s (%s)"), IPAddress(*sntp).toString().c_str(), name ? name : "?");
   ntpinfo.printf_P(PSTR(" reachable: %s"), sntp_getreachability(i) ? "Yes" : "No");
  }
 }
 add_table_row_from_value(page_content, F("NTP Info"), ntpinfo);
#endif

 time_t now = time(nullptr);
 add_table_row_from_value(page_content, FPSTR(INTL_TIME), ctime(&now));
 add_table_row_from_value(page_content, F("Uptime"), delayToString(millis() - time_point_device_start_ms));
 add_table_row_from_value(page_content, F("Reset Reason"), ESP.getResetReason());
 if (cfg::sds_read) {
  page_content += FPSTR(EMPTY_ROW);
  add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), last_value_SDS_version);
 }

 page_content += FPSTR(EMPTY_ROW);
 page_content += F("<tr><td colspan='2'><b>" INTL_ERROR "</b></td></tr>");
 add_table_row_from_value(page_content, F("WiFi"), String(WiFi_error_count));
 if (last_update_returncode != 0) {
  add_table_row_from_value(page_content, F("OTA Return"),
   last_update_returncode > 0 ? String(last_update_returncode) : HTTPClient::errorToString(last_update_returncode));
 }
 add_table_row_from_value(page_content, F("Data Send"), String(sendData_error_count));
 if (last_sendData_returncode != 0) {
  add_table_row_from_value(page_content, F("Data Send Return"),
   last_sendData_returncode > 0 ? String(last_sendData_returncode) : HTTPClient::errorToString(last_sendData_returncode));
 }
 if (cfg::sds_read) {
  add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), String(SDS_error_count));
 }
 if (cfg::sps30_read) {
  add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), String(SPS30_read_error_counter));
 }

 server.sendContent(page_content);
 page_content = emptyString;

 if (count_sends > 0) {
  page_content += FPSTR(EMPTY_ROW);
  add_table_row_from_value(page_content, F(INTL_NUMBER_OF_MEASUREMENTS), String(count_sends));
  if (sending_time > 0) {
   add_table_row_from_value(page_content, F(INTL_TIME_SENDING_MS), String(sending_time), "ms");
  }
 }

 page_content += FPSTR(TABLE_TAG_CLOSE_BR);
 end_html_page(page_content);

}




static void webserver_debug_level() {
 if (!webserver_request_auth())
 { return; }

 RESERVE_STRING(page_content, LARGE_STR);
 start_html_page(page_content, FPSTR(INTL_DEBUG_LEVEL));
 debug_outln_info(F("ws: debug level ..."));

 if (server.hasArg("lvl")) {
  const int lvl = server.arg("lvl").toInt();
  if (lvl >= 0 && lvl <= 5) {
   cfg::debug = lvl;
   page_content += F("<h3>");
   page_content += FPSTR(INTL_DEBUG_SETTING_TO);
   page_content += ' ';

   const __FlashStringHelper* lvlText;
   switch (lvl) {
   case DEBUG_ERROR:
    lvlText = F(INTL_ERROR);
    break;
   case DEBUG_WARNING:
    lvlText = F(INTL_WARNING);
    break;
   case DEBUG_MIN_INFO:
    lvlText = F(INTL_MIN_INFO);
    break;
   case DEBUG_MED_INFO:
    lvlText = F(INTL_MED_INFO);
    break;
   case DEBUG_MAX_INFO:
    lvlText = F(INTL_MAX_INFO);
    break;
   default:
    lvlText = F(INTL_NONE);
   }

   page_content += lvlText;
   page_content += F(".</h3>");
  }
 }
 end_html_page(page_content);
}




static void webserver_removeConfig() {
 if (!webserver_request_auth())
 { return; }

 RESERVE_STRING(page_content, LARGE_STR);
 start_html_page(page_content, FPSTR(INTL_DELETE_CONFIG));
 debug_outln_info(F("ws: removeConfig ..."));

 if (server.method() == HTTP_GET) {
  page_content += FPSTR(WEB_REMOVE_CONFIG_CONTENT);

 } else {

  SPIFFS.remove(F("/config.json.old"));
  if (SPIFFS.exists(F("/config.json"))) {
   debug_outln_info(F("removing config.json..."));
   if (SPIFFS.remove(F("/config.json"))) {
    page_content += F("<h3>" INTL_CONFIG_DELETED ".</h3>");
   } else {
    page_content += F("<h3>" INTL_CONFIG_CAN_NOT_BE_DELETED ".</h3>");
   }
  } else {
   page_content += F("<h3>" INTL_CONFIG_NOT_FOUND ".</h3>");
  }
 }
 end_html_page(page_content);
}




static void webserver_reset() {
 if (!webserver_request_auth())
 { return; }

 String page_content;
 page_content.reserve(512);

 start_html_page(page_content, FPSTR(INTL_RESTART_SENSOR));
 debug_outln_info(F("ws: reset ..."));

 if (server.method() == HTTP_GET) {
  page_content += FPSTR(WEB_RESET_CONTENT);
 } else {
  sensor_restart();
 }
 end_html_page(page_content);
}




static void webserver_data_json() {
 String s1;
 unsigned long age = 0;

 debug_outln_info(F("ws: data json..."));
 if (!count_sends) {
  s1 = FPSTR(data_first_part);
  s1 += "]}";
  age = cfg::sending_intervall_ms - msSince(starttime);
  if (age > cfg::sending_intervall_ms) {
   age = 0;
  }
  age = 0 - age;
 } else {
  s1 = last_data_string;
  debug_outln(last_data_string, DEBUG_MED_INFO);
  age = msSince(starttime);
  if (age > cfg::sending_intervall_ms) {
   age = 0;
  }
 }
 String s2 = F(", \"age\":\"");
 s2 += String((long)((age + 500) / 1000));
 s2 += F("\", \"sensordatavalues\"");
 s1.replace(F(", \"sensordatavalues\""), s2);
 server.send(200, FPSTR(TXT_CONTENT_TYPE_JSON), s1);
}




static void webserver_prometheus_endpoint() {
 debug_outln_info(F("ws: prometheus endpoint..."));
 String data_4_prometheus = F("software_version{version=\"" SOFTWARE_VERSION_STR "\",{id}} 1\nuptime_ms{{id}} {up}\nsending_intervall_ms{{id}} {si}\nnumber_of_measurements{{id}} {cs}\n");
 debug_outln_info(F("Parse JSON for Prometheus"));
 String id(F("node=\"" SENSOR_BASENAME));
 id += esp_chipid;
 id += '\"';
 data_4_prometheus.replace("{id}", id);
 data_4_prometheus.replace("{up}", String(msSince(time_point_device_start_ms)));
 data_4_prometheus.replace("{si}", String(cfg::sending_intervall_ms));
 data_4_prometheus.replace("{cs}", String(count_sends));
 DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
 DeserializationError err = deserializeJson(json2data, last_data_string);
 if (!err) {
  for (JsonObject measurement : json2data[FPSTR(JSON_SENSOR_DATA_VALUES)].as<JsonArray>()) {
   data_4_prometheus += measurement["value_type"].as<char*>();
   data_4_prometheus += '{';
   data_4_prometheus += id;
   data_4_prometheus += "} ";
   data_4_prometheus += measurement["value"].as<char*>();
   data_4_prometheus += '\n';
  }
  data_4_prometheus += F("last_sample_age_ms{");
  data_4_prometheus += id;
  data_4_prometheus += "} ";
  data_4_prometheus += String(msSince(starttime));
  data_4_prometheus += '\n';
 } else {
  debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
 }
 debug_outln(data_4_prometheus, DEBUG_MED_INFO);
 server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), data_4_prometheus);
}




static void webserver_images() {
 server.sendHeader(F("Cache-Control"), F("max-age=2592000, public"));

 if (server.arg("name") == F("luftdaten_logo")) {
  debug_outln_info(F("ws: luftdaten_logo..."));
  server.send_P(200, TXT_CONTENT_TYPE_IMAGE_PNG,
   LUFTDATEN_INFO_LOGO_PNG, LUFTDATEN_INFO_LOGO_PNG_SIZE);
 } else {
  webserver_not_found();
 }
}




static void webserver_not_found() {
 last_page_load = millis();
 debug_outln_info(F("ws: not found ..."));
 if (WiFi.status() != WL_CONNECTED) {
  if ((server.uri().indexOf(F("success.html")) != -1) || (server.uri().indexOf(F("detect.html")) != -1)) {
   server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), FPSTR(WEB_IOS_REDIRECT));
  } else {
   sendHttpRedirect();
  }
 } else {
  server.send(404, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), F("Not found."));
 }
}




static void setup_webserver() {
 server.on("/", webserver_root);
 server.on(F("/config"), webserver_config);
 server.on(F("/wifi"), webserver_wifi);
 server.on(F("/values"), webserver_values);
 server.on(F("/status"), webserver_status);
 server.on(F("/generate_204"), webserver_config);
 server.on(F("/fwlink"), webserver_config);
 server.on(F("/debug"), webserver_debug_level);
 server.on(F("/removeConfig"), webserver_removeConfig);
 server.on(F("/reset"), webserver_reset);
 server.on(F("/data.json"), webserver_data_json);
 server.on(F("/metrics"), webserver_prometheus_endpoint);
 server.on(F("/images"), webserver_images);
 server.onNotFound(webserver_not_found);

 debug_outln_info(F("Starting Webserver... "), WiFi.localIP().toString());
 server.begin();
}

static int selectChannelForAp() {
 std::array<int, 14> channels_rssi;
 std::fill(channels_rssi.begin(), channels_rssi.end(), -100);

 for (unsigned i = 0; i < count_wifiInfo; i++) {
  if (wifiInfo[i].RSSI > channels_rssi[wifiInfo[i].channel]) {
   channels_rssi[wifiInfo[i].channel] = wifiInfo[i].RSSI;
  }
 }

 if ((channels_rssi[1] < channels_rssi[6]) && (channels_rssi[1] < channels_rssi[11])) {
  return 1;
 } else if ((channels_rssi[6] < channels_rssi[1]) && (channels_rssi[6] < channels_rssi[11])) {
  return 6;
 } else {
  return 11;
 }
}





void enableWebServerOffline(){
 debug_outln_info(F("Starting WiFiManager"));
 debug_outln_info(F("AP ID: "), String(cfg::fs_ssid));
 debug_outln_info(F("Password: "), String(cfg::fs_pwd));

 WiFi.disconnect(true);

 WiFi.mode(WIFI_AP);
 const IPAddress apIP(192, 168, 4, 1);
 WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
 WiFi.softAP(cfg::fs_ssid, cfg::fs_pwd, selectChannelForAp());

 debug_outln_info(F("AP Password is: "), cfg::fs_pwd);

 DNSServer dnsServer;

 dnsServer.setTTL(0);
 dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
 dnsServer.start(53, "*", apIP);

 setup_webserver();
}




static void wifiConfig() {
 debug_outln_info(F("Starting WiFiManager"));
 debug_outln_info(F("AP ID: "), String(cfg::fs_ssid));
 debug_outln_info(F("Password: "), String(cfg::fs_pwd));

 wificonfig_loop = true;

 WiFi.disconnect(true);
 debug_outln_info(F("scan for wifi networks..."));
 count_wifiInfo = WiFi.scanNetworks(false , true );
 delete [] wifiInfo;
 wifiInfo = new struct_wifiInfo[count_wifiInfo];

 for (int i = 0; i < count_wifiInfo; i++) {
  String SSID;
  uint8_t* BSSID;

  memset(&wifiInfo[i], 0, sizeof(struct_wifiInfo));
#if defined(ESP8266)
  WiFi.getNetworkInfo(i, SSID, wifiInfo[i].encryptionType,
   wifiInfo[i].RSSI, BSSID, wifiInfo[i].channel,
   wifiInfo[i].isHidden);
#else
  WiFi.getNetworkInfo(i, SSID, wifiInfo[i].encryptionType,
   wifiInfo[i].RSSI, BSSID, wifiInfo[i].channel);
#endif
  SSID.toCharArray(wifiInfo[i].ssid, sizeof(wifiInfo[0].ssid));
 }

 WiFi.mode(WIFI_AP);
 const IPAddress apIP(192, 168, 4, 1);
 WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
 WiFi.softAP(cfg::fs_ssid, cfg::fs_pwd, selectChannelForAp());

 debug_outln_info(F("AP Password is: "), cfg::fs_pwd);

 DNSServer dnsServer;

 dnsServer.setTTL(0);
 dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
 dnsServer.start(53, "*", apIP);

 setup_webserver();


 last_page_load = millis();
 while ((millis() - last_page_load) < cfg::time_for_wifi_config + 500) {
  dnsServer.processNextRequest();
  server.handleClient();
#if defined(ESP8266)
  wdt_reset();
  MDNS.update();
#endif
  yield();
 }

 WiFi.softAPdisconnect(true);
 WiFi.mode(WIFI_STA);

 dnsServer.stop();
 delay(100);

 debug_outln_info(FPSTR(DBG_TXT_CONNECTING_TO), cfg::wlanssid);

 WiFi.begin(cfg::wlanssid, cfg::wlanpwd);

 debug_outln_info(F("---- Result Webconfig ----"));
 debug_outln_info(F("WLANSSID: "), cfg::wlanssid);
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_info_bool(F("PPD: "), cfg::ppd_read);
 debug_outln_info_bool(F("SDS: "), cfg::sds_read);
 debug_outln_info_bool(F("PMS: "), cfg::pms_read);
 debug_outln_info_bool(F("HPM: "), cfg::hpm_read);
 debug_outln_info_bool(F("SPS30: "), cfg::sps30_read);
 debug_outln_info_bool(F("DHT: "), cfg::dht_read);
 debug_outln_info_bool(F("DS18B20: "), cfg::ds18b20_read);
 debug_outln_info_bool(F("HTU21D: "), cfg::htu21d_read);
 debug_outln_info_bool(F("BMP: "), cfg::bmp_read);
 debug_outln_info_bool(F("DNMS: "), cfg::dnms_read);
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_info_bool(F("SensorCommunity: "), cfg::send2dusti);
 debug_outln_info_bool(F("Madavi: "), cfg::send2madavi);
 debug_outln_info_bool(F("CSV: "), cfg::send2csv);
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_info_bool(F("Autoupdate: "), cfg::auto_update);
 debug_outln_info_bool(F("Display: "), cfg::has_display);
 debug_outln_info_bool(F("LCD 1602: "), !!lcd_1602);
 debug_outln_info(F("Debug: "), String(cfg::debug));
 wificonfig_loop = false;
}

static void waitForWifiToConnect(int maxRetries) {
 int retryCount = 0;
 while ((WiFi.status() != WL_CONNECTED) && (retryCount < maxRetries)) {
  delay(500);
  debug_out(".", DEBUG_MIN_INFO);
  ++retryCount;
 }
}




static void connectWifi() {
 display_debug(F("Connecting to"), String(cfg::wlanssid));
#if defined(ESP8266)

 system_phy_set_powerup_option(1);

 WiFi.setOutputPower(20.0f);
 WiFi.setSleepMode(WIFI_NONE_SLEEP);
 WiFi.setPhyMode(WIFI_PHY_MODE_11N);
 delay(100);
#endif
 if (WiFi.getAutoConnect()) {
  WiFi.setAutoConnect(false);
 }
 if (!WiFi.getAutoReconnect()) {
  WiFi.setAutoReconnect(true);
 }
 WiFi.mode(WIFI_STA);
 WiFi.hostname(cfg::fs_ssid);
 WiFi.begin(cfg::wlanssid, cfg::wlanpwd);

 debug_outln_info(FPSTR(DBG_TXT_CONNECTING_TO), cfg::wlanssid);

 waitForWifiToConnect(40);
 debug_outln_info(emptyString);
 if (WiFi.status() != WL_CONNECTED) {
  String fss(cfg::fs_ssid);
  display_debug(fss.substring(0, 16), fss.substring(16));
  wifiConfig();
  if (WiFi.status() != WL_CONNECTED) {
   waitForWifiToConnect(20);
   debug_outln_info(emptyString);
  }
 }
 debug_outln_info(F("WiFi connected, IP is: "), WiFi.localIP().toString());
 last_signal_strength = WiFi.RSSI();

 if (MDNS.begin(cfg::fs_ssid)) {
  MDNS.addService("http", "tcp", 80);
  MDNS.addServiceTxt("http", "tcp", "PATH", "/config");
 }
}

#if defined(ESP8266)
BearSSL::X509List x509_dst_root_ca(dst_root_ca_x3);

static void configureCACertTrustAnchor(WiFiClientSecure* client) {
 constexpr time_t fw_built_year = (__DATE__[ 7] - '0') * 1000 + \
         (__DATE__[ 8] - '0') * 100 + \
         (__DATE__[ 9] - '0') * 10 + \
         (__DATE__[10] - '0');
 if (time(nullptr) < (fw_built_year - 1970) * 365 * 24 * 3600) {
  debug_outln_info(F("Time incorrect; Disabling CA verification."));
  client->setInsecure();
 }
 else {
  client->setTrustAnchors(&x509_dst_root_ca);
 }
}
#endif

static WiFiClient* getNewLoggerWiFiClient(const LoggerEntry logger) {

 WiFiClient* _client;
 if (loggerConfigs[logger].session) {
  _client = new WiFiClientSecure;
#if defined(ESP8266)
  static_cast<WiFiClientSecure*>(_client)->setSession(loggerConfigs[logger].session);
  static_cast<WiFiClientSecure*>(_client)->setBufferSizes(1024, TCP_MSS > 1024 ? 2048 : 1024);
  switch (logger) {
  case Loggeraircms:
  case LoggerInflux:
  case LoggerCustom:
  case LoggerFSapp:
   static_cast<WiFiClientSecure*>(_client)->setInsecure();
   break;
  default:
   configureCACertTrustAnchor(static_cast<WiFiClientSecure*>(_client));
  }
#endif
 } else {
  _client = new WiFiClient;
 }
 _client->setTimeout(20000);
 return _client;
}




static unsigned long sendData(const LoggerEntry logger, const String& data, const int pin, const char* host, const char* url) {

 unsigned long start_send = millis();
 const __FlashStringHelper* contentType;
 int result = 0;

 String s_Host(FPSTR(host));
 String s_url(FPSTR(url));

 switch (logger) {
 case Loggeraircms:
  contentType = FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN);
  break;
 case LoggerInflux:
  contentType = FPSTR(TXT_CONTENT_TYPE_INFLUXDB);
  break;
 default:
  contentType = FPSTR(TXT_CONTENT_TYPE_JSON);
  break;
 }

 std::unique_ptr<WiFiClient> client(getNewLoggerWiFiClient(logger));

 HTTPClient http;
 http.setTimeout(20 * 1000);
 http.setUserAgent(SOFTWARE_VERSION + '/' + esp_chipid);
    http.setReuse(false);
 bool send_success = false;
 if (logger == LoggerCustom && (*cfg::user_custom || *cfg::pwd_custom)) {
  http.setAuthorization(cfg::user_custom, cfg::pwd_custom);
 }
 if (logger == LoggerInflux && (*cfg::user_influx || *cfg::pwd_influx)) {
  http.setAuthorization(cfg::user_influx, cfg::pwd_influx);
 }
 if (http.begin(*client, s_Host, loggerConfigs[logger].destport, s_url, !!loggerConfigs[logger].session)) {
  http.addHeader(F("Content-Type"), contentType);
  http.addHeader(F("X-Sensor"), String(F(SENSOR_BASENAME)) + esp_chipid);
  if (pin) {
   http.addHeader(F("X-PIN"), String(pin));
  }

  result = http.POST(data);

  if (result >= HTTP_CODE_OK && result <= HTTP_CODE_ALREADY_REPORTED) {
   debug_outln_info(F("Succeeded - "), s_Host);
   send_success = true;
  } else if (result >= HTTP_CODE_BAD_REQUEST) {
   debug_outln_info(F("Request failed with error: "), String(result));
   debug_outln_info(F("Details:"), http.getString());
  }
  http.end();
 } else {
  debug_outln_info(F("Failed connecting to "), s_Host);
 }

 if (!send_success && result != 0) {
  sendData_error_count++;
  last_sendData_returncode = result;
 }

 return millis() - start_send;
}




static unsigned long sendSD(const String &data, const int pin, const __FlashStringHelper *sensorname, const char *replace_str)
{
 unsigned long start_send = millis();

 if (cfg::send2sd && data.length())
 {
  RESERVE_STRING(data_SD, LARGE_STR);
  data_SD = FPSTR(data_first_part);

  debug_outln_info(F("## Logging data to SD - "), sensorname);
  data_SD += data;
  data_SD.remove(data_SD.length() - 1);
  data_SD.replace(replace_str, emptyString);
  data_SD += "], \"timestamp\":";
  data_SD += "\"";
  data_SD += timestamp;
  data_SD += "\"";
  data_SD += "}";
  Serial.println(data_SD);

  sensor_readings.print(data_SD);
  sensor_readings.print(", ");
  sensor_readings.print(pin);
  sensor_readings.print(", ");
  sensor_readings.print(sensorname);
  sensor_readings.println("/t");

  pcf8575.digitalWrite(LOGGER_LED, HIGH);
  delay(5000);
  pcf8575.digitalWrite(LOGGER_LED, LOW);
  debug_outln_info("sensors data logged successfuly");
 }
 else
 {
  pcf8575.digitalWrite(LOGGER_LED, LOW);
  debug_outln_info("error logging data!!");
 }

 return millis() - start_send;
}




static unsigned long sendCFA(const String &data, const int pin, const __FlashStringHelper *sensorname, const char *replace_str)
{
 unsigned long sum_send_time = 0;

 if (cfg::send2cfa && data.length())
 {
  RESERVE_STRING(data_CFA, LARGE_STR);
  data_CFA = FPSTR(data_first_part);

  debug_outln_info(F("## Sending to sensors.AFRICA - "), sensorname);
  data_CFA += data;
  data_CFA.remove(data_CFA.length() - 1);
  data_CFA.replace(replace_str, emptyString);
  data_CFA += "], \"timestamp\":";
  data_CFA += "\"";
  data_CFA += timestamp;
  data_CFA += "\"";
  data_CFA += "}";
  Serial.println(data_CFA);

  sum_send_time = sendData(LoggerCFA, data_CFA, pin, HOST_CFA, URL_CFA);
 }

 return sum_send_time;
}




static unsigned long sendSensorCommunity(const String& data, const int pin, const __FlashStringHelper* sensorname, const char* replace_str) {
 unsigned long sum_send_time = 0;

 if (cfg::send2dusti && data.length()) {
  RESERVE_STRING(data_sensorcommunity, LARGE_STR);
  data_sensorcommunity = FPSTR(data_first_part);

  debug_outln_info(F("## Sending to sensor.community - "), sensorname);
  data_sensorcommunity += data;
  data_sensorcommunity.remove(data_sensorcommunity.length() - 1);
  data_sensorcommunity.replace(replace_str, emptyString);
  data_sensorcommunity += "]}";
  sum_send_time = sendData(LoggerSensorCommunity, data_sensorcommunity, pin, HOST_SENSORCOMMUNITY, URL_SENSORCOMMUNITY);
 }

 return sum_send_time;
}
# 2693 "F:/EMBEDDED SOFTWARE/CFA/sensors.AFRICA-AQ-sensors-software/airrohr-firmware/airrohr-firmware.ino"
static void create_influxdb_string_from_data(String& data_4_influxdb, const String& data) {
 debug_outln_verbose(F("Parse JSON for influx DB: "), data);
 DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
 DeserializationError err = deserializeJson(json2data, data);
 if (!err) {
  data_4_influxdb += cfg::measurement_name_influx;
  data_4_influxdb += F(",node=" SENSOR_BASENAME);
  data_4_influxdb += esp_chipid + " ";
  for (JsonObject measurement : json2data[FPSTR(JSON_SENSOR_DATA_VALUES)].as<JsonArray>()) {
   data_4_influxdb += measurement["value_type"].as<char*>();
   data_4_influxdb += '=';
   data_4_influxdb += measurement["value"].as<char*>();
   data_4_influxdb += ',';
  }
  if ((unsigned)(data_4_influxdb.lastIndexOf(',') + 1) == data_4_influxdb.length()) {
   data_4_influxdb.remove(data_4_influxdb.length() - 1);
  }

  data_4_influxdb += '\n';
 } else {
  debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
 }
}




static void send_csv(const String& data) {
 DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
 DeserializationError err = deserializeJson(json2data, data);
 debug_outln_info(F("CSV Output: "), data);
 if (!err) {
  String headline = F("Timestamp_ms;");
  String valueline(act_milli);
  valueline += ';';
  for (JsonObject measurement : json2data[FPSTR(JSON_SENSOR_DATA_VALUES)].as<JsonArray>()) {
   headline += measurement["value_type"].as<char*>();
   headline += ';';
   valueline += measurement["value"].as<char*>();
   valueline += ';';
  }
  static bool first_csv_line = true;
  if (first_csv_line) {
   if (headline.length() > 0) {
    headline.remove(headline.length() - 1);
   }
   Serial.println(headline);
   first_csv_line = false;
  }
  if (valueline.length() > 0) {
   valueline.remove(valueline.length() - 1);
  }
  Serial.println(valueline);
 } else {
  debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
 }
}




static void fetchSensorDHT(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DHT22));


 last_value_DHT_T = -128;
 last_value_DHT_H = -1;

 int count = 0;
 const int MAX_ATTEMPTS = 5;
 while ((count++ < MAX_ATTEMPTS)) {
  auto t = dht.readTemperature();
  auto h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
   delay(100);
   t = dht.readTemperature(false);
   h = dht.readHumidity();
  }
  if (isnan(t) || isnan(h)) {
   debug_outln_error(F("DHT11/DHT22 read failed"));
  } else {
   last_value_DHT_T = t;
   last_value_DHT_H = h;
   add_Value2Json(s, F("temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_DHT_T);
   add_Value2Json(s, F("humidity"), FPSTR(DBG_TXT_HUMIDITY), last_value_DHT_H);
   break;
  }
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DHT22));
}





void parseDHTPayloadForDebug(String &dht_data){
 int start_DHT_T = dht_data.indexOf('{');
 int end_DHT_T = dht_data.indexOf('}',start_DHT_T);
 String DHT_T_value = dht_data.substring(start_DHT_T,end_DHT_T);

 DynamicJsonDocument DHT_T_doc(1024);
 deserializeJson(DHT_T_doc,DHT_T_value);
   JsonObject DHT_T_obj = DHT_T_doc.as<JsonObject>();
 String T_value = DHT_T_obj["value"];

 int start_DHT_H = dht_data.indexOf('{',end_DHT_T);
 int end_DHT_H = dht_data.indexOf('}',start_DHT_H);
 String DHT_H_value = dht_data.substring(start_DHT_H,end_DHT_H);

 DynamicJsonDocument DHT_H_doc(1024);
 deserializeJson(DHT_H_doc,DHT_H_value);
   JsonObject DHT_H_obj = DHT_H_doc.as<JsonObject>();
 String H_value = DHT_H_obj["value"];

 last_value_DHT_T = T_value.toFloat();
 last_value_DHT_H = H_value.toFloat();

 debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE),last_value_DHT_T);
 debug_outln_info(FPSTR(DBG_TXT_HUMIDITY), last_value_DHT_H);

}




String fetchSensorDHTFromAtmega(){
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DHT22));
 RESERVE_STRING(s,SMALL_STR);


 atmega328p.println("fetchSensorDHT");
 delay(3000);
 while(atmega328p.available() > 0){
  String dht_data = atmega328p.readString();
  if(dht_data.indexOf("DHT")){
   int last_character = dht_data.lastIndexOf(",");
   s = dht_data.substring(0,(last_character+1));
   parseDHTPayloadForDebug(s);

  }
 }

 pcf8575.digitalWrite(DHT_LED, HIGH);
 delay(5000);
 pcf8575.digitalWrite(DHT_LED, LOW);

 obtain_sendTime();
 pcf8575.digitalWrite(RTC_LED, HIGH);
 delay(5000);
 pcf8575.digitalWrite(RTC_LED, LOW);

 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DHT22));
 return s;
}




static void fetchSensorHTU21D(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_HTU21D));

 const auto t = htu21d.readTemperature();
 const auto h = htu21d.readHumidity();
 if (isnan(t) || isnan(h)) {
  last_value_HTU21D_T = -128.0;
  last_value_HTU21D_H = -1.0;
  debug_outln_error(F("HTU21D read failed"));
 } else {
  last_value_HTU21D_T = t;
  last_value_HTU21D_H = h;
  add_Value2Json(s, F("HTU21D_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_HTU21D_T);
  add_Value2Json(s, F("HTU21D_humidity"), FPSTR(DBG_TXT_HUMIDITY), last_value_HTU21D_H);
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_HTU21D));
}




static void fetchSensorBMP(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_BMP180));

 const auto p = bmp.readPressure();
 const auto t = bmp.readTemperature();
 if (isnan(p) || isnan(t)) {
  last_value_BMP_T = -128.0;
  last_value_BMP_P = -1.0;
  debug_outln_error(F("BMP180 read failed"));
 } else {
  last_value_BMP_T = t;
  last_value_BMP_P = p;
  add_Value2Json(s, F("BMP_pressure"), FPSTR(DBG_TXT_PRESSURE), last_value_BMP_P);
  add_Value2Json(s, F("BMP_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_BMP_T);
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_BMP180));
}




static void fetchSensorSHT3x(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_SHT3X));

 const auto t = sht3x.readTemperature();
 const auto h = sht3x.readHumidity();
 if (isnan(h) || isnan(t)) {
  last_value_SHT3X_T = -128.0;
  last_value_SHT3X_H = -1.0;
  debug_outln_error(F("SHT3X read failed"));
 } else {
  last_value_SHT3X_T = t;
  last_value_SHT3X_H = h;
  add_Value2Json(s, F("SHT3X_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_SHT3X_T);
  add_Value2Json(s, F("SHT3X_humidity"), FPSTR(DBG_TXT_HUMIDITY), last_value_SHT3X_H);
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_SHT3X));
}




static void fetchSensorBMX280(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_BMX280));

 bmx280.takeForcedMeasurement();
 const auto t = bmx280.readTemperature();
 const auto p = bmx280.readPressure();
 const auto h = bmx280.readHumidity();
 if (isnan(t) || isnan(p)) {
  last_value_BMX280_T = -128.0;
  last_value_BMX280_P = -1.0;
  last_value_BME280_H = -1.0;
  debug_outln_error(F("BMP/BME280 read failed"));
 } else {
  last_value_BMX280_T = t;
  last_value_BMX280_P = p;
  if (bmx280.sensorID() == BME280_SENSOR_ID) {
   add_Value2Json(s, F("BME280_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_BMX280_T);
   add_Value2Json(s, F("BME280_pressure"), FPSTR(DBG_TXT_PRESSURE), last_value_BMX280_P);
   last_value_BME280_H = h;
   add_Value2Json(s, F("BME280_humidity"), FPSTR(DBG_TXT_HUMIDITY), last_value_BME280_H);
  } else {
   add_Value2Json(s, F("BMP280_pressure"), FPSTR(DBG_TXT_PRESSURE), last_value_BMX280_P);
   add_Value2Json(s, F("BMP280_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_BMX280_T);
  }
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_BMX280));
}




static void fetchSensorDS18B20(String& s) {
 float t;
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DS18B20));



 const int MAX_ATTEMPTS = 5;
 int count = 0;
 do {
  ds18b20.requestTemperatures();

  t = ds18b20.getTempCByIndex(0);
  ++count;
  debug_outln_info(F("DS18B20 trying...."));
 } while (count < MAX_ATTEMPTS && (isnan(t) || t >= 85.0f || t <= (-127.0f)));

 if (count == MAX_ATTEMPTS) {
  last_value_DS18B20_T = -128.0;
  debug_outln_error(F("DS18B20 read failed"));
 } else {
  last_value_DS18B20_T = t;
  add_Value2Json(s, F("DS18B20_temperature"), FPSTR(DBG_TXT_TEMPERATURE), last_value_DS18B20_T);
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DS18B20));
}




static void fetchSensorSDS(String& s) {

 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_SDS011));

 if (cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS) &&
  msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
  if (is_SDS_running) {
   is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
  }
 } else {
  if (! is_SDS_running) {
   is_SDS_running = SDS_cmd(PmSensorCmd::Start);
  }

  const uint8_t constexpr header_measurement[2] = { 0xAA, 0xC0 };

  while (serialSDS.available() >= 10 &&
     serialSDS.find(header_measurement, sizeof(header_measurement))) {
   uint8_t data[8];
   yield_for_serial_buffer(sizeof(data));
   unsigned r = serialSDS.readBytes(data, sizeof(data));
   if (r == sizeof(data) && SDS_checksum_valid(data)) {
    uint32_t pm25_serial = data[0] | (data[1] << 8);
    uint32_t pm10_serial = data[2] | (data[3] << 8);

    if (msSince(starttime) > (cfg::sending_intervall_ms - READINGTIME_SDS_MS)) {
     sds_pm10_sum += pm10_serial;
     sds_pm25_sum += pm25_serial;
     if (sds_pm10_min > pm10_serial) {
      sds_pm10_min = pm10_serial;
     }
     if (sds_pm10_max < pm10_serial) {
      sds_pm10_max = pm10_serial;
     }
     if (sds_pm25_min > pm25_serial) {
      sds_pm25_min = pm25_serial;
     }
     if (sds_pm25_max < pm25_serial) {
      sds_pm25_max = pm25_serial;
     }
     debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial / 10.0f));
     debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial / 10.0f));
     sds_val_count++;
    }
   }
  }
 }
 if (send_now) {
  last_value_SDS_P1 = -1;
  last_value_SDS_P2 = -1;
  if (sds_val_count > 2) {
   sds_pm10_sum = sds_pm10_sum - sds_pm10_min - sds_pm10_max;
   sds_pm25_sum = sds_pm25_sum - sds_pm25_min - sds_pm25_max;
   sds_val_count = sds_val_count - 2;
  }
  if (sds_val_count > 0) {
   last_value_SDS_P1 = float(sds_pm10_sum) / (sds_val_count * 10.0f);
   last_value_SDS_P2 = float(sds_pm25_sum) / (sds_val_count * 10.0f);
   add_Value2Json(s, F("SDS_P1"), F("PM10:  "), last_value_SDS_P1);
   add_Value2Json(s, F("SDS_P2"), F("PM2.5: "), last_value_SDS_P2);
   debug_outln_info(FPSTR(DBG_TXT_SEP));
   if (sds_val_count < 3) {
    SDS_error_count++;
   }
  }
  else {
   SDS_error_count++;
  }
  sds_pm10_sum = 0;
  sds_pm25_sum = 0;
  sds_val_count = 0;
  sds_pm10_max = 0;
  sds_pm10_min = 20000;
  sds_pm25_max = 0;
  sds_pm25_min = 20000;
  if ((cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {

   if (is_SDS_running) {
    is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
   }
  }
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_SDS011));
}




static void fetchSensorPMS(String& s) {
 char buffer;
 int value;
 int len = 0;
 int pm1_serial = 0;
 int pm10_serial = 0;
 int pm25_serial = 0;
 int checksum_is = 0;
 int checksum_should = 0;
 bool checksum_ok = false;
 int frame_len = 24;

 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_PMSx003));
 if (msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
  if (is_PMS_running) {
   is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
  }
 } else {
  if (! is_PMS_running) {
   is_PMS_running = PMS_cmd(PmSensorCmd::Start);
  }

  while (serialSDS.available() > 0) {
   buffer = serialSDS.read();
   debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO);

   value = int(buffer);
   switch (len) {
   case 0:
    if (value != 66) {
     len = -1;
    };
    break;
   case 1:
    if (value != 77) {
     len = -1;
    };
    break;
   case 2:
    checksum_is = value;
    break;
   case 3:
    frame_len = value + 4;
    break;
   case 10:
    pm1_serial += ( value << 8);
    break;
   case 11:
    pm1_serial += value;
    break;
   case 12:
    pm25_serial = ( value << 8);
    break;
   case 13:
    pm25_serial += value;
    break;
   case 14:
    pm10_serial = ( value << 8);
    break;
   case 15:
    pm10_serial += value;
    break;
   case 22:
    if (frame_len == 24) {
     checksum_should = ( value << 8 );
    };
    break;
   case 23:
    if (frame_len == 24) {
     checksum_should += value;
    };
    break;
   case 30:
    checksum_should = ( value << 8 );
    break;
   case 31:
    checksum_should += value;
    break;
   }
   if ((len > 2) && (len < (frame_len - 2))) { checksum_is += value; }
   len++;
   if (len == frame_len) {
    debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is + 143));
    debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(checksum_should));
    if (checksum_should == (checksum_is + 143)) {
     checksum_ok = true;
    } else {
     len = 0;
    };
    if (checksum_ok && (msSince(starttime) > (cfg::sending_intervall_ms - READINGTIME_SDS_MS))) {
     if ((! isnan(pm1_serial)) && (! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
      pms_pm1_sum += pm1_serial;
      pms_pm10_sum += pm10_serial;
      pms_pm25_sum += pm25_serial;
      if (pms_pm1_min > pm1_serial) {
       pms_pm1_min = pm1_serial;
      }
      if (pms_pm1_max < pm1_serial) {
       pms_pm1_max = pm1_serial;
      }
      if (pms_pm25_min > pm25_serial) {
       pms_pm25_min = pm25_serial;
      }
      if (pms_pm25_max < pm25_serial) {
       pms_pm25_max = pm25_serial;
      }
      if (pms_pm10_min > pm10_serial) {
       pms_pm10_min = pm10_serial;
      }
      if (pms_pm10_max < pm10_serial) {
       pms_pm10_max = pm10_serial;
      }
      debug_outln_verbose(F("PM1 (sec.): "), String(pm1_serial));
      debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial));
      debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial));
      pms_val_count++;
     }
     len = 0;
     checksum_ok = false;
     pm1_serial = 0;
     pm10_serial = 0;
     pm25_serial = 0;
     checksum_is = 0;
    }
   }
   yield();
  }
 }
 if (send_now) {
  last_value_PMS_P0 = -1;
  last_value_PMS_P1 = -1;
  last_value_PMS_P2 = -1;
  if (pms_val_count > 2) {
   pms_pm1_sum = pms_pm1_sum - pms_pm1_min - pms_pm1_max;
   pms_pm10_sum = pms_pm10_sum - pms_pm10_min - pms_pm10_max;
   pms_pm25_sum = pms_pm25_sum - pms_pm25_min - pms_pm25_max;
   pms_val_count = pms_val_count - 2;
  }
  if (pms_val_count > 0) {
   last_value_PMS_P0 = float(pms_pm1_sum) / float(pms_val_count);
   last_value_PMS_P1 = float(pms_pm10_sum) / float(pms_val_count);
   last_value_PMS_P2 = float(pms_pm25_sum) / float(pms_val_count);
   add_Value2Json(s, F("PMS_P0"), F("PM1:   "), last_value_PMS_P0);
   add_Value2Json(s, F("PMS_P1"), F("PM10:  "), last_value_PMS_P1);
   add_Value2Json(s, F("PMS_P2"), F("PM2.5: "), last_value_PMS_P2);
   debug_outln_info(FPSTR(DBG_TXT_SEP));
  }
  pms_pm1_sum = 0;
  pms_pm10_sum = 0;
  pms_pm25_sum = 0;
  pms_val_count = 0;
  pms_pm1_max = 0;
  pms_pm1_min = 20000;
  pms_pm10_max = 0;
  pms_pm10_min = 20000;
  pms_pm25_max = 0;
  pms_pm25_min = 20000;
  if (cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS)) {
   is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
  }
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_PMSx003));
}





void parsePMSPayloadForDebug(String &pms_data){
 int start_PMS_P0 = pms_data.indexOf('{');
 int end_PMS_P0 = pms_data.indexOf('}',start_PMS_P0);
 String PMS_P0_value = pms_data.substring(start_PMS_P0,end_PMS_P0);

 DynamicJsonDocument P0_doc(1024);
 deserializeJson(P0_doc,PMS_P0_value);
   JsonObject P0_obj = P0_doc.as<JsonObject>();
 String P0_value = P0_obj["value"];

 int start_PMS_P1 = pms_data.indexOf('{',end_PMS_P0);
 int end_PMS_P1 = pms_data.indexOf('}',start_PMS_P1);
 String PMS_P1_value = pms_data.substring(start_PMS_P1,end_PMS_P1);

 DynamicJsonDocument P1_doc(1024);
 deserializeJson(P1_doc,PMS_P1_value);
   JsonObject P1_obj = P1_doc.as<JsonObject>();
 String P1_value = P1_obj["value"];

 int start_PMS_P2 = pms_data.indexOf('{',end_PMS_P1);
 int end_PMS_P2 = pms_data.indexOf('}',start_PMS_P2);
 String PMS_P2_value = pms_data.substring(start_PMS_P2,end_PMS_P2);

 DynamicJsonDocument P2_doc(1024);
 deserializeJson(P2_doc,PMS_P2_value);
   JsonObject P2_obj = P2_doc.as<JsonObject>();
 String P2_value = P2_obj["value"];

 last_value_PMS_P0 = P0_value.toFloat();
 last_value_PMS_P1 = P1_value.toFloat();
 last_value_PMS_P2 = P2_value.toFloat();

 debug_outln_info(FPSTR("PM1 (sec.): "), String(last_value_PMS_P0));
 debug_outln_info(FPSTR("PM2.5 (sec.): "), String(last_value_PMS_P2));
 debug_outln_info(FPSTR("PM10 (sec.) : "), String(last_value_PMS_P1));


}




String fetchSensorPMSFromAtmega(){
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_PMSx003));
 RESERVE_STRING(s,SMALL_STR);

 if(send_now){
  atmega328p.println("fetchSensorPMS");
  delay(WARMUPTIME_SDS_MS + READINGTIME_SDS_MS + 2000);
  while(atmega328p.available() > 0){
   String pms_data = atmega328p.readString();
   if(pms_data.indexOf("PMS")){
    int last_character = pms_data.lastIndexOf(",");
    s = pms_data.substring(0,(last_character+1));
    parsePMSPayloadForDebug(s);

   }
  }

  obtain_sendTime();
  pcf8575.digitalWrite(PMS_LED, HIGH);
  delay(5000);
  pcf8575.digitalWrite(PMS_LED, LOW);
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_PMSx003));
 return s;
}




static void fetchSensorHPM(String& s) {
 char buffer;
 int value;
 int len = 0;
 int pm10_serial = 0;
 int pm25_serial = 0;
 int checksum_is = 0;
 int checksum_should = 0;
 bool checksum_ok = false;

 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_HPM));
 if (msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
  if (is_HPM_running) {
   is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
  }
 } else {
  if (! is_HPM_running) {
   is_HPM_running = HPM_cmd(PmSensorCmd::Start);
  }

  while (serialSDS.available() > 0) {
   buffer = serialSDS.read();
   debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO);

   value = int(buffer);
   switch (len) {
   case 0:
    if (value != 66) {
     len = -1;
    };
    break;
   case 1:
    if (value != 77) {
     len = -1;
    };
    break;
   case 2:
    checksum_is = value;
    break;
   case 6:
    pm25_serial += ( value << 8);
    break;
   case 7:
    pm25_serial += value;
    break;
   case 8:
    pm10_serial = ( value << 8);
    break;
   case 9:
    pm10_serial += value;
    break;
   case 30:
    checksum_should = ( value << 8 );
    break;
   case 31:
    checksum_should += value;
    break;
   }
   if (len > 2 && len < 30) { checksum_is += value; }
   len++;
   if (len == 32) {
    debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is + 143));
    debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(checksum_should));
    if (checksum_should == (checksum_is + 143)) {
     checksum_ok = true;
    } else {
     len = 0;
    };
    if (checksum_ok && (long(msSince(starttime)) > (long(cfg::sending_intervall_ms) - long(READINGTIME_SDS_MS)))) {
     if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
      hpm_pm10_sum += pm10_serial;
      hpm_pm25_sum += pm25_serial;
      if (hpm_pm10_min > pm10_serial) {
       hpm_pm10_min = pm10_serial;
      }
      if (hpm_pm10_max < pm10_serial) {
       hpm_pm10_max = pm10_serial;
      }
      if (hpm_pm25_min > pm25_serial) {
       hpm_pm25_min = pm25_serial;
      }
      if (hpm_pm25_max < pm25_serial) {
       hpm_pm25_max = pm25_serial;
      }
      debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial));
      debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial));
      hpm_val_count++;
     }
     len = 0;
     checksum_ok = false;
     pm10_serial = 0;
     pm25_serial = 0;
     checksum_is = 0;
    }
   }
   yield();
  }

 }
 if (send_now) {
  last_value_HPM_P1 = -1.0f;
  last_value_HPM_P2 = -1.0f;
  if (hpm_val_count > 2) {
   hpm_pm10_sum = hpm_pm10_sum - hpm_pm10_min - hpm_pm10_max;
   hpm_pm25_sum = hpm_pm25_sum - hpm_pm25_min - hpm_pm25_max;
   hpm_val_count = hpm_val_count - 2;
  }
  if (hpm_val_count > 0) {
   last_value_HPM_P1 = float(hpm_pm10_sum) / float(hpm_val_count);
   last_value_HPM_P2 = float(hpm_pm25_sum) / float(hpm_val_count);
   add_Value2Json(s, F("HPM_P1"), F("PM2.5: "), last_value_HPM_P1);
   add_Value2Json(s, F("HPM_P2"), F("PM10:  "), last_value_HPM_P2);
   debug_outln_info(FPSTR(DBG_TXT_SEP));
  }
  hpm_pm10_sum = 0;
  hpm_pm25_sum = 0;
  hpm_val_count = 0;
  hpm_pm10_max = 0;
  hpm_pm10_min = 20000;
  hpm_pm25_max = 0;
  hpm_pm25_min = 20000;
  if (cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS)) {
   is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
  }
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_HPM));
}




static void fetchSensorPPD(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_PPD42NS));

 if (msSince(starttime) <= SAMPLETIME_MS) {


  boolean valP1 = digitalRead(PPD_PIN_PM1);
  boolean valP2 = digitalRead(PPD_PIN_PM2);

  if (valP1 == LOW && trigP1 == false) {
   trigP1 = true;
   trigOnP1 = act_micro;
  }

  if (valP1 == HIGH && trigP1 == true) {
   lowpulseoccupancyP1 += act_micro - trigOnP1;
   trigP1 = false;
  }

  if (valP2 == LOW && trigP2 == false) {
   trigP2 = true;
   trigOnP2 = act_micro;
  }

  if (valP2 == HIGH && trigP2 == true) {
   unsigned long durationP2 = act_micro - trigOnP2;
   lowpulseoccupancyP2 += durationP2;
   trigP2 = false;
  }

 }

 if (send_now) {
  auto calcConcentration = [](const float ratio) {

   return (1.1f * ratio * ratio * ratio - 3.8f * ratio * ratio + 520.0f * ratio + 0.62f);
  };

  last_value_PPD_P1 = -1;
  last_value_PPD_P2 = -1;
  float ratio = lowpulseoccupancyP1 / (SAMPLETIME_MS * 10.0f);
  float concentration = calcConcentration(ratio);


  last_value_PPD_P1 = concentration;
  add_Value2Json(s, F("durP1"), F("LPO P10    : "), lowpulseoccupancyP1);
  add_Value2Json(s, F("ratioP1"), F("Ratio PM10%: "), ratio);
  add_Value2Json(s, F("P1"), F("PM10 Count : "), last_value_PPD_P1);

  ratio = lowpulseoccupancyP2 / (SAMPLETIME_MS * 10.0f);
  concentration = calcConcentration(ratio);


  last_value_PPD_P2 = concentration;
  add_Value2Json(s, F("durP2"), F("LPO PM25   : "), lowpulseoccupancyP2);
  add_Value2Json(s, F("ratioP2"), F("Ratio PM25%: "), ratio);
  add_Value2Json(s, F("P2"), F("PM25 Count : "), last_value_PPD_P2);

  debug_outln_info(FPSTR(DBG_TXT_SEP));
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_PPD42NS));
}




static void fetchSensorSPS30(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_SPS30));

 last_value_SPS30_P0 = value_SPS30_P0 / SPS30_measurement_count;
 last_value_SPS30_P2 = value_SPS30_P2 / SPS30_measurement_count;
 last_value_SPS30_P4 = value_SPS30_P4 / SPS30_measurement_count;
 last_value_SPS30_P1 = value_SPS30_P1 / SPS30_measurement_count;
 last_value_SPS30_N05 = value_SPS30_N05 / SPS30_measurement_count;
 last_value_SPS30_N1 = value_SPS30_N1 / SPS30_measurement_count;
 last_value_SPS30_N25 = value_SPS30_N25 / SPS30_measurement_count;
 last_value_SPS30_N4 = value_SPS30_N4 / SPS30_measurement_count;
 last_value_SPS30_N10 = value_SPS30_N10 / SPS30_measurement_count;
 last_value_SPS30_TS = value_SPS30_TS / SPS30_measurement_count;

 add_Value2Json(s, F("SPS30_P0"), F("PM1.0: "), last_value_SPS30_P0);
 add_Value2Json(s, F("SPS30_P2"), F("PM2.5: "), last_value_SPS30_P2);
 add_Value2Json(s, F("SPS30_P4"), F("PM4.0: "), last_value_SPS30_P4);
 add_Value2Json(s, F("SPS30_P1"), F("PM 10: "), last_value_SPS30_P1);
 add_Value2Json(s, F("SPS30_N05"), F("NC0.5: "), last_value_SPS30_N05);
 add_Value2Json(s, F("SPS30_N1"), F("NC1.0: "), last_value_SPS30_N1);
 add_Value2Json(s, F("SPS30_N25"), F("NC2.5: "), last_value_SPS30_N25);
 add_Value2Json(s, F("SPS30_N4"), F("NC4.0: "), last_value_SPS30_N4);
 add_Value2Json(s, F("SPS30_N10"), F("NC10:  "), last_value_SPS30_N10);
 add_Value2Json(s, F("SPS30_TS"), F("TPS:   "), last_value_SPS30_TS);

 debug_outln_info(F("SPS30 read counter: "), String(SPS30_read_counter));
 debug_outln_info(F("SPS30 read error counter: "), String(SPS30_read_error_counter));

 SPS30_measurement_count = 0;
 SPS30_read_counter = 0;
 SPS30_read_error_counter = 0;
 value_SPS30_P0 = 0.0;
 value_SPS30_P2 = 0.0;
 value_SPS30_P4 = 0.0;
 value_SPS30_P1 = 0.0;
 value_SPS30_N05 = 0.0;
 value_SPS30_N1 = 0.0;
 value_SPS30_N25 = 0.0;
 value_SPS30_N4 = 0.0;
 value_SPS30_N10 = 0.0;
 value_SPS30_TS = 0.0;

 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_SPS30));
}





static float readDNMScorrection() {
 char* pEnd = nullptr;

 float r = float(strtol(cfg::dnms_correction, &pEnd, 10));
 if (pEnd && pEnd[0] == '.' && pEnd[1] >= '0' && pEnd[1] <= '9') {
  r += (r >= 0 ? 1.0 : -1.0) * ((pEnd[1] - '0') / 10.0);
 }
 return r;
}

static void fetchSensorDNMS(String& s) {
 static bool dnms_error = false;
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DNMS));
 last_value_dnms_laeq = -1.0;
 last_value_dnms_la_min = -1.0;
 last_value_dnms_la_max = -1.0;

 if (dnms_calculate_leq() != 0) {

  dnms_error = true;
 }
 uint16_t data_ready = 0;
 dnms_error = true;
 for (unsigned i = 0; i < 20; i++) {
  delay(2);
  int16_t ret_dnms = dnms_read_data_ready(&data_ready);
  if ((ret_dnms == 0) && (data_ready != 0)) {
   dnms_error = false;
   break;
  }
 }
 if (!dnms_error) {
  struct dnms_measurements dnms_values;
  if (dnms_read_leq(&dnms_values) == 0) {
   float dnms_corr_value = readDNMScorrection();
   last_value_dnms_laeq = dnms_values.leq_a + dnms_corr_value;
   last_value_dnms_la_min = dnms_values.leq_a_min + dnms_corr_value;
   last_value_dnms_la_max = dnms_values.leq_a_max + dnms_corr_value;
  } else {

   dnms_error = true;
  }
 }
 if (dnms_error) {

  dnms_reset();
  debug_outln_error(F("DNMS read failed"));
 } else {
  add_Value2Json(s, F("DNMS_noise_LAeq"), F("LAeq: "), last_value_dnms_laeq);
  add_Value2Json(s, F("DNMS_noise_LA_min"), F("LA_MIN: "), last_value_dnms_la_min);
  add_Value2Json(s, F("DNMS_noise_LA_max"), F("LA_MAX: "), last_value_dnms_la_max);
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DNMS));
}




static void fetchSensorGPS(String& s) {
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), "GPS");

 if (gps.location.isUpdated()) {
  if (gps.location.isValid()) {
   last_value_GPS_lat = gps.location.lat();
   last_value_GPS_lon = gps.location.lng();
  } else {
   last_value_GPS_lat = -200;
   last_value_GPS_lon = -200;
   debug_outln_verbose(F("Lat/Lng INVALID"));
  }
  if (gps.altitude.isValid()) {
   last_value_GPS_alt = gps.altitude.meters();
   String gps_alt(last_value_GPS_lat);
  } else {
   last_value_GPS_alt = -1000;
   debug_outln_verbose(F("Altitude INVALID"));
  }
  if (gps.date.isValid()) {
   char gps_date[16];
   snprintf_P(gps_date, sizeof(gps_date), PSTR("%02d/%02d/%04d"),
     gps.date.month(), gps.date.day(), gps.date.year());
   last_value_GPS_date = gps_date;
   last_value_GPS_timestamp = gps_date;
  } else {
   debug_outln_verbose(F("Date INVALID"));
  }
  if (gps.time.isValid()) {
   char gps_time[20];
   snprintf_P(gps_time, sizeof(gps_time), PSTR("%02d:%02d:%02d.%02d"),
     gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond());
   last_value_GPS_time = gps_time;
   last_value_GPS_timestamp += "T";
   last_value_GPS_timestamp += gps_time;
  } else {
   debug_outln_verbose(F("Time: INVALID"));
  }
 }

 if (send_now) {
  debug_outln_info(F("Lat: "), String(last_value_GPS_lat, 6));
  debug_outln_info(F("Lng: "), String(last_value_GPS_lon, 6));
  debug_outln_info(F("Date: "), last_value_GPS_date);
  debug_outln_info(F("Time "), last_value_GPS_time);

  add_Value2Json(s, F("GPS_lat"), String(last_value_GPS_lat, 6));
  add_Value2Json(s, F("GPS_lon"), String(last_value_GPS_lon, 6));
  add_Value2Json(s, F("GPS_height"), F("Altitude: "), last_value_GPS_alt);
  add_Value2Json(s, F("GPS_timestamp"), last_value_GPS_timestamp);
  debug_outln_info(FPSTR(DBG_TXT_SEP));

 }

 if ( count_sends > 0 && gps.charsProcessed() < 10) {
  debug_outln_error(F("No GPS data received: check wiring"));
  gps_init_failed = true;
 }

 debug_outln_verbose(FPSTR(DBG_TXT_END_READING), "GPS");
}





void parseGPSPayloadForDebug(String &gps_data){


 int start_GPS_lat = gps_data.indexOf('{');
 int end_GPS_lat = gps_data.indexOf('}',start_GPS_lat);
 String GPS_lat_value = gps_data.substring(start_GPS_lat,end_GPS_lat);

 DynamicJsonDocument Lat_doc(1024);
 deserializeJson(Lat_doc,GPS_lat_value);
   JsonObject Lat_obj = Lat_doc.as<JsonObject>();
 String Lat_value = Lat_obj["value"];


 int start_GPS_lon = gps_data.indexOf('{',end_GPS_lat);
 int end_GPS_lon = gps_data.indexOf('}',start_GPS_lon);
 String GPS_lon_value = gps_data.substring(start_GPS_lon,end_GPS_lon);

 DynamicJsonDocument Lon_doc(1024);
 deserializeJson(Lon_doc,GPS_lon_value);
   JsonObject Lon_obj = Lon_doc.as<JsonObject>();
 String Lon_value = Lon_obj["value"];


 int start_GPS_alt = gps_data.indexOf('{',end_GPS_lon);
 int end_GPS_alt = gps_data.indexOf('}',start_GPS_alt);
 String GPS_alt_value = gps_data.substring(start_GPS_alt,end_GPS_alt);

 DynamicJsonDocument Alt_doc(1024);
 deserializeJson(Alt_doc,GPS_alt_value);
   JsonObject Alt_obj = Alt_doc.as<JsonObject>();
 String Alt_value = Alt_obj["value"];


 int start_GPS_date = gps_data.indexOf('{',end_GPS_alt);
 int end_GPS_date= gps_data.indexOf('}',start_GPS_date);
 String GPS_date_value = gps_data.substring(start_GPS_date,end_GPS_date);

 DynamicJsonDocument Date_doc(1024);
 deserializeJson(Date_doc,GPS_date_value);
   JsonObject Date_obj = Date_doc.as<JsonObject>();
 String Date_value = Date_obj["value"];


 int start_GPS_time = gps_data.indexOf('{',end_GPS_date);
 int end_GPS_time= gps_data.indexOf('}',start_GPS_time);
 String GPS_time_value = gps_data.substring(start_GPS_time,end_GPS_time);

 DynamicJsonDocument Time_doc(1024);
 deserializeJson(Time_doc,GPS_time_value);
   JsonObject Time_obj = Time_doc.as<JsonObject>();
 String Time_value = Time_obj["value"];

 last_value_GPS_lat = Lat_value.toFloat();
 last_value_GPS_lon = Lon_value.toFloat();
 last_value_GPS_alt = Alt_value.toFloat();
 last_value_GPS_date = Date_value;
 last_value_GPS_time = Time_value;

 debug_outln_info(F("Lat: "), String(last_value_GPS_lat, 6));
 debug_outln_info(F("Lng: "), String(last_value_GPS_lon, 6));
 debug_outln_info(F("Date: "), last_value_GPS_date);
 debug_outln_info(F("Time "), last_value_GPS_time);
}





String fetchSensorGPSFromAtmega(){
 debug_outln_verbose(FPSTR(DBG_TXT_START_READING), "GPS");
 RESERVE_STRING(s,SMALL_STR);


 atmega328p.println("fetchSensorGPS");
 delay(3000);
 while(atmega328p.available() > 0){
  String gps_data = atmega328p.readString();
  if(gps_data.indexOf("GPS")){
   int last_character = gps_data.lastIndexOf(",");
   s = gps_data.substring(0,(last_character+1));
   parseGPSPayloadForDebug(s);

  }
 }

 obtain_sendTime();
 pcf8575.digitalWrite(GPS_LED, HIGH);
 delay(5000);
 pcf8575.digitalWrite(GPS_LED, LOW);

 debug_outln_info(FPSTR(DBG_TXT_SEP));
 return s;
}




void init_PCF8575() {

 Serial.begin(115200);

 pcf8575.pinMode(GPS_LED, OUTPUT);
 pcf8575.pinMode(LOGGER_LED, OUTPUT);
 pcf8575.pinMode(RTC_LED, OUTPUT);
 pcf8575.pinMode(MIC_LED, OUTPUT);
 pcf8575.pinMode(PMS_LED, OUTPUT);
 pcf8575.pinMode(DHT_LED, OUTPUT);
 pcf8575.pinMode(LOGGER_SWITCH, INPUT);
}




void init_SPH0645(){
 rx_buf_cnt = 0;
 pinMode(I2SI_WS, OUTPUT);
 pinMode(I2SI_BCK, OUTPUT);
 pinMode(I2SI_DATA, INPUT);

 slc_init();
 i2s_init();
}




void Reinit_SPH0645(){
 pinMode(I2SI_WS, OUTPUT);
 pinMode(I2SI_BCK, OUTPUT);
 pinMode(I2SI_DATA, INPUT);

 i2s_init();
}






void fetchSensorSPH0645(String& s){

 if (rx_buf_flag) {
    for (int x = 0; x < SLC_BUF_LEN; x++) {
      if (i2s_slc_buf_pntr[rx_buf_idx][x] > 0) {
   float sensor_value = convert(i2s_slc_buf_pntr[rx_buf_idx][x]);
   value_SPH0645 = convert_to_dB(sensor_value);
    }
  else{
   debug_outln_error(F("No Mic Value available"));
   Reinit_SPH0645();
   delay(1000);
  }
    }
    rx_buf_flag = false;
  }

  if(send_now){
   debug_outln_info(F("noise_Leq: "), String(value_SPH0645));
   add_Value2Json(s, F("noise_Leq"), String(value_SPH0645));
   obtain_sendTime();
   pcf8575.digitalWrite(MIC_LED, HIGH);
   delay(5000);
   pcf8575.digitalWrite(MIC_LED, LOW);
  }

}




void init_RTC()
{
 pinMode(RTC_PIN_SDA, OUTPUT);
 pinMode(RTC_PIN_SCL, OUTPUT);
 if (!rtc.isrunning())
 {

   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


 }
 else
 {
  pcf8575.digitalWrite(RTC_LED, HIGH);
  delay(5000);
  pcf8575.digitalWrite(RTC_LED, LOW);
 }

}

void obtain_sendTime()
{
 char buf[40];
 DateTime now = rtc.now();
 sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02dZ", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
 timestamp = buf;
}





static bool fwDownloadStream(WiFiClientSecure& client, const String& url, Stream* ostream) {

 HTTPClient http;
 int bytes_written = -1;

 http.setTimeout(20 * 1000);
 http.setUserAgent(SOFTWARE_VERSION + ' ' + esp_chipid + ' ' + SDS_version_date() + ' ' +
     String(cfg::current_lang) + ' ' + String(CURRENT_LANG) + ' ' +
     String(cfg::use_beta ? F("BETA") : F("")));
    http.setReuse(false);

 debug_outln_verbose(F("HTTP GET: "), String(FPSTR(FW_DOWNLOAD_HOST)) + ':' + String(FW_DOWNLOAD_PORT) + url);

 if (http.begin(client, FPSTR(FW_DOWNLOAD_HOST), FW_DOWNLOAD_PORT, url)) {
  int r = http.GET();
  debug_outln_verbose(F("GET r: "), String(r));
  last_update_returncode = r;
  if (r == HTTP_CODE_OK) {
   bytes_written = http.writeToStream(ostream);
  }
  http.end();
 }

 if (bytes_written > 0)
  return true;

 return false;
}

static bool fwDownloadStreamFile(WiFiClientSecure& client, const String& url, const String& fname) {

 String fname_new(fname);
 fname_new += F(".new");
 bool downloadSuccess = false;

 File fwFile = SPIFFS.open(fname_new, "w");
 if (fwFile) {
  downloadSuccess = fwDownloadStream(client, url, &fwFile);
  fwFile.close();
  if (downloadSuccess) {
   SPIFFS.remove(fname);
   SPIFFS.rename(fname_new, fname);
   debug_outln_info(F("Success downloading: "), url);
  }
 }

 if (downloadSuccess)
  return true;

 SPIFFS.remove(fname_new);
 return false;
}

#if defined(ESP8266)
static bool launchUpdateLoader(const String& md5) {

 File loaderFile = SPIFFS.open(F("/loader.bin"), "r");
 if (!loaderFile) {
  return false;
 }

 if (!Update.begin(loaderFile.size(), U_FLASH)) {
  return false;
 }

 if (md5.length() && !Update.setMD5(md5.c_str())) {
  return false;
 }

 if (Update.writeStream(loaderFile) != loaderFile.size()) {
  return false;
 }
 loaderFile.close();

 if (!Update.end()) {
  return false;
 }

 debug_outln_info(F("Erasing SDK config."));
 ESP.eraseConfig();

 sensor_restart();
 return true;
}
#endif

static void twoStageOTAUpdate() {

 if (!cfg::auto_update) return;

#if defined(ESP8266)
 debug_outln_info(F("twoStageOTAUpdate"));

 String lang_variant(cfg::current_lang);
 if (lang_variant.length() != 2) {
  lang_variant = CURRENT_LANG;
 }
 lang_variant.toLowerCase();

 String fetch_name(F(OTA_BASENAME "/update/latest_"));
 if (cfg::use_beta) {
  fetch_name = F(OTA_BASENAME "/beta/latest_");
 }
 fetch_name += lang_variant;
 fetch_name += F(".bin");

 WiFiClientSecure client;
 BearSSL::Session clientSession;

 client.setBufferSizes(1024, TCP_MSS > 1024 ? 2048 : 1024);
 client.setSession(&clientSession);
 configureCACertTrustAnchor(&client);

 String fetch_md5_name(fetch_name);
 fetch_md5_name += F(".md5");

 StreamString newFwmd5;
 if (!fwDownloadStream(client, fetch_md5_name, &newFwmd5))
  return;

 newFwmd5.trim();
 if (newFwmd5 == ESP.getSketchMD5()) {
  display_debug(FPSTR(DBG_TXT_UPDATE), FPSTR(DBG_TXT_UPDATE_NO_UPDATE));
  debug_outln_verbose(F("No newer version available."));
  return;
 }

 debug_outln_info(F("Update md5: "), newFwmd5);
 debug_outln_info(F("Sketch md5: "), ESP.getSketchMD5());


 WiFiUDP::stopAll();
 WiFiClient::stopAllExcept(&client);
 delay(100);

 String firmware_name(F("/firmware.bin"));
 String firmware_md5(F("/firmware.bin.md5"));
 String loader_name(F("/loader.bin"));
 if (!fwDownloadStreamFile(client, fetch_name, firmware_name))
  return;
 if (!fwDownloadStreamFile(client, fetch_md5_name, firmware_md5))
  return;
 if (!fwDownloadStreamFile(client, FPSTR(FW_2ND_LOADER_URL), loader_name))
  return;

 File fwFile = SPIFFS.open(firmware_name, "r");
 if (!fwFile) {
  SPIFFS.remove(firmware_name);
  SPIFFS.remove(firmware_md5);
  debug_outln_error(F("Failed reopening fw file.."));
  return;
 }
 size_t fwSize = fwFile.size();
 MD5Builder md5;
 md5.begin();
 md5.addStream(fwFile, fwSize);
 md5.calculate();
 fwFile.close();
 String md5String = md5.toString();


 if (fwSize < (1<<17) || (fwSize % 16 != 0) || newFwmd5 != md5String) {
  debug_outln_info(F("FW download failed validation.. deleting"));
  SPIFFS.remove(firmware_name);
  SPIFFS.remove(firmware_md5);
  return;
 }

 StreamString loaderMD5;
 if (!fwDownloadStream(client, String(FPSTR(FW_2ND_LOADER_URL)) + F(".md5"), &loaderMD5))
  return;

 loaderMD5.trim();

 debug_outln_info(F("launching 2nd stage"));
 if (!launchUpdateLoader(loaderMD5)) {
  debug_outln_error(FPSTR(DBG_TXT_UPDATE_FAILED));
  display_debug(FPSTR(DBG_TXT_UPDATE), FPSTR(DBG_TXT_UPDATE_FAILED));
  SPIFFS.remove(firmware_name);
  SPIFFS.remove(firmware_md5);
  return;
 }
#endif
}

static String displayGenerateFooter(unsigned int screen_count) {
 String display_footer;
 for (unsigned int i = 0; i < screen_count; ++i) {
  display_footer += (i != (next_display_count % screen_count)) ? " . " : " o ";
 }
 return display_footer;
}




static void display_values() {
 float t_value = -128.0;
 float h_value = -1.0;
 float p_value = -1.0;
 String t_sensor, h_sensor, p_sensor;
 float pm01_value = -1.0;
 float pm04_value = -1.0;
 float pm10_value = -1.0;
 float pm25_value = -1.0;
 String pm10_sensor;
 String pm25_sensor;
 float nc005_value = -1.0;
 float nc010_value = -1.0;
 float nc025_value = -1.0;
 float nc040_value = -1.0;
 float nc100_value = -1.0;
 float la_eq_value = -1.0;
 float la_max_value = -1.0;
 float la_min_value = -1.0;
 String la_sensor;
 float tps_value = -1.0;
 double lat_value = -200.0;
 double lon_value = -200.0;
 double alt_value = -1000.0;
 String display_header;
 String display_lines[3] = { "", "", ""};
 uint8_t screen_count = 0;
 uint8_t screens[8];
 int line_count = 0;
 debug_outln_info(F("output values to display..."));
 if (cfg::ppd_read) {
  pm10_value = last_value_PPD_P1;
  pm10_sensor = FPSTR(SENSORS_PPD42NS);
  pm25_value = last_value_PPD_P2;
  pm25_sensor = FPSTR(SENSORS_PPD42NS);
 }
 if (cfg::pms_read) {
  pm10_value = last_value_PMS_P1;
  pm10_sensor = FPSTR(SENSORS_PMSx003);
  pm25_value = last_value_PMS_P2;
  pm25_sensor = FPSTR(SENSORS_PMSx003);
 }
 if (cfg::hpm_read) {
  pm10_value = last_value_HPM_P1;
  pm10_sensor = FPSTR(SENSORS_HPM);
  pm25_value = last_value_HPM_P2;
  pm25_sensor = FPSTR(SENSORS_HPM);
 }
 if (cfg::sps30_read) {
  pm10_sensor = FPSTR(SENSORS_SPS30);
  pm25_sensor = FPSTR(SENSORS_SPS30);
  pm01_value = last_value_SPS30_P0;
  pm25_value = last_value_SPS30_P2;
  pm04_value = last_value_SPS30_P4;
  pm10_value = last_value_SPS30_P1;
  nc005_value = last_value_SPS30_N05;
  nc010_value = last_value_SPS30_N1;
  nc025_value = last_value_SPS30_N25;
  nc040_value = last_value_SPS30_N4;
  nc100_value = last_value_SPS30_N10;
  tps_value = last_value_SPS30_TS;
 }
 if (cfg::sds_read) {
  pm10_sensor = pm25_sensor = FPSTR(SENSORS_SDS011);
  pm10_value = last_value_SDS_P1;
  pm25_value = last_value_SDS_P2;
 }
 if (cfg::dht_read) {
  t_sensor = h_sensor = FPSTR(SENSORS_DHT22);
  t_value = last_value_DHT_T;
  h_value = last_value_DHT_H;
 }
 if (cfg::ds18b20_read) {
  t_sensor = FPSTR(SENSORS_DS18B20);
  t_value = last_value_DS18B20_T;
 }
 if (cfg::htu21d_read) {
  h_sensor = t_sensor = FPSTR(SENSORS_HTU21D);
  t_value = last_value_HTU21D_T;
  h_value = last_value_HTU21D_H;
 }
 if (cfg::bmp_read) {
  t_sensor = h_sensor = FPSTR(SENSORS_BMP180);
  t_value = last_value_BMP_T;
  p_value = last_value_BMP_P;
 }
 if (cfg::bmx280_read) {
  t_sensor = p_sensor = FPSTR(SENSORS_BMX280);
  t_value = last_value_BMX280_T;
  p_value = last_value_BMX280_P;
  if (bmx280.sensorID() == BME280_SENSOR_ID) {
   h_sensor = FPSTR(SENSORS_BMX280);
   h_value = last_value_BME280_H;
  }
 }
 if (cfg::sht3x_read) {
  h_sensor = t_sensor = FPSTR(SENSORS_SHT3X);
  t_value = last_value_SHT3X_T;
  h_value = last_value_SHT3X_H;
 }
 if (cfg::dnms_read) {
  la_sensor = FPSTR(SENSORS_DNMS);
  la_eq_value = last_value_dnms_laeq;
  la_max_value = last_value_dnms_la_max;
  la_min_value = last_value_dnms_la_min;
 }
 if (cfg::gps_read) {
  lat_value = last_value_GPS_lat;
  lon_value = last_value_GPS_lon;
  alt_value = last_value_GPS_alt;
 }
 if (cfg::ppd_read || cfg::pms_read || cfg::hpm_read || cfg::sds_read) {
  screens[screen_count++] = 1;
 }
 if (cfg::sps30_read) {
  screens[screen_count++] = 2;
 }
 if (cfg::dht_read || cfg::ds18b20_read || cfg::htu21d_read || cfg::bmp_read || cfg::bmx280_read || cfg::sht3x_read) {
  screens[screen_count++] = 3;
 }
 if (cfg::gps_read) {
  screens[screen_count++] = 4;
 }
 if (cfg::dnms_read) {
  screens[screen_count++] = 5;
 }
 if (cfg::display_wifi_info) {
  screens[screen_count++] = 6;
 }
 if (cfg::display_device_info) {
  screens[screen_count++] = 7;
 }


 if (cfg::has_display || cfg::has_sh1106 || lcd_2004) {
  switch (screens[next_display_count % screen_count]) {
  case 1:
   display_header = pm25_sensor;
   if (pm25_sensor != pm10_sensor) {
    display_header += " / " + pm10_sensor;
   }
   display_lines[0] = std::move(tmpl(F("PM2.5: {v} µg/m³"), check_display_value(pm25_value, -1, 1, 6)));
   display_lines[1] = std::move(tmpl(F("PM10: {v} µg/m³"), check_display_value(pm10_value, -1, 1, 6)));
   display_lines[2] = emptyString;
   break;
  case 2:
   display_header = FPSTR(SENSORS_SPS30);
   display_lines[0] = "PM: " + check_display_value(pm01_value, -1, 1, 4) + " " + check_display_value(pm25_value, -1, 1, 4) + " " + check_display_value(pm04_value, -1, 1, 4) + " " + check_display_value(pm10_value, -1, 1, 4);
   display_lines[1] = "NC: " + check_display_value(nc005_value, -1, 0, 3) + " " + check_display_value(nc010_value, -1, 0, 3) + " " + check_display_value(nc025_value, -1, 0, 3) + " " + check_display_value(nc040_value, -1, 0, 3) + " " + check_display_value(nc100_value, -1, 0, 3);
   display_lines[2] = std::move(tmpl(F("TPS: {v} µm"), check_display_value(tps_value, -1, 2, 5)));
   break;
  case 3:
   display_header = t_sensor;
   if (h_sensor && t_sensor != h_sensor) {
    display_header += " / " + h_sensor;
   }
   if ((h_sensor && p_sensor && (h_sensor != p_sensor)) || (h_sensor == "" && p_sensor && (t_sensor != p_sensor))) {
    display_header += " / " + p_sensor;
   }
   if (t_sensor != "") { display_lines[line_count] = "Temp.: "; display_lines[line_count] += check_display_value(t_value, -128, 1, 6); display_lines[line_count++] += " °C"; }
   if (h_sensor != "") { display_lines[line_count] = "Hum.:  "; display_lines[line_count] += check_display_value(h_value, -1, 1, 6); display_lines[line_count++] += " %"; }
   if (p_sensor != "") { display_lines[line_count] = "Pres.: "; display_lines[line_count] += check_display_value(p_value / 100, (-1 / 100.0), 1, 6); display_lines[line_count++] += " hPa"; }
   while (line_count < 3) { display_lines[line_count++] = emptyString; }
   break;
  case 4:
   display_header = "NEO6M";
   display_lines[0] = "Lat: ";
   display_lines[0] += check_display_value(lat_value, -200.0, 6, 10);
   display_lines[1] = "Lon: ";
   display_lines[1] += check_display_value(lon_value, -200.0, 6, 10);
   display_lines[2] = "Alt: ";
   display_lines[2] += check_display_value(alt_value, -1000.0, 2, 10);
   break;
  case 5:
   display_header = FPSTR(SENSORS_DNMS);
   display_lines[0] = std::move(tmpl(F("LAeq: {v} db(A)"), check_display_value(la_eq_value, -1, 1, 6)));
   display_lines[1] = std::move(tmpl(F("LA_max: {v} db(A)"), check_display_value(la_max_value, -1, 1, 6)));
   display_lines[2] = std::move(tmpl(F("LA_min: {v} db(A)"), check_display_value(la_min_value, -1, 1, 6)));
   break;
  case 6:
   display_header = F("Wifi info");
   display_lines[0] = "IP: "; display_lines[0] += WiFi.localIP().toString();
   display_lines[1] = "SSID: "; display_lines[1] += WiFi.SSID();
   display_lines[2] = std::move(tmpl(F("Signal: {v} %"), String(calcWiFiSignalQuality(last_signal_strength))));
   break;
  case 7:
   display_header = F("Device Info");
   display_lines[0] = "ID: "; display_lines[0] += esp_chipid;
   display_lines[1] = "FW: "; display_lines[1] += SOFTWARE_VERSION;
   display_lines[2] = F("Measurements: "); display_lines[2] += String(count_sends);
   break;
  }

  if (cfg::has_display) {
   display.clear();
   display.displayOn();
   display.setTextAlignment(TEXT_ALIGN_CENTER);
   display.drawString(64, 1, display_header);
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   display.drawString(0, 16, display_lines[0]);
   display.drawString(0, 28, display_lines[1]);
   display.drawString(0, 40, display_lines[2]);
   display.setTextAlignment(TEXT_ALIGN_CENTER);
   display.drawString(64, 52, displayGenerateFooter(screen_count));
   display.display();
  }
  if (cfg::has_sh1106) {
   display_sh1106.clear();
   display_sh1106.displayOn();
   display_sh1106.setTextAlignment(TEXT_ALIGN_CENTER);
   display_sh1106.drawString(64, 1, display_header);
   display_sh1106.setTextAlignment(TEXT_ALIGN_LEFT);
   display_sh1106.drawString(0, 16, display_lines[0]);
   display_sh1106.drawString(0, 28, display_lines[1]);
   display_sh1106.drawString(0, 40, display_lines[2]);
   display_sh1106.setTextAlignment(TEXT_ALIGN_CENTER);
   display_sh1106.drawString(64, 52, displayGenerateFooter(screen_count));
   display_sh1106.display();
  }
  if (lcd_2004) {
   display_header = std::move(String((next_display_count % screen_count) + 1) + '/' + String(screen_count) + ' ' + display_header);
   display_lines[0].replace(" µg/m³", emptyString);
   display_lines[0].replace("°", String(char(223)));
   display_lines[1].replace(" µg/m³", emptyString);
   lcd_2004->clear();
   lcd_2004->setCursor(0, 0);
   lcd_2004->print(display_header);
   lcd_2004->setCursor(0, 1);
   lcd_2004->print(display_lines[0]);
   lcd_2004->setCursor(0, 2);
   lcd_2004->print(display_lines[1]);
   lcd_2004->setCursor(0, 3);
   lcd_2004->print(display_lines[2]);
  }
 }






 if (lcd_1602) {
  switch (screens[next_display_count % screen_count]) {
  case 1:
   display_lines[0] = "PM2.5: ";
   display_lines[0] += check_display_value(pm25_value, -1, 1, 6);
   display_lines[1] = "PM10:  ";
   display_lines[1] += check_display_value(pm10_value, -1, 1, 6);
   break;
  case 2:
   display_lines[0] = "PM1.0: ";
   display_lines[0] += check_display_value(pm01_value, -1, 1, 4);
   display_lines[1] = "PM4: ";
   display_lines[1] += check_display_value(pm04_value, -1, 1, 4);
   break;
  case 3:
   display_lines[0] = std::move(tmpl(F("T: {v} °C"), check_display_value(t_value, -128, 1, 6)));
   display_lines[1] = std::move(tmpl(F("H: {v} %"), check_display_value(h_value, -1, 1, 6)));
   break;
  case 4:
   display_lines[0] = "Lat: ";
   display_lines[0] += check_display_value(lat_value, -200.0, 6, 11);
   display_lines[1] = "Lon: ";
   display_lines[1] += check_display_value(lon_value, -200.0, 6, 11);
   break;
  case 5:
   display_lines[0] = std::move(tmpl(F("LAeq: {v} db(A)"), check_display_value(la_eq_value, -1, 1, 6)));
   display_lines[1] = std::move(tmpl(F("LA_max: {v} db(A)"), check_display_value(la_max_value, -1, 1, 6)));
   break;
  case 6:
   display_lines[0] = WiFi.localIP().toString();
   display_lines[1] = WiFi.SSID();
   break;
  case 7:
   display_lines[0] = "ID: ";
   display_lines[0] += esp_chipid;
   display_lines[1] = "FW: ";
   display_lines[1] += SOFTWARE_VERSION;
   break;
  }

  display_lines[0].replace("°", String(char(223)));

  lcd_1602->clear();
  lcd_1602->setCursor(0, 0);
  lcd_1602->print(display_lines[0]);
  lcd_1602->setCursor(0, 1);
  lcd_1602->print(display_lines[1]);
 }
 yield();
 next_display_count++;
}




static void init_display() {
 display.init();
 display_sh1106.init();
 if (cfg::has_flipped_display) {
  display.flipScreenVertically();
  display_sh1106.flipScreenVertically();
 }
}




static void init_lcd() {
    if (cfg::has_lcd1602) {
        lcd_1602 = new LiquidCrystal_I2C(0x3f, 16, 2);
    }
 else if (cfg::has_lcd1602_27) {
        lcd_1602 = new LiquidCrystal_I2C(0x27, 16, 2);
 }
    if (lcd_1602) {
  lcd_1602->init();
  lcd_1602->backlight();
 }

 if (cfg::has_lcd2004) {
  lcd_2004 = new LiquidCrystal_I2C(0x3f, 20, 4);
 }
 else if (cfg::has_lcd2004_27) {
  lcd_2004 = new LiquidCrystal_I2C(0x27, 20, 4);
 }
 if (lcd_2004) {
  lcd_2004->init();
  lcd_2004->backlight();
 }
}




static bool initBMX280(char addr) {
 debug_out(String(F("Trying BMP280/BME280 sensor on ")) + String(addr, HEX), DEBUG_MIN_INFO);

 if (bmx280.begin(addr)) {
  debug_outln_info(FPSTR(DBG_TXT_FOUND));
  bmx280.setSampling(
   BMX280::MODE_FORCED,
   BMX280::SAMPLING_X1,
   BMX280::SAMPLING_X1,
   BMX280::SAMPLING_X1);
  return true;
 } else {
  debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));
  return false;
 }
}




static void initSPS30() {
 char serial[SPS_MAX_SERIAL_LEN];
 debug_out(F("Trying SPS30 sensor on 0x69H "), DEBUG_MIN_INFO);
 sps30_reset();
 delay(200);
 if ( sps30_get_serial(serial) != 0 ) {
  debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));

  debug_outln_info(F("Check SPS30 wiring"));
  sps30_init_failed = true;
  return;
 }
 debug_outln_info(F(" ... found, Serial-No.: "), String(serial));
 if (sps30_set_fan_auto_cleaning_interval(SPS30_AUTO_CLEANING_INTERVAL) != 0) {
  debug_outln_error(F("setting of Auto Cleaning Intervall SPS30 failed!"));
  sps30_init_failed = true;
  return;
 }
 delay(100);
 if (sps30_start_measurement() != 0) {
  debug_outln_error(F("SPS30 error starting measurement"));
  sps30_init_failed = true;
  return;
 }
}




static void init_SD()
{
 serialSD.begin(115200);
 debug_outln_info("Micro SD Logger initializing...");

 if (!SD.begin(SD_chipSelect)) {
  debug_outln_info("Check SD card");
  return;
 }
 debug_outln_info("Card initialized.");

}




static void initDNMS() {
 char dnms_version[DNMS_MAX_VERSION_LEN + 1];

 debug_out(F("Trying DNMS sensor on 0x55H "), DEBUG_MIN_INFO);
 dnms_reset();
 delay(1000);
 if (dnms_read_version(dnms_version) != 0) {
  debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));
  debug_outln_error(F("Check DNMS wiring"));
  dnms_init_failed = true;
 } else {
  dnms_version[DNMS_MAX_VERSION_LEN] = 0;
  debug_outln_info(FPSTR(DBG_TXT_FOUND), String(": ") + String(dnms_version));
 }
}

static void powerOnTestSensors() {
 if (cfg::wifi_enabled)
 {
  debug_outln_info(F("WIFI ENABLED..."));
 }
 else
 {
  debug_outln_info(F("WIFI DISABLED..."));
 }

 if (cfg::ppd_read) {
  pinMode(PPD_PIN_PM1, INPUT_PULLUP);
  pinMode(PPD_PIN_PM2, INPUT_PULLUP);
  debug_outln_info(F("Read PPD..."));
 }

 if (cfg::sds_read) {
  debug_outln_info(F("Read SDS...: "), SDS_version_date());
  SDS_cmd(PmSensorCmd::ContinuousMode);
  delay(100);
  debug_outln_info(F("Stopping SDS011..."));
  is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
 }

 if (cfg::pms_read) {
  debug_outln_info(F("Read PMS(1,3,5,6,7)003..."));
  PMS_cmd(PmSensorCmd::Start);
  delay(100);
  PMS_cmd(PmSensorCmd::ContinuousMode);
  delay(100);
  debug_outln_info(F("Stopping PMS..."));
  is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
  pcf8575.digitalWrite(PMS_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(PMS_LED, LOW);
 }

 if (cfg::hpm_read) {
  debug_outln_info(F("Read HPM..."));
  HPM_cmd(PmSensorCmd::Start);
  delay(100);
  HPM_cmd(PmSensorCmd::ContinuousMode);
  delay(100);
  debug_outln_info(F("Stopping HPM..."));
  is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
 }

 if (cfg::sps30_read) {
  debug_outln_info(F("Read SPS30..."));
  initSPS30();
 }

 if (cfg::dht_read) {
  dht.begin();
  debug_outln_info(F("Read DHT..."));
  pcf8575.digitalWrite(DHT_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(DHT_LED, LOW);
 }

 if (cfg::rtc_read) {
  rtc.begin();
  debug_outln_info(F("Read Time from RTC..."));
  init_RTC();
  pcf8575.digitalWrite(RTC_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(RTC_LED, LOW);
 }

 if (cfg::htu21d_read) {
  debug_outln_info(F("Read HTU21D..."));


  if (!htu21d.begin() && htu21d.readHumidity() < 1.0f) {
   debug_outln_error(F("Check HTU21D wiring"));
   htu21d_init_failed = true;
  }
 }

 if (cfg::bmp_read) {
  debug_outln_info(F("Read BMP..."));
  if (!bmp.begin()) {
   debug_outln_error(F("No valid BMP085 sensor, check wiring!"));
   bmp_init_failed = true;
  }
 }

 if (cfg::bmx280_read) {
  debug_outln_info(F("Read BMP280/BME280..."));
  if (!initBMX280(0x76) && !initBMX280(0x77)) {
   debug_outln_error(F("Check BMP280/BME280 wiring"));
   bmx280_init_failed = true;
  }
 }

 if (cfg::sht3x_read) {
  debug_outln_info(F("Read SHT3x..."));
  if (!sht3x.begin()) {
   debug_outln_error(F("Check SHT3x wiring"));
   sht3x_init_failed = true;
  }
 }

 if (cfg::ds18b20_read) {
  ds18b20.begin();
  debug_outln_info(F("Read DS18B20..."));
 }

 if (cfg::dnms_read) {
  debug_outln_info(F("Read DNMS..."));
  initDNMS();
 }

 if(cfg::sph0645_read){
  debug_outln_info(F("Read SPH0645..."));
  init_SPH0645();
  pcf8575.digitalWrite(MIC_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(MIC_LED, LOW);
 }

 if (cfg::gps_read){
  pcf8575.digitalWrite(GPS_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(GPS_LED, LOW);
 }

 if (cfg::sd_read){
  pcf8575.digitalWrite(LOGGER_LED, HIGH);
  delay(2000);
  pcf8575.digitalWrite(LOGGER_LED, LOW);
 }

}

static void logEnabledAPIs() {
 debug_outln_info(F("Send to :"));
 if (cfg::send2dusti) {
  debug_outln_info(F("sensor.community"));
 }
   if (cfg::send2cfa) {
     debug_outln_info(F("CFA"));
   }

 if (cfg::send2fsapp) {
  debug_outln_info(F("Feinstaub-App"));
 }

 if (cfg::send2madavi) {
  debug_outln_info(F("Madavi.de"));
 }

 if (cfg::send2csv) {
  debug_outln_info(F("Serial as CSV"));
 }

 if (cfg::send2custom) {
  debug_outln_info(F("custom API"));
 }

 if (cfg::send2aircms) {
  debug_outln_info(F("aircms API"));
 }

 if (cfg::send2influx) {
  debug_outln_info(F("custom influx DB"));
 }
 debug_outln_info(FPSTR(DBG_TXT_SEP));
 if (cfg::auto_update) {
  debug_outln_info(F("Auto-Update active..."));
 }
}

static void logEnabledDisplays() {
 if (cfg::has_display || cfg::has_sh1106) {
  debug_outln_info(F("Show on OLED..."));
 }
 if (lcd_1602) {
  debug_outln_info(F("Show on LCD 1602 ..."));
 }
 if (lcd_2004) {
  debug_outln_info(F("Show on LCD 2004 ..."));
 }
}

static void setupNetworkTime() {


 static char ntpServer1[18], ntpServer2[18], ntpServer3[18];
#if defined(ESP8266)
 settimeofday_cb([]() {
  if (!sntp_time_set) {
   time_t now = time(nullptr);
   debug_outln_info(F("SNTP synced: "), ctime(&now));
   twoStageOTAUpdate();
   last_update_attempt = millis();
  }
  sntp_time_set++;
 });
#endif
 strcpy_P(ntpServer1, NTP_SERVER_1);
 strcpy_P(ntpServer2, NTP_SERVER_2);
 configTime(0, 0, ntpServer1, ntpServer2, ntpServer3);
}




void openLoggingFile()
{
 switchState = digitalRead(LOGGER_SWITCH);
 if (cfg::send2sd && switchState == HIGH)
 {
  init_SD();
  debug_outln_info(F("## Logging to SD: "));
  sensor_readings = SD.open(esp_chipid + "_" + "sensor_readings.txt", FILE_WRITE);
  delay(5000);
 }
}

static unsigned long sendDataToOptionalApis(const String &data) {
 unsigned long sum_send_time = 0;

 if (cfg::send2madavi) {
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("madavi.de: "));
  sum_send_time += sendData(LoggerMadavi, data, 0, HOST_MADAVI, URL_MADAVI);
 }

 if (cfg::send2sensemap && (cfg::senseboxid[0] != '\0')) {
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("opensensemap: "));
  String sensemap_path(tmpl(FPSTR(URL_SENSEMAP), cfg::senseboxid));
  sum_send_time += sendData(LoggerSensemap, data, 0, HOST_SENSEMAP, sensemap_path.c_str());
 }

 if (cfg::send2fsapp) {
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("Server FS App: "));
  sum_send_time += sendData(LoggerFSapp, data, 0, HOST_FSAPP, URL_FSAPP);
 }

 if (cfg::send2aircms) {
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("aircms.online: "));
  unsigned long ts = millis() / 1000;
  String token = WiFi.macAddress();
  String aircms_data("L=");
  aircms_data += esp_chipid;
  aircms_data += "&t=";
  aircms_data += String(ts, DEC);
  aircms_data += F("&airrohr=");
  aircms_data += data;
  String aircms_url(FPSTR(URL_AIRCMS));
  aircms_url += hmac1(sha1Hex(token), aircms_data + token);

  sum_send_time += sendData(Loggeraircms, aircms_data, 0, HOST_AIRCMS, aircms_url.c_str());
 }

 if (cfg::send2influx) {
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("custom influx db: "));
  RESERVE_STRING(data_4_influxdb, LARGE_STR);
  create_influxdb_string_from_data(data_4_influxdb, data);
  sum_send_time += sendData(LoggerInflux, data_4_influxdb, 0, cfg::host_influx, cfg::url_influx);
 }

 if (cfg::send2custom) {
  String data_to_send = data;
  data_to_send.remove(0, 1);
  String data_4_custom(F("{\"esp8266id\": \""));
  data_4_custom += esp_chipid;
  data_4_custom += "\", ";
  data_4_custom += data_to_send;
  debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("custom api: "));
  sum_send_time += sendData(LoggerCustom, data_4_custom, 0, cfg::host_custom, cfg::url_custom);
 }

 if (cfg::send2csv) {
  debug_outln_info(F("## Sending as csv: "));
  send_csv(data);
 }

 return sum_send_time;
}





void setup(void) {
 Serial.begin(9600);
 atmega328p.begin(9600, SWSERIAL_8N1,ATMEGA_TX,ATMEGA_RX,false,256);

#if defined(ESP8266)
 serialSDS.begin(9600, SWSERIAL_8N1, PM_SERIAL_RX, PM_SERIAL_TX);
#endif
#if defined(ESP32)
 serialSDS.begin(9600, SERIAL_8N1, PM_SERIAL_RX, PM_SERIAL_TX);
#endif
 serialSDS.enableIntTx(true);
 serialSDS.setTimeout((12 * 9 * 1000) / 9600);

#if defined(WIFI_LoRa_32_V2)

 pinMode(RST_OLED, OUTPUT);
 digitalWrite(RST_OLED, LOW);
 delay(50);
 digitalWrite(RST_OLED, HIGH);
#endif
 Wire.begin(I2C_PIN_SDA, I2C_PIN_SCL);

#if defined(ESP8266)
 esp_chipid = std::move(String(ESP.getChipId()));
#endif
#if defined(ESP32)
 uint64_t chipid_num;
 chipid_num = ESP.getEfuseMac();
 esp_chipid = String((uint16_t)(chipid_num >> 32), HEX);
 esp_chipid += String((uint32_t)chipid_num, HEX);
#endif
 cfg::initNonTrivials(esp_chipid.c_str());
 WiFi.persistent(false);

 debug_outln_info(F("airRohr: " SOFTWARE_VERSION_STR "/"), String(CURRENT_LANG));
 if ((airrohr_selftest_failed = !ESP.checkFlashConfig(true) )) {
  debug_outln_error(F("ERROR: SELF TEST FAILED!"));
  SOFTWARE_VERSION += F("-STF");
 }

 init_config();
 init_display();
 init_lcd();
 if(cfg::wifi_enabled){
  setupNetworkTime();
  connectWifi();
  setup_webserver();
 }
 if(!cfg::wifi_enabled){
  enableWebServerOffline();
 }
 createLoggerConfigs();
 debug_outln_info(F("\nChipId: "), esp_chipid);

 if (cfg::gps_read) {
#if defined(ESP8266)
  serialGPS = new SoftwareSerial;
  serialGPS->begin(9600, SWSERIAL_8N1, GPS_SERIAL_RX, GPS_SERIAL_TX, false, 128);
#endif
#if defined(ESP32)
  serialGPS->begin(9600, SERIAL_8N1, GPS_SERIAL_RX, GPS_SERIAL_TX);
#endif
  debug_outln_info(F("Read GPS..."));
  disable_unneeded_nmea();
 }

 powerOnTestSensors();
 logEnabledAPIs();
 logEnabledDisplays();

 delay(50);


#if defined(ESP8266)
 wdt_disable();
#if defined(NDEBUG)
 wdt_enable(120000);
#endif
#endif

 starttime = millis();
 last_update_attempt = time_point_device_start_ms = starttime;
 last_display_millis = starttime_SDS = starttime;
}




void loop(void) {
 String result_PPD, result_SDS, result_PMS, result_HPM;
 String result_GPS, result_DNMS, result_SPH0645;

 unsigned sum_send_time = 0;

 act_micro = micros();
 act_milli = millis();
 send_now = msSince(starttime) > cfg::sending_intervall_ms;


 if (!sntp_time_set && send_now &&
   msSince(time_point_device_start_ms) < 1000 * 2 * 30 + 5000) {
  debug_outln_info(F("NTP sync not finished yet, skipping send"));
  send_now = false;
  starttime = act_milli;
 }

 sample_count++;

#if defined(ESP8266)
 wdt_reset();
#endif

 if (last_micro != 0) {
  unsigned long diff_micro = act_micro - last_micro;
  if (max_micro < diff_micro) {
   max_micro = diff_micro;
  }
  if (min_micro > diff_micro) {
   min_micro = diff_micro;
  }
 }
 last_micro = act_micro;

 if (msSince(time_point_device_start_ms) > DURATION_BEFORE_FORCED_RESTART_MS) {
  sensor_restart();
 }

 if (msSince(last_update_attempt) > PAUSE_BETWEEN_UPDATE_ATTEMPTS_MS) {
  twoStageOTAUpdate();
  last_update_attempt = act_milli;
 }

 if (cfg::sps30_read && ( !sps30_init_failed)) {
  if ((msSince(starttime) - SPS30_read_timer) > SPS30_WAITING_AFTER_LAST_READ) {
   struct sps30_measurement sps30_values;
   int16_t ret_SPS30;

   SPS30_read_timer = msSince(starttime);

   ret_SPS30 = sps30_read_measurement(&sps30_values);
   ++SPS30_read_counter;
   if (ret_SPS30 < 0) {
    debug_outln_info(F("SPS30 error reading measurement"));
    SPS30_read_error_counter++;
   } else {
    if (SPS_IS_ERR_STATE(ret_SPS30)) {
     debug_outln_info(F("SPS30 measurements may not be accurate"));
     SPS30_read_error_counter++;
    }
    value_SPS30_P0 += sps30_values.mc_1p0;
    value_SPS30_P2 += sps30_values.mc_2p5;
    value_SPS30_P4 += sps30_values.mc_4p0;
    value_SPS30_P1 += sps30_values.mc_10p0;
    value_SPS30_N05 += sps30_values.nc_0p5;
    value_SPS30_N1 += sps30_values.nc_1p0;
    value_SPS30_N25 += sps30_values.nc_2p5;
    value_SPS30_N4 += sps30_values.nc_4p0;
    value_SPS30_N10 += sps30_values.nc_10p0;
    value_SPS30_TS += sps30_values.tps;
    ++SPS30_measurement_count;
   }
  }
 }

 if (cfg::ppd_read) {
  fetchSensorPPD(result_PPD);
 }


 if (cfg::rtc_read) {
  obtain_sendTime();
  Serial.println(timestamp);
  delay(2000);
 }

 if(cfg::sph0645_read){
  fetchSensorSPH0645(result_SPH0645);
 }

 if ((msSince(starttime_SDS) > SAMPLETIME_SDS_MS) || send_now) {
  starttime_SDS = act_milli;
  if (cfg::sds_read) {
   fetchSensorSDS(result_SDS);
  }

  if (cfg::pms_read) {
   if(readPMSFromAtmega){
    result_PMS = fetchSensorPMSFromAtmega();
   }
   else{
    fetchSensorPMS(result_PMS);
   }

  }

  if (cfg::hpm_read) {
   fetchSensorHPM(result_HPM);
  }
 }

 if (cfg::gps_read && !gps_init_failed) {

  while (serialGPS->available() > 0) {
   gps.encode(serialGPS->read());
  }

  if ((msSince(starttime_GPS) > SAMPLETIME_GPS_MS) || send_now) {

   if(readGPSFromAtmega){
    result_GPS = fetchSensorGPSFromAtmega();
   }
   else{
    fetchSensorGPS(result_GPS);
   }

   starttime_GPS = act_milli;
  }
 }

 if ((msSince(last_display_millis) > DISPLAY_UPDATE_INTERVAL_MS) &&
   (cfg::has_display || cfg::has_sh1106 || lcd_1602 || lcd_2004)) {
  display_values();
  last_display_millis = act_milli;
 }

 server.handleClient();
 if(!cfg::wifi_enabled){
  #if defined(ESP8266)
  wdt_reset();
  #endif
 }
 yield();

 if (send_now) {
  last_signal_strength = WiFi.RSSI();
  RESERVE_STRING(data, LARGE_STR);
  data = FPSTR(data_first_part);
  RESERVE_STRING(result, MED_STR);


  openLoggingFile();

  if(cfg::sph0645_read){
   data += result_SPH0645;
   if(cfg::send2sd){
    sum_send_time += sendSD(result_SPH0645, SPH0645_API_PIN, FPSTR(SENSORS_SPH0645), "SPH0645_");
   }
        if(cfg::wifi_enabled){
    sum_send_time += sendCFA(result_SPH0645, SPH0645_API_PIN, FPSTR(SENSORS_SPH0645), "SPH0645_");
    sum_send_time += sendSensorCommunity(result_SPH0645, SPH0645_API_PIN, FPSTR(SENSORS_SPH0645), "SHP0645_");
     }
  }

  if (cfg::ppd_read) {
   data += result_PPD;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result_PPD, PPD_API_PIN, FPSTR(SENSORS_PPD42NS), "PPD_");
   }
   if(cfg::wifi_enabled){
    sum_send_time += sendCFA(result_PPD, PPD_API_PIN, FPSTR(SENSORS_PPD42NS), "PPD_");
    sum_send_time += sendSensorCommunity(result_PPD, PPD_API_PIN, FPSTR(SENSORS_PPD42NS), "PPD_");
   }

  }
  if (cfg::sds_read) {
   data += result_SDS;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result_SDS, SDS_API_PIN, FPSTR(SENSORS_SDS011), "SDS_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result_SDS, SDS_API_PIN, FPSTR(SENSORS_SDS011), "SDS_");
    sum_send_time += sendSensorCommunity(result_SDS, SDS_API_PIN, FPSTR(SENSORS_SDS011), "SDS_");
   }
  }
  if (cfg::pms_read) {
   data += result_PMS;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result_PMS, PMS_API_PIN, FPSTR(SENSORS_PMSx003), "PMS_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result_PMS, PMS_API_PIN, FPSTR(SENSORS_PMSx003), "PMS_");
    sum_send_time += sendSensorCommunity(result_PMS, PMS_API_PIN, FPSTR(SENSORS_PMSx003), "PMS_");
   }
  }
  if (cfg::hpm_read) {
   data += result_HPM;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result_HPM, HPM_API_PIN, FPSTR(SENSORS_HPM), "HPM_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result_HPM, HPM_API_PIN, FPSTR(SENSORS_HPM), "HPM_");
    sum_send_time += sendSensorCommunity(result_HPM, HPM_API_PIN, FPSTR(SENSORS_HPM), "HPM_");
   }
  }
  if (cfg::sps30_read && (! sps30_init_failed)) {
   fetchSensorSPS30(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, SPS30_API_PIN, FPSTR(SENSORS_SPS30), "SPS30_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, SPS30_API_PIN, FPSTR(SENSORS_SPS30), "SPS30_");
    sum_send_time += sendSensorCommunity(result, SPS30_API_PIN, FPSTR(SENSORS_SPS30), "SPS30_");
   }
   result = emptyString;
  }
  if (cfg::dht_read) {

   if(readDHTFromAtmega){
    result = fetchSensorDHTFromAtmega();
   }
   else{
    fetchSensorDHT(result);
   }
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, DHT_API_PIN, FPSTR(SENSORS_DHT22), "DHT_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, DHT_API_PIN, FPSTR(SENSORS_DHT22), "DHT_");
    sum_send_time += sendSensorCommunity(result, DHT_API_PIN, FPSTR(SENSORS_DHT22), "DHT_");
   }
   result = emptyString;
  }
  if (cfg::htu21d_read && (! htu21d_init_failed)) {

   fetchSensorHTU21D(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, HTU21D_API_PIN, FPSTR(SENSORS_HTU21D), "HTU21D_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, HTU21D_API_PIN, FPSTR(SENSORS_HTU21D), "HTU21D_");
    sum_send_time += sendSensorCommunity(result, HTU21D_API_PIN, FPSTR(SENSORS_HTU21D), "HTU21D_");
   }
   result = emptyString;
  }
  if (cfg::bmp_read && (! bmp_init_failed)) {

   fetchSensorBMP(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, BMP_API_PIN, FPSTR(SENSORS_BMP180), "BMP_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, BMP_API_PIN, FPSTR(SENSORS_BMP180), "BMP_");
    sum_send_time += sendSensorCommunity(result, BMP_API_PIN, FPSTR(SENSORS_BMP180), "BMP_");
   }
   result = emptyString;
  }
  if (cfg::bmx280_read && (! bmx280_init_failed)) {

   fetchSensorBMX280(result);
   data += result;
   if (bmx280.sensorID() == BME280_SENSOR_ID) {
    if(cfg::send2sd) {
     sum_send_time += sendSD(result, BME280_API_PIN, FPSTR(SENSORS_BMX280), "BME280_");
    }
          if(cfg::wifi_enabled){
     sum_send_time += sendCFA(result, BME280_API_PIN, FPSTR(SENSORS_BMX280), "BME280_");
     sum_send_time += sendSensorCommunity(result, BME280_API_PIN, FPSTR(SENSORS_BMX280), "BME280_");
    }
   } else {
    if(cfg::send2sd){
     sum_send_time += sendSD(result, BMP280_API_PIN, FPSTR(SENSORS_BMX280), "BMP280_");
    }
          if(cfg::wifi_enabled) {
     sum_send_time += sendCFA(result, BMP280_API_PIN, FPSTR(SENSORS_BMX280), "BMP280_");
     sum_send_time += sendSensorCommunity(result, BMP280_API_PIN, FPSTR(SENSORS_BMX280), "BMP280_");
    }
   }
   result = emptyString;
  }
  if (cfg::sht3x_read && (! sht3x_init_failed )) {

   fetchSensorSHT3x(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, SHT3X_API_PIN, FPSTR(SENSORS_SHT3X), "SHT3X_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, SHT3X_API_PIN, FPSTR(SENSORS_SHT3X), "SHT3X_");
    sum_send_time += sendSensorCommunity(result, SHT3X_API_PIN, FPSTR(SENSORS_SHT3X), "SHT3X_");
   }
   result = emptyString;
  }
  if (cfg::ds18b20_read) {

   fetchSensorDS18B20(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, DS18B20_API_PIN, FPSTR(SENSORS_DS18B20), "DS18B20_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, DS18B20_API_PIN, FPSTR(SENSORS_DS18B20), "DS18B20_");
    sum_send_time += sendSensorCommunity(result, DS18B20_API_PIN, FPSTR(SENSORS_DS18B20), "DS18B20_");
   }
   result = emptyString;
  }
  if (cfg::dnms_read && (! dnms_init_failed)) {

   fetchSensorDNMS(result);
   data += result;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result, DNMS_API_PIN, FPSTR(SENSORS_DNMS), "DNMS_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result, DNMS_API_PIN, FPSTR(SENSORS_DNMS), "DNMS_");
    sum_send_time += sendSensorCommunity(result, DNMS_API_PIN, FPSTR(SENSORS_DNMS), "DNMS_");
   }
   result = emptyString;
  }
  if (cfg::gps_read) {
   data += result_GPS;
   if(cfg::send2sd) {
    sum_send_time += sendSD(result_GPS, GPS_API_PIN, F("GPS"), "GPS_");
   }
        if(cfg::wifi_enabled) {
    sum_send_time += sendCFA(result_GPS, GPS_API_PIN, F("GPS"), "GPS_");
    sum_send_time += sendSensorCommunity(result_GPS, GPS_API_PIN, F("GPS"), "GPS_");
   }
   result = emptyString;
  }
  add_Value2Json(data, F("samples"), String(sample_count));
  add_Value2Json(data, F("min_micro"), String(min_micro));
  add_Value2Json(data, F("max_micro"), String(max_micro));
  add_Value2Json(data, F("signal"), String(last_signal_strength));

  if ((unsigned)(data.lastIndexOf(',') + 1) == data.length()) {
   data.remove(data.length() - 1);
  }
  data += "]}";

  yield();

  if(cfg::wifi_enabled) {
   sum_send_time += sendDataToOptionalApis(data);
  }


  sending_time = (3 * sending_time + sum_send_time) / 4;
  if (sum_send_time > 0) {
   debug_outln_info(F("Time for Sending (ms): "), String(sending_time));
  }


  if ((WiFi.status() != WL_CONNECTED && cfg::wifi_enabled)) {
   debug_outln_info(F("Connection lost, reconnecting "));
   WiFi_error_count++;
   WiFi.reconnect();
   waitForWifiToConnect(20);
  }


  last_data_string = std::move(data);
  lowpulseoccupancyP1 = 0;
  lowpulseoccupancyP2 = 0;
  sample_count = 0;
  last_micro = 0;
  min_micro = 1000000000;
  max_micro = 0;
  sum_send_time = 0;
  starttime = millis();
  count_sends++;
 }
 yield();
#if defined(ESP8266)
 MDNS.update();
 serialSDS.perform_work();
#endif

 if (sample_count % 500 == 0) {

 }
}