#include <adri_tools.h>

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
   char printf_buf[300];
   fs(tdblspace,     "\t");
   fs(tparm,         " :\t");
#endif


void debugPrint(String buf){Serial.print(buf);};
void debugPrintLn(String buf){Serial.println(buf);};


String ch_toString(char * c){
   char result[255];
   fssprintf(result, "%s", c);
   return String(result);
}
String ch_toString(const char * c){
   // char result[1024];
   // sprintf(result, "%s", c);

   return String((const __FlashStringHelper*) c);
}
// char * add_string(String s) {
//    // char * result;
//    // String t=s;
//    // s.toCharArray(result+strlen(result),s.length()+1);
//    char result[300];
//    sprintf(result,"%s",s.c_str());
//    return result;
// }



#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)

   String info_parm(String name, String value) {
      String s=name;
      while (s.length()<25) s+=" ";
      return fsget(tdblspace)+s+fsget(tparm)+value+"\n";
   }
   String info_parm(String name, String value, int space) {
      String s=name;
      int size = s.length();
      while (size<space) s+=" ";
      return fsget(tdblspace)+s+fsget(tparm)+value+"\n";
   }
   String info_parm(String name, int value) {
      String s=name;
      while (s.length()<25) s+=" ";
      return fsget(tdblspace)+s+fsget(tparm)+String(value)+"\n";
   }
   String info_parm(String name, String value , String sep) {
      String s=name;
      while (s.length()<25) s+=" ";
      return fsget(tdblspace)+s+sep+fsget(tdblspace)+value+"\n";
   }
   String info_parm(String name, String value , String sep, int len, String last, String tdb1, String tdb2) {
      String s=name;
      int size = s.length();
      while (size<len) s+=" ";
      return tdb1+s+sep+tdb2+value+last;
   }
#endif

int explode(String s, char sep, String * list) {
  // Serial.printf("\nexplode s: %s\n", s.c_str() );
	String t=s+sep;
	int str_index=0;
	int list_index=0;
	int j;
	String sub;
  int size = t.length();
	while (str_index < size ) {
		j=t.indexOf(sep,str_index);
		if (j!=-1) {
			sub=t.substring(str_index, j);
			// Serial.printf("explode index:%d %s\n", str_index,sub.c_str() );
			list[list_index++]=sub;
			str_index=j+1;
		}
	}
	list[list_index]="";
	return list_index;
}

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
   String ip2string(IPAddress a) {
     char buf[18];
     fssprintf(buf,"%d.%d.%d.%d",a[0],a[1],a[2],a[3]);
     return String(buf);
   }

   IPAddress string2ip(String ip) {
   	String a[10];
   	explode(ip, '.', a);
   	IPAddress adr={static_cast<uint8_t>(a[0].toInt()),
      static_cast<uint8_t>(a[1].toInt()),
      static_cast<uint8_t>(a[2].toInt()),
      static_cast<uint8_t>(a[3].toInt())};
   	return adr;
   }
#endif
void decimalToBinary(int decimal)

{
   fsprintfs("\ndecimalToBinary\n");
   fsprintf("decimal: %d\n", decimal);
   // int bits, bit_fac;
   // char binary[255];
   // bits = int(log(decimal)/log(2));
   // for(int i = 0; i < bits+1; ++i)

   //     {
   //         bit_fac=int(pow(2,bits-i));
   //         binary[i]=(decimal / bit_fac > 0? '1' : '0');
   //         decimal=(decimal / bit_fac > 0? decimal - bit_fac : decimal);
   //     }
   //     // cout <<"Voici son equivalent binaire : ";
   //     fsprintfs("result: ");
   //     for(int j=0; j<bits+1; ++j)

   //         {
   //              fsprintf("%d", binary[j]);
   //         }


   //     cout<<endl;
   int num = decimal;
   uint8_t bitsCount = sizeof( num ) * 8;
   char str[ bitsCount + 1 ];

   itoa( num, str, 2 );
   fsprintfs("result: ");
   Serial.println( str );
}
int convertBinToDec(boolean Bin[]) {
  int ReturnInt = 0;
  for (int i = 0; i < 8; i++) {
    if (Bin[7 - i]) {
      Serial.print("Set Bit ");
      Serial.print(i);
      ReturnInt += 1<<i;
      Serial.print(" ==> ");
      Serial.print(1<<i);
      Serial.print(", ");
    }
  }
  return ReturnInt;
}
void convertDecToBin(int Dec, boolean Bin[]) {
  for(int i = 7 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      Bin[8-(i+1)] = 1;
    } else {
    }
  }
}


void seconds2time(unsigned long s, char * time) {
   // int milli      = (s                    ) % 1000;
   int seconds    = (s /   (1000)         ) % 60   ;
   int minutes    = (s /   (1000*60)      ) % 60   ;
   int hours      = (s /   (1000*3600)    ) % 24   ;
   int days    = (s /  (1000*3600*24)  )     ;
   sprintf(time,"%d-%02d:%02d:%02d", days, hours , minutes, seconds);
}


String on_time() {
   char t[100];
   unsigned long offset = 0; //1000 * 60 * 60 * 24 * 3 ;
   unsigned long ms=millis()+offset;
   seconds2time(ms, t);
   return String(t);
}

String on_time(long ms) {
   char t[100];
   seconds2time(ms, t);
   return String(t);
}

void seconds2time_h(unsigned long s, char * time) {

   int seconds    = (s                ) % 60   ;
   int minutes    = (s /   (60)      ) % 60   ;
   int hours      = (s /   (3600)    ) % 24   ;

   sprintf(time,"%02d:%02d:%02d", hours , minutes, seconds);
}


String on_time_h(long ms) {
   char t[100];
   seconds2time_h(ms, t);
   return String(t);
}

String literal_value(String name, String xml){
   String open,close;
   String value = "";
   int start, end;
   open="<"+name+">";
   close="</"+name+">";
   start=xml.indexOf(open);
   if (start!=-1) {
      start+=name.length()+2;
      end=xml.indexOf(close);
      value=xml.substring(start,end);
   }
   return value;
}

String literal_item(String name, String value) {
   String x="<"+name+">"+value+"</"+name+">";
   return x;
}


String ini_item_section(String name) {
   String x="[" + name + "]\n";
   return x;
}
String ini_item_key(String name, String value) {
   String x= name + "=" + value + "\n";
   return x;
}

void toggleBool(String header, boolean *val ){
   *val ? *val = false : *val = true;
}
// void _toggleBool(String header, boolean *val ){
//    *val ? *val = false : *val = true;
//    Serial.printf("%s : %d\n", header.c_str(), *val);
// }


boolean literal_value_isntEmpty(String name, String string) {
   if ( literal_value(name, string) != "") return true;
   else return false;
}
void literal_value_set(int       * var, String name, String string) { * var = literal_value(name, string ).toInt(); }
void literal_value_set(uint32_t  * var, String name, String string) { * var = literal_value(name, string ).toInt(); }
void literal_value_set(uint16_t  * var, String name, String string) { * var = literal_value(name, string ).toInt(); }
void literal_value_set(uint8_t   * var, String name, String string) { * var = literal_value(name, string ).toInt(); }
// String valueFromSPIFF(boolean debug, String pName, String search){

//    String sString                =  pattern_loadFromSPIFF(debug,pName);
//    if (sString == "")   sString  =  pattern.setDefaultValue(pName);
//    if (sString != "")               pattern_loadFromString(sString); 
//    if (sString == "")               return "";

//    if ( !literal_value_isntEmpty(search, sString) ) return "";

//    return literal_value(search, sString );
// }


String jsonAddString (String label, String value) {
   String json = "{";
   json += "\""+label+"\":\"" +  value + "\"";
   json += "}";
   return json;
}
String jsonAddStringValue (boolean start, String label, String value) {
   String ret;
   if (start) ret = "\""+label+"\":\"" +  value + "\"";
   else ret = ", \""+label+"\":\"" +  value + "\"";
   return ret;
}
String jsonAddStringsValue (boolean start, String label, String value) {
   String ret;
   if (start) ret = "\""+label+"\":\"" +  value + "\"";
   else ret = ", \""+label+"\":\"" +  value + "\"";
   return ret;
}
String jsonAddStringValue (boolean start, char * c_label, String value) {
   String label = ch_toString(c_label);
   String ret;
   if (start) ret = "\""+label+"\":\"" +  value + "\"";
   else ret = ", \""+label+"\":\"" +  value + "\"";
   return ret;
}
String jsonAddIntValue (boolean start, String label, String value) {
   String ret;
   if (start) ret =  "\""+label+"\":" +  value ;
   else ret = ", \""+label+"\":" +  value ;
   return ret;
}
String jsonAddIntValue (boolean start, char * c_label, String value) {
   String label = ch_toString(c_label);
   String ret;
   if (start) ret =  "\""+label+"\":" +  value ;
   else ret = ", \""+label+"\":" +  value ;
   return ret;
}

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
   String heap_string() {
      return String(system_get_free_heap_size());
   }
#endif

// #ifndef ADRIWIFI_H
// void debugPrint(String buf) {
//     Serial.print(buf);
//     // appi_softRemotePrint(buf );
// }
// void debugPrintLn(String buf) {
//     Serial.print(buf);
//     // appi_softRemotePrint(buf + "\n");
// }
// #endif
// 


   boolean stringToBool(String value) {
      boolean ret;
      if (value == "0") ret = false; else ret = true;
      return ret;
   }

   boolean stringToBool(int value) {
      if (value == 0) return false;
      return true;
   }   




   int* splitTime(String Val, char sep) {
       String      aVal            = Val;
       byte        firstIndex      = aVal.indexOf(sep);
       byte        secondIndex     = aVal.indexOf(sep, firstIndex + 1);
       String      hr              = aVal.substring(0, firstIndex);
       String      minute          = aVal.substring(firstIndex + 1, secondIndex);
       String      sec             = aVal.substring(secondIndex + 1);
       int         _hr             = hr.toInt();
       int         _minute         = minute.toInt();
       int         _sec            = sec.toInt();

       int     *array          = new int[3];
               array[0]        = _hr;
               array[1]        = _minute;
               array[2]        = _sec;
       return array;    
   }   


String  string_to_split(String name, String value, String sep){
    return name + sep + value;
}
String  string_to_split(String name, String value){
    return name + ";" + value + "\n";
}


void adriTools_serialReadItem::item_add(   
  String      name,
  const char* key,
  String      ret,
  at_srFunc   f )
{
  _name       = name;
  _key        = key;
  _ret        = ret;
  _function   = f;
}


adriTools_serialRead * adriTools_serialRead_ptr;
adriTools_serialRead * adriTools_serialReadPtr_get(){
    return adriTools_serialRead_ptr;
}
adriTools_serialRead::adriTools_serialRead(){
    adriTools_serialRead_ptr = this;
  // _generalArray = new adriTools_serialReadItem[2];
  // _generalArray[0].item_add("reset",     "a", "", adriTools_serialRead_ESPreset);
  // _generalArray[1].item_add("reset_2",   "z", "", adriTools_serialRead_ESPreset);
  


  // for (int i = 0; i < 2; ++i)
  // {
  //   fsprintf("[%10d][%15s][%15s]\n", 
  //               i, 
  //               _generalArray[i]._name.c_str(), 
  //               _generalArray[i]._key.c_str()
  //           );
  // }
}
void adriTools_serialRead::menu(){
    fsprintf("\n[letter]\n");
    for (int i = 0; i < _cmd_1_cnt; ++i) {
    fsprintf("[%5d][%25s][%-15s]\n", 
                i, 
                _cmd_1_Array[i]._name.c_str(), 
                _cmd_1_Array[i]._key
            );
    }
    fsprintf("\n[!]\n");
    for (int i = 0; i < _cmd_2_cnt; ++i) {
    fsprintf("[%5d][%25s][%-15s]\n", 
                i, 
                _cmd_2_Array[i]._name.c_str(), 
                _cmd_2_Array[i]._key
            );
    } 
    if (_cmd_3_desc!="") {
        fsprintf("\n[%s][%s]\n", _cmd_3_sep, _cmd_3_desc.c_str());
    } 
    if (_cmd_4_desc!="") {
        fsprintf("\n[%s][%s]\n", _cmd_4_sep, _cmd_4_desc.c_str());
    }                  
}
void adriTools_serialRead::cmd_array(int pos, int cnt) {
    switch (pos){
        case 1: 
            _cmd_1_Array = new adriTools_serialReadItem[cnt];
        break;
        case 2: 
            _cmd_2_Array = new adriTools_serialReadItem[cnt];
        break;
    }
    
    
   
    
}


void adriTools_serialRead::cmd_item_add(int pos, String name, const char* key, String ret, at_srFunc f){

    switch (pos){
        case 1: 
            _cmd_1_Array[_cmd_1_cnt].item_add(name, key, ret, f);
            _cmd_1_cnt++;
        break;
        case 2: 
            _cmd_2_Array[_cmd_2_cnt].item_add(name, key, ret, f);
            _cmd_2_cnt++;
        break;
    }

}
void adriTools_serialRead::cmd_3(char* sep, String desc, at_srFunc f){
    _cmd_3_sep  = sep;
    _cmd_4_desc = desc;
    _cmd_3      = f;
}
void adriTools_serialRead::cmd_4(char* sep, String desc, at_srFunc f){
    _cmd_4_sep  = sep;
    _cmd_4_desc = desc;
    _cmd_4      = f;    
}

void adriTools_serialRead::loop(){

    if(Serial.available()) { 
        boolean next = true;

        String a = Serial.readStringUntil('\n');

        String cmd = "";
        String value = "";  
        // const char * bl = "";
        static String lastMsg = "";

        if (a.indexOf("^")>=0)a=lastMsg;
        lastMsg = a;

        if (a.indexOf("!")>=0){
            splitText(a, "!", cmd,  value) ; 
            for (int i = 0; i < _cmd_2_cnt; ++i) {
                if (cmd == _cmd_2_Array[i]._key) {
                    _cmd_2_Array[i]._function(cmd, value);
                    next = false;
                    break;
                }
            }        
        }       
        else if (_cmd_3_sep != (char *)"") {
            if (a.indexOf(_cmd_3_sep)>=0) {
                 splitText(a, _cmd_3_sep, cmd,  value) ; 
                _cmd_3(cmd, value);
                next = false;
            }   
        }   
        else if (_cmd_4_sep != (char *)"") {
            if (a.indexOf(_cmd_4_sep)>=0) {
                 splitText(a, _cmd_4_sep, cmd,  value) ; 
                _cmd_4(cmd, value);
                next = false;
            }                            
        } 
        if (next) {
            for (int i = 0; i < _cmd_1_cnt; ++i) {
                if (a.indexOf(_cmd_1_Array[i]._key)>=0 ) {
                    _cmd_1_Array[i]._function("", "");
                }
            }                        
        }        
        
    }       
}
int adriTools_serialRead::splitText(String A_readString, const char* sep, String & cmd, String & value) {

    String  s_command;
    String  s_valueCommand;
    String  s_readString = A_readString;
    char    inputChar[s_readString.length() + 1] ;
            s_readString.toCharArray(inputChar, s_readString.length() + 1);
    char    * Rcommand  = strtok(inputChar, sep);

    while (Rcommand != 0){          
        char* separator  = strchr(Rcommand, '=');
        if (separator != 0) {
            *separator  = 0;            
            ++separator ;
            s_command = String(Rcommand);
            s_valueCommand = String(separator); 
            
            if (s_command!=""){
                value = s_valueCommand;
                cmd = s_command;
                break;
            }
        }
        Rcommand = strtok(0, sep); 
    }

    return 0;
}



adri_tools * adri_tools_ptr;
adri_tools * adri_toolsPtr_get(){
    return adri_tools_ptr;
}
adri_tools::adri_tools(){
    adri_tools_ptr = this;
}
void adri_tools::log_read(String & ret, boolean lineNbr){
  if (lineNbr) fsprintf("\n[_log_read]\n"); 
  char buffer[255];
  ret = "";
  int nbr = 0;
    File file = LittleFS.open("/log.txt", "r");
    if (file) {
    while (file.position()<file.size()) {
      String xml = file.readStringUntil('\n');
      if (xml != "") {
        if (lineNbr)  {
            sprintf(buffer, "[%15d] %s", nbr, xml.c_str());
          ret += String(buffer) + "\n";
          fsprintf("%s\n", buffer);
          delay(5);
          nbr++;
        }
        else      ret += xml + "\n";
      }
    }
        file.close(); 
    }
}
void adri_tools::log_write(String old, String timeStr){
    int       freeHeap  = ESP.getFreeHeap();
    File file = LittleFS.open("/log.txt", "w");
    if (file) {
        char buffer[255];
        sprintf(buffer, "%15s | %15d", timeStr.c_str(), freeHeap);
        String result = old + "\n" + String(buffer);
        file.println(result);
        file.close(); 
    } 
}

void adri_tools::log_write(String old , String timeStr, String msg){
    File file = LittleFS.open("/log.txt", "w");
    if (file) {
        char buffer[255];
        sprintf(buffer, "%15s | %s", timeStr.c_str(), msg.c_str());
        String result = old + "\n" + String(buffer);
        file.println(result);
        file.close(); 
    } 
}