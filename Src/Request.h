#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_HEAD "HEAD"
#define METHOD_PUT "PUT"
#define METHOD_DELETE "DELETE"
#define METHOD_TRACE "TRACE"
#define METHOD_PATCH "PATCH"
#define METHOD_OPTIONS "OPTIONS"
#define METHOD_CONNECT "CONNECT"

class Request{
  String method;
  String path;
  String userAgent;
  String host;
  String body;
  String httpVersion;
  char* lines[1000];

  public:
  Request(String rawData){
    char* raw = (char*)rawData.c_str();

    if(raw == NULL){
      Serial.println("Empty request.");
      return;
    }

    lines[0] = strtok(raw, "\n");

    for(int i = 1; lines[i - 1] != NULL && i < 1000; i++){
      lines[i] = strtok(NULL, "\n");
    }

    method = strtok(lines[0], " ");
    path = strtok(NULL, " ");
    path.replace("\r", "");
    httpVersion = strtok(NULL, " ");

    for(int i = 1; lines[i] != NULL && i < 1000; i++){
      if(strstr(lines[i], "User-Agent: ") != NULL){
        userAgent = lines[i];
        break;
      }
    }
    for(int i = 1; lines[i] != NULL && i < 1000; i++){
      if(strstr(lines[i], "Host: ") != NULL){
        host = lines[i];
        break;
      }
    }
  }

  void print(){
    for(int i = 0; lines[i] != NULL && i < 1000; i++){
      Serial.println(lines[i]);
    }
  }

  String getMethod(){
    return method;
  }
  String getPath(){
    return path;
  }
  String getHttpVersion(){
    return httpVersion;
  }
  String getUserAgent(){
    return userAgent;
  }
  String getHost(){
    return host;
  }
  String getBody(){
    return body;
  }
};