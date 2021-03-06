#include <iostream>
#include <sstream>
#include "lib/rapidjson/document.h"
#include "controller/Manager.h"
#include "lib/rapidjson/stringbuffer.h"
#include "lib/rapidjson/writer.h"

int main() {
    std::cout << "content-type: text/html\n\n";

    //receive inJson into string
    std::stringstream inBuff;

    std::string temp_str, inJsonRequest = inBuff.str();
    std::cin >> inJsonRequest;
    rapidjson::Document inJson, outJson; outJson.SetObject(); auto &allocator = outJson.GetAllocator();
    rapidjson::Value tmp_val;
    inJson.Parse(inJsonRequest.c_str());

    Manager manager;

    switch (inJson["identifier"].GetString()[0]){
        case 'a':
            temp_str = manager.getRecentLogin(inJsonRequest);
            tmp_val.SetString(temp_str.c_str(), temp_str.length(), allocator);
            outJson.AddMember("lastLogin",tmp_val,allocator);
            tmp_val.SetBool(manager.authenticate(inJsonRequest));
            outJson.AddMember("areValid",tmp_val,allocator);

            goto send_response;
//            break;
        case 'n':
            temp_str = "Never";
            tmp_val.SetString(temp_str.c_str(), temp_str.length(), allocator);
            outJson.AddMember("lastLogin",tmp_val,allocator);
            tmp_val.SetBool(manager.createUser(inJsonRequest));
            outJson.AddMember("areValid",tmp_val,allocator);
            goto send_response;
//            break;
        case 'c':
            tmp_val.SetBool(manager.createNote(inJsonRequest));
            outJson.AddMember("success",tmp_val,allocator);
            goto send_response;
//            break;
        case 'p':
            tmp_val.SetBool(manager.updateNote(inJsonRequest));
            outJson.AddMember("success",tmp_val,allocator);
            goto send_response;
//            break;
        case 'd':
            tmp_val.SetBool(manager.deleteNote(inJsonRequest));
            outJson.AddMember("success",tmp_val,allocator);
            goto send_response;
//            break;
        case 'g':
            inJsonRequest = manager.getNotesList(inJsonRequest);
            if(!inJsonRequest.empty()) {
                std::cout << inJsonRequest;
                break;
            }
        default:
            std::cout << "{\"error\":147}";
    }


    return 0;

    send_response:
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    outJson.Accept(writer);
    std::cout << buffer.GetString();

    return 0;
}