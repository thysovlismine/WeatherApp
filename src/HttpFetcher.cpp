#include "HttpFetcher.h"

wxDEFINE_EVENT(EVT_HTTP_FETCH_COMPLETE, wxThreadEvent);

// Constructor
HttpFetcher::HttpFetcher(wxEvtHandler* handler, const wxString& url)
    : m_handler(handler), m_url(url) {}

void HttpFetcher::Fetch() {
    //creates a separate thread
    std::thread(&HttpFetcher::FetchData, this).detach();
}

void HttpFetcher::Destroy(){
    //mark as a thread to be killed
    dead = true;
}

void HttpFetcher::FetchData(){
    //make sync call (takes some time)
    cpr::Response response;
    try{
        response = cpr::Get(cpr::Url{m_url.ToStdString()});
    }catch(const std::exception&){
        // Handle errors safely
        response.status_code = 0;
        response.text = "";
    }

    //send response back to the main thread (to be sure of order in execution)
    wxTheApp->CallAfter([this, response]() {
        //block and delete if dead
        if(dead){
            delete this;
            return;
        }

        if(m_handler) {
            //wxMessageBox("Handler is valid.");
        } else {
            wxMessageBox("Handler is NULL!");
        }

        //Emit Event
        if (wxTheApp && wxTheApp->IsMainLoopRunning()) {
            auto event = new wxThreadEvent(EVT_HTTP_FETCH_COMPLETE);
            event->SetPayload(response.status_code == 200 ? response.text : "");
            wxQueueEvent(m_handler, event);
        }

        //delete
        delete this;
    });
}
