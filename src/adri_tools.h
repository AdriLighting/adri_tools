
#ifndef ADRI_TOOLS_H
	#define ADRI_TOOLS_H
	#include <arduino.h>


			#if  defined(ARDUINO_ARCH_ESP32)
				#include <WiFi.h>
				#include <SPIFFS.h>
			#elif defined(ARDUINO_ARCH_ESP8266)
				#include <ESP8266WiFi.h>
				#include <FS.h>
			#endif
					// #ifdef ESP8266

			// #include <ESP8266WiFi.h>

			
			void debugPrint(String buf);
			void debugPrintLn(String buf);

		#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
			
			extern char printf_buf[];

			#define fs(parm_a,parm_b) 		static const char parm_a[] PROGMEM = parm_b
			#define fsprintln(parm_a) 		debugPrintLn(FPSTR(parm_a))
			#define fsprint(parm_a) 		debugPrint(FPSTR(parm_a))
			#define fsget(parm_a) 			String(FPSTR(parm_a))


// #ifdef DEBUG_ESP_WIFI
// #ifdef DEBUG_ESP_PORT
// #define DEBUG_WIFI_MULTI(fmt, ...) DEBUG_ESP_PORT.printf_P( (PGM_P)PSTR(fmt), ##__VA_ARGS__ )
// #endif
// #endif

// #ifndef DEBUG_WIFI_MULTI
// #define DEBUG_WIFI_MULTI(...) do { (void)0; } while (0)
// #endif

			#define fsprintf(parm_a, ...) 	{sprintf_P(printf_buf, (PGM_P)PSTR(parm_a), ##__VA_ARGS__); debugPrint(String(printf_buf));}


			#define fsprintfs(parm_a) 		{sprintf_P(printf_buf, PSTR(parm_a)); debugPrint(String(printf_buf));}
			#define fssprintf(parm_b, parm_a,...) sprintf_P(parm_b, PSTR(parm_a), __VA_ARGS__)
		#endif
			


		// #define TRACE(text)									\
		// 		{											\
		// 			String t=__FILE__;						\
		// 			t.replace("..","");						\
		// 			t+=":"+String(__LINE__)+" "+text;		\
		// 			Serial.println (t);								\
				}

					
		void 		add_string(char * result, String s);
		// char * 		add_string(String s); 
		const char * add_string(String s);

		#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
			String      info_parm(String name, String value);
			String      info_parm(String name, int value);
			String      info_parm(String name, String value , String sep);
			String      info_parm(String name, String value , String sep, int len, String last, String tdb1, String tdb2);   
			String      info_parm(String name, String value, int space)  ;  
		#endif

		String      ini_item_section(String name);
		String      ini_item_key(String name, String value);

		String      literal_item(String name, String value);
		String      literal_value(String name, String xml);

		void        seconds2time(unsigned long s, char * time);
		String      on_time();
		String 		on_time(long ms);

		void 		seconds2time_h(unsigned long s, char * time);
		String 		on_time_h(long ms);

		#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
			String      ip2string(IPAddress a);
			IPAddress   string2ip(String ip);
		#endif
		void decimalToBinary(int decimal);
		int convertBinToDec(boolean Bin[]);
		void convertDecToBin(int Dec, boolean Bin[]);

		int         explode(String s, char sep, String * list);
		String 		ch_toString(char * c);
		String 		ch_toString(const char * c);

		boolean 	literal_value_isntEmpty(String name, String string);
		void 		literal_value_set	(int 		* var, String name, String string );
		void 		literal_value_set 	(uint32_t 	* var, String name, String string );
		void 		literal_value_set	(uint16_t 	* var, String name, String string );
		void 		literal_value_set	(uint8_t 	* var, String name, String string );

		String 		jsonAddString (String label, String value);
		String 		jsonAddStringValue (boolean start, String label, String value);
		String 		jsonAddStringValue (boolean start, char * c_label, String value);
		String 		jsonAddIntValue (boolean start, String label, String value);
		String 		jsonAddIntValue (boolean start, char * c_label, String value);

		String 		heap_string();
#endif

