#include <adri_tools.h>

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
   char printf_buf[300];
   fs(tdblspace,     "\t");
   fs(tparm,         " :\t");
#endif


void debugPrint(String buf){Serial.print(buf);};
void debugPrintLn(String buf){Serial.println(buf);};


String ch_toString(char * c){
   char result[300];
   sprintf(result, "%s", c);
   return String(result);
}
String ch_toString(const char * c){
   char result[300];
   sprintf(result, "%s", c);
   return String(result);
}
// char * add_string(String s) {
//    // char * result;
//    // String t=s;
//    // s.toCharArray(result+strlen(result),s.length()+1);
//    char result[300];
//    sprintf(result,"%s",s.c_str());
//    return result;
// }
const char * add_string(String s) {
   // char * result;
   // String t=s;
   // s.toCharArray(result+strlen(result),s.length()+1);
   char result[300];
   sprintf(result,"%s",s.c_str());
   return result;
}

void add_string(char * result, String s) {
   String t=s;
   s.toCharArray(result+strlen(result),s.length()+1);
}

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
   String info_parm(String name, String value) {
      String s=name;
      while (s.length()<25) s+=" ";
      return fsget(tdblspace)+s+fsget(tparm)+value+"\n";
   }
   String info_parm(String name, String value, int space) {
      String s=name;
      while (s.length()<space) s+=" ";
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
      while (s.length()<len) s+=" ";
      return tdb1+s+sep+tdb2+value+last;
   }
#endif

int explode(String s, char sep, String * list) {
	String t=s+sep;
	int str_index=0;
	int list_index=0;
	int j;
	String sub;
	while (str_index < t.length() ) {
		j=t.indexOf(sep,str_index);
		if (j!=-1) {
			sub=t.substring(str_index, j);
			//Serial.printf("explode index:%d %s\n", str_index,sub.c_str() );
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
   	IPAddress adr={a[0].toInt(),a[1].toInt(),a[2].toInt(),a[3].toInt()};
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
   int milli      = (s                    ) % 1000;
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