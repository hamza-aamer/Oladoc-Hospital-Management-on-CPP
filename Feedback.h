#include <iostream>
#include <string>
using namespace std;
class Feedback{
private:
    bool Feedback_status;
    bool Response_status;
    char Feedback[100];
    int Rating;
    char Response[100];

public:
    bool getRstatus(){
        return Response_status;
    }
    void setRstatus(bool set){
        Response_status=set;
    }
    void createResponse(){

    };
    bool getstatus(){
        return Feedback_status;
    }
    string getFeedback(){
        return Feedback;
    }
    int getRating(){
        return Rating;
    }
    string getResponse(){
        return Response;
    }
    void setstatus (bool set){
        Feedback_status=set;
    }
    void setFeedback(char*set){
        strcpy(Feedback,set);
    }
    void setRating(int set){
        Rating=set;
    }
    void setResponse(char*set){
        strcpy(Response,set);
    }
};