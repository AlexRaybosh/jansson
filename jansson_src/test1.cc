#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <jansson.h>

uint32_t h(const void *key, size_t length) {
	if (length==0) return 0;
	else if (length==1){
		return (uint32_t)*((char*)key);
	} else if (length==2){
		return (uint32_t)*((uint16_t*)key);
	}  else if (length==3){
		return (((uint32_t)*((uint16_t*)key))<<8) | (uint32_t)*((char*)key+2);
	}  else if (length==4){
		return *((uint32_t*)key);
	} else {
		uint32_t first=*((uint32_t*)key);
		uint32_t last=*((uint32_t*)((char*)key+length-4));
		return first ^ last;
	}
}


std::ostream& pa(std::stringstream & sb, int off, const char* attr) {
	if (attr) {
		for (int i=0;i<off;++i)
			sb<<"\t";
		sb<<attr<<"=";
	} else {
		for (int i=0;i<off;++i) sb<<"\t";
	}
	return sb;
}

void walk(std::stringstream & sb, const char* attr, json_t *json, int off) {
	if (!json) {
		//null
		return;
	}
	switch (json_typeof(json)) {
	case JSON_NULL: {
			//po(off)<<pa(attr)<<"NULL"<<std::endl;
			pa(sb,off,attr)<<"NULL"<<std::endl;
		}
		break;
	case JSON_OBJECT: {
			//po(off)<<pa(attr)<<"{"<<std::endl;
			pa(sb,off,attr)<<"{"<<std::endl;
			/*std::vector<const char*> keys;
			for (void *iter = json_object_iter(json);iter;iter = json_object_iter_next(json, iter)) {
				const char *key = json_object_iter_key(iter);
				keys.push_back(key);
			}
			for (auto & k : keys) {
				json_t * child=json_object_get(json, k);
				walk(sb, k,child,off+1);
			}
			sb<<"--------------\n";
			*/
			for (void *iter = json_object_iter(json);iter;iter = json_object_iter_next(json, iter)) {
				const char *key = json_object_iter_key(iter);
				json_t * child = json_object_iter_value(iter);
				//print
				walk(sb, key,child,off+1);
			}
			pa(sb,off,NULL)<<"}"<<std::endl;
		}
		break;
	case JSON_ARRAY:
		pa(sb,off,attr)<<"["<<std::endl;
		for (size_t i=0;i<json_array_size(json);++i) {
			auto child=json_array_get(json, i);
			walk(sb, NULL,child,off+1);
		}
		pa(sb,off,NULL)<<"]"<<std::endl;
		break;
	case JSON_STRING:{
		auto str=json_string_value(json);
		pa(sb,off,attr)<<str<<std::endl;
		}
		break;
	case JSON_INTEGER: {
			json_int_t val=json_integer_value(json);
			pa(sb,off,attr)<<val<<std::endl;
		}
		break;
	case JSON_REAL: {
			double num=json_real_value(json);
			pa(sb,off,attr)<<num<<std::endl;
		}
		break;
	case JSON_FALSE:
	case JSON_TRUE:
		{
			bool b=json_boolean_value(json);
			pa(sb,off,attr)<<b<<std::endl;
		}
		break;
	default:
		return;
	}
}
int main() {
	std::vector<std::string> v={"", "a","ab","cd","ba","abc", "abcd", "abcde", "abcdef", "abcdefg","abcdefgh","abcdefghe"};
	for (auto & s : v) {
		std::cout<<s<<"\t\t"<<h(s.data(), s.size())<<std::endl;
	}


	std::string j1="{"
			"\"null\":null, "
			"	\"mybool\" : true,"
			"	\"mybool1\" : false,"
			"\"widget\": {\n"
			"    \"debug\": \"on\",\n"
			"    \"window\": {\n"
			"        \"title\": \"Sample Konfabulator Widget\",\n"
			"        \"name\": \"main_window\",\n"
			"        \"width\": 500,\n"
			"        \"height\": 500\n"
			"    },\n"
			"    \"image\": { \n"
			"        \"src\": \"Images/Sun.png\",\n"
			"        \"name\": \"sun1\",\n"
			"        \"hOffset\": 250,\n"
			"        \"vOffset\": 250.123,\n"
			"        \"alignment\": \"center\"\n"
			"    },\n"
			"    \"text\": {\n"
			"        \"data\": \"Click Here\",\n"
			"        \"size\": 36,\n"
			"        \"style\": \"bold\",\n"
			"        \"name\": \"text1\",\n"
			"        \"hOffset\": 250,\n"
			"        \"vOffset\": 100,\n"
			"        \"alignment\": \"center\",\n"
			"        \"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n"
			"    }\n"
			"}}";
	std::cout<<j1<<std::endl;
    json_error_t error;
    json_t *root=json_loads(j1.c_str(), j1.size(), &error);
    std::cout<<error.text<<std::endl;
    std::stringstream sb;
    walk(sb, NULL,root, 0);
    json_decref(root);
    std::cout<<sb.str()<<std::endl;

	return 0;
}
