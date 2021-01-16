
#ifndef ADRI_TOOLS_H
	#define ADRI_TOOLS_H
	#include <arduino.h>

			#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

			#if  defined(ARDUINO_ARCH_ESP32)
				#include <WiFi.h>
				#include <SPIFFS.h>
			#elif defined(ARDUINO_ARCH_ESP8266)
				#include <ESP8266WiFi.h>
				#include <LittleFS.h>
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
		String 		jsonAddStringsValue (boolean start, String label, String value);

		String 		heap_string();

		boolean 	stringToBool(String value);
		boolean 	stringToBool(int value);

		int* splitTime(String Val, char sep);

		String  string_to_split(String name, String value, String sep);
		String  string_to_split(String name, String value);

		

	// struct SerialMenuList {
	// 	String 	name;
	// 	String 	key;
	// 	// String 	ret;
	// 	// String 	(* function)();
		
	// };
	// SerialMenuList serialMenuList[10];
		// 
typedef String (*at_srFunc)(String cmd, String value);  
class adriTools_serialReadItem
{

public:
		String 			_name;
		const char*		_key;
		String 			_ret;
		at_srFunc 		_function;	

	adriTools_serialReadItem(){}
	void item_add(
		String 		name,
		const char*	key,
		String 		ret,
		at_srFunc 	f		);

	~adriTools_serialReadItem(){};
	
};
class adriTools_serialRead
{
		int _cmd_1_cnt = 0;
		int _cmd_2_cnt = 0;
		adriTools_serialReadItem * _cmd_1_Array = nullptr; // simpl letter 	- split
		adriTools_serialReadItem * _cmd_2_Array = nullptr; // ! 			- split
		at_srFunc 	_cmd_3 		= NULL;		
		char* 		_cmd_3_sep  = (char *)"";		
		String		_cmd_3_desc = "";		
		at_srFunc 	_cmd_4 		= NULL;		
		char*		_cmd_4_sep  = (char *)"";		
		String 		_cmd_4_desc = "";		
public:

	adriTools_serialRead();
	~adriTools_serialRead(){};

	int splitText(String A_readString, const char* sep, String & cmd, String & value) ;
	void cmd_array(int pos, int cnt);

	void cmd_item_add (int pos, String name, const char* key, String ret, at_srFunc f);
	void cmd_3(char* sep, String desc, at_srFunc f);
	void cmd_4(char* sep, String desc, at_srFunc f);

	void loop();
	void menu();
};
adriTools_serialRead * adriTools_serialReadPtr_get();





class adri_tools
{
public:
	adri_tools();
	~adri_tools(){};
	void log_read(String & ret, boolean lineNbr);
	void log_write(String old, String timeStr);
	void log_write(String old, String timeStr, String msg);
	
};
adri_tools * adri_toolsPtr_get();

#endif
/*
void _serial_loop(String a){
    String cmd = "";
    String value = "";  
    static String lastMsg = "";

        if (a.indexOf("&")>=0){
            _serialRead_split(a, "&", cmd,  value) ;
            effectIdInstance()->settingFromSerial(cmd, value, true);
        } else if (a.indexOf("!")>=0){
            _serialRead_split(a, "!", cmd,  value) ;
            if (cmd == "p") effect_manager_instance()->activateEffect(value.toInt());
        } else {
            if (a.indexOf("a")>=0) {effectIdInstance()->settingToSerial();Serial.println(F("__"));}
            if (a.indexOf("z")>=0) {effect_manager_instance()->print_list();}
            if (a.indexOf("q")>=0) {ESP.restart();}
            if (a.indexOf("w")>=0) {
                uint8_t pos = effect_manager_instance()->activeEffectIndex();
                effect_manager_sav(pos);
            }

        }
}
*/